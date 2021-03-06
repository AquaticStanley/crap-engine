#include "Player.h"

std::map<std::string, std::string> PlayerSpriteSheet::s_spriteMap = {
	{ "STANDING", "grillStandingSprite.png" }
};

std::string PlayerSpriteSheet::operator[](std::string spriteName)
{
	return s_spriteMap[spriteName];
}

std::vector<GameObject> PlayerDataComponent::bullet(World& world)
{
  std::vector<GameObject> gameObjects;
  GameObjectFactory gof;

  // Get starting position
  sf::Vector2f position = getProjectileStartingPos(world);

  // Get velocity
  sf::Vector2f velocity(PLAYER_BULLET_VELOCITY, 0.0);

  if(!facingRight)
  {
    velocity.x *= -1;
  }

  sf::Vector2f hitbox(PLAYER_BULLET_WIDTH, PLAYER_BULLET_HEIGHT);
  GameObject* object = gof.createBullet(position, velocity, hitbox);
  gameObjects.push_back(*object);

  return gameObjects;
}

std::vector<GameObject> PlayerDataComponent::shotgun(World& world)
{
  (void)world;
  std::vector<GameObject> gameObjects;
  GameObjectFactory gof;

  // Get starting position
  sf::Vector2f position = getProjectileStartingPos(world);

  // Get velocity for multiple bullets
  double currentVelocityX = PLAYER_BULLET_VELOCITY;

  if(!facingRight)
  {
    currentVelocityX *= -1;
  }
  double currentVelocityY = (0.0 - (SHOTGUN_CONE_WIDTH / 2));
  double distanceBetweenEachPellet = SHOTGUN_CONE_WIDTH / NUM_SHOTGUN_PELLETS;

  sf::Vector2f hitbox(PLAYER_BULLET_WIDTH, PLAYER_BULLET_HEIGHT);

  for(int i = 0; i < NUM_SHOTGUN_PELLETS; i++)
  {
    currentVelocityY += distanceBetweenEachPellet;
    GameObject* object = gof.createPellet(position, sf::Vector2f(currentVelocityX, currentVelocityY), hitbox);
    gameObjects.push_back(*object);
  }

  return gameObjects;
}

std::vector<GameObject> PlayerDataComponent::blink(World& world)
{
  std::vector<GameObject> gameObjects;

  // Get ending position
  sf::Vector2f blinkVector(BLINK_DISTANCE, 1.0);

  if(!facingRight)
  {
    blinkVector.x *= -1.0;
  }

  sf::Vector2f oldPosition = m_position;
  m_position += blinkVector;

  // Check if position is occupied
  if(world.isOccupied(this))
  {
    m_position = oldPosition;
  }


  return gameObjects;
}

// std::vector<GameObject> PlayerDataComponent::hookshot(World& world)
// {
//   (void)world;
//   std::vector<GameObject> gameObjects;
//   GameObjectFactory gof;
// }


bool PlayerDataComponent::isIdle()
{
  return !(walkingRight || walkingLeft || floatingRight || floatingLeft);
}

bool PlayerDataComponent::anyAbilitiesActivated()
{
  return (ab1Activated || ab2Activated || ab3Activated || ab4Activated);
}

bool PlayerDataComponent::anyAbilitiesInProgress()
{
  return abilityIP;
}

void PlayerDataComponent::setWalkingRight()
{
  clearLeftRight();
  walkingRight = true;
  facingRight = true;
}

void PlayerDataComponent::setWalkingLeft()
{
  clearLeftRight();
  walkingLeft = true;
  facingRight = false;
}

void PlayerDataComponent::setFloatingRight()
{
  clearLeftRight();
  floatingRight = true;
  facingRight = true;
}

void PlayerDataComponent::setFloatingLeft()
{
  clearLeftRight();
  floatingLeft = true;
  facingRight = false;
}

void PlayerDataComponent::clearLeftRight()
{
  walkingLeft = false;
  walkingRight = false;
  floatingLeft = false;
  floatingRight = false;
}

void PlayerDataComponent::clearAbilityActivatedFlags()
{
  ab1Activated = false;
  ab2Activated = false;
  ab3Activated = false;
  ab4Activated = false;
}

sf::Vector2f PlayerDataComponent::getProjectileStartingPos(World& world)
{
  // Later on use world to check where to spawn bullet
  (void)world;

  // Get starting position
  sf::Vector2f position(m_position);
  position.y += (m_hitbox.y / 2.0);
  if(facingRight)
  {
    position.x += m_hitbox.x;
  }

  return position;
}


void PlayerPhysicsComponent::update(World& world)
{
  if(m_data->walkingRight)
  {
    m_data->m_velocity.x += WALK_ACCELERATION_GROUND;
  }
  else if(m_data->walkingLeft)
  {
    m_data->m_velocity.x -= WALK_ACCELERATION_GROUND;
  }
  else if(m_data->floatingRight)
  {
    m_data->m_velocity.x += WALK_ACCELERATION_AIR;
  }
  else if(m_data->floatingLeft)
  {
    m_data->m_velocity.x -= WALK_ACCELERATION_AIR;
  }
  else if(m_data->isIdle())
  {
    if(m_data->m_velocity.x > 0)
    {
      if(m_data->m_isOnGround)
      {
        m_data->m_velocity.x = std::max(m_data->m_velocity.x - IDLE_X_ACCELERATION_GROUND, 0.0);
      }
      else
      {
        m_data->m_velocity.x = std::max(m_data->m_velocity.x - IDLE_X_ACCELERATION_AIR, 0.0);
      }
    }
    else
    {
      if(m_data->m_isOnGround)
      {
        m_data->m_velocity.x = std::min(m_data->m_velocity.x + IDLE_X_ACCELERATION_GROUND, 0.0);
      }
      else
      {
        m_data->m_velocity.x = std::min(m_data->m_velocity.x + IDLE_X_ACCELERATION_AIR, 0.0);
      }
    }
  }

  if(m_data->ab1Activated && !m_data->abilityIP)
  {
    world.addEntities(m_data->abilities[0](world));
    m_data->abilityIP = true;
    m_data->ab1Activated = false;
  }

  if(m_data->ab2Activated && !m_data->abilityIP)
  {
    world.addEntities(m_data->abilities[1](world));
    m_data->abilityIP = true;
    m_data->ab2Activated = false;
  }

  if(m_data->ab3Activated && !m_data->abilityIP)
  {
    world.addEntities(m_data->abilities[2](world));
    m_data->abilityIP = true;
    m_data->ab3Activated = false;
  }

  if(m_data->jumping && !m_data->jumpIP && m_data->m_isOnGround)
  {
    m_data->m_velocity.y += JUMP_VELOCITY;
    m_data->m_isOnGround = false;
    m_data->jumpIP = true;
    m_data->jumping = false;
  }

  if(m_data->m_hp <= 0)
  {
    m_data->m_toBeRemoved = true;
  }

  // Set player's velocity due to acceleration from gravity
  if(m_data->m_isOnGround)
  {
    m_data->m_velocity.y = 0;
  }
  else
  {
    m_data->m_velocity.y += WORLD_GRAVITY_ACCELERATION;
  }

  // Cap x and y movement speeds
  if(std::abs(m_data->m_velocity.x) >= WORLD_X_SPEED_LIMIT)
  {
    if(m_data->m_velocity.x < 0)
    {
      m_data->m_velocity.x = WORLD_X_SPEED_LIMIT * -1;
    }
    else
    {
      m_data->m_velocity.x = WORLD_X_SPEED_LIMIT;
    }
  }

  if(std::abs(m_data->m_velocity.y) >= WORLD_Y_SPEED_LIMIT)
  {
    if(m_data->m_velocity.y < 0)
    {
      m_data->m_velocity.y = WORLD_Y_SPEED_LIMIT * -1;
    }
    else
    {
      m_data->m_velocity.y = WORLD_Y_SPEED_LIMIT;
    }
  }

  // Set player's position due to velocity and other modifiers
  m_data->m_position += m_data->m_velocity;

  // Resolve world collisions
  world.resolveCollision(m_data);

	return;
}

void PlayerInputComponent::update()
{
  // This function is to determine which functions the player will
  // actually accomplish when the time comes to update physics

  if(m_data->canMove)
  {
    if(sf::Keyboard::isKeyPressed(key_right))
    {
      if(m_data->m_isOnGround)
      {
        m_data->setWalkingRight();
      }
      else
      {
        m_data->setFloatingRight();
      }
    }
    else if(sf::Keyboard::isKeyPressed(key_left))
    {
      if(m_data->m_isOnGround)
      {
        m_data->setWalkingLeft();
      }
      else
      {
        m_data->setFloatingLeft();
      }
    }
    else // Neither right or left are held
    {
      m_data->clearLeftRight();
    }
  }

  if(!m_data->jumpIP)
  {
    if(sf::Keyboard::isKeyPressed(key_space))
    {
      if(m_data->m_isOnGround)
      {
        m_data->jumping = true;
      }
    }
  }
  else
  {
    m_data->jumping = false;
    if(!sf::Keyboard::isKeyPressed(key_space))
    {
      m_data->jumpIP = false;
    }
  }


  // Set these to false conditionally
  if(!m_data->anyAbilitiesInProgress())
  {
    if(sf::Keyboard::isKeyPressed(key_ab1))
    {
      m_data->ab1Activated = true;
    }
    else if(sf::Keyboard::isKeyPressed(key_ab2))
    {
      m_data->ab2Activated = true;
    }
    else if(sf::Keyboard::isKeyPressed(key_ab3))
    {
      m_data->ab3Activated = true;
    }
    else if(sf::Keyboard::isKeyPressed(key_ab4))
    {
      m_data->ab4Activated = true;
    }
  }
  else
  {
    m_data->clearAbilityActivatedFlags();
    if(!sf::Keyboard::isKeyPressed(key_ab1) && !sf::Keyboard::isKeyPressed(key_ab2) && !sf::Keyboard::isKeyPressed(key_ab3))
    {
      m_data->abilityIP = false;
    }
  }
  
	return;
}

void PlayerGraphicsComponent::update(Graphics& graphics, double frameProgress)
{
  // sf::Vector2f predictedPosition = object.position_ + sf::Vector2f(object.velocity_.x * frameProgress, object.velocity_.y * frameProgress);

  sf::Vector2f predictedPosition = m_data->m_position + sf::Vector2f(m_data->m_velocity.x * frameProgress, m_data->m_velocity.y * frameProgress);
	
  graphics.draw(predictedPosition, m_data->m_hitbox, STANDING_SPRITE);

  return;
}

