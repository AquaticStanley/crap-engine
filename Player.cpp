#include "Player.h"

std::map<std::string, std::string> PlayerSpriteSheet::s_spriteMap = {
	{ "STANDING", "grillStandingSprite.png" }
};

std::string PlayerSpriteSheet::operator[](std::string spriteName)
{
	return s_spriteMap[spriteName];
}

bool PlayerDataComponent::isIdle()
{
  return (walkingRight || walkingLeft || floatingRight || floatingLeft);
}

bool PlayerDataComponent::usingAbility()
{
  return (usingAb1 || usingAb2 || usingAb3 || usingAb4);
}

void PlayerDataComponent::setWalkingRight()
{
  clearLeftRight();
  walkingRight = true;
}

void PlayerDataComponent::setWalkingLeft()
{
  clearLeftRight();
  walkingLeft = true;
}

void PlayerDataComponent::setFloatingRight()
{
  clearLeftRight();
  floatingRight = true;
}

void PlayerDataComponent::setFloatingLeft()
{
  clearLeftRight();
  floatingLeft = true;
}

void PlayerDataComponent::clearLeftRight()
{
  walkingLeft = false;
  walkingRight = false;
  floatingLeft = false;
  floatingRight = false;
}

void PlayerPhysicsComponent::update(GameObject& object, World& world)
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
      if(m_data->isOnGround)
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
      if(m_data->isOnGround)
      {
        m_data->m_velocity.x = std::min(m_data->m_velocity.x + IDLE_X_ACCELERATION_GROUND, 0.0);
      }
      else
      {
        m_data->m_velocity.x = std::min(m_data->m_velocity.x + IDLE_X_ACCELERATION_AIR, 0.0);
      }
    }
  }

  if(m_data->jumping && m_data->isOnGround)
  {
    m_data->m_velocity.y += JUMP_VELOCITY;
    m_data->isOnGround = false;
  }

	return;
}

void PlayerInputComponent::update()
{
  // This function is to determine which functions the player will
  // actually accomplish when the time comes to update physics

  if(sf::Keyboard::isKeyPressed(key_right))
  {
    if(m_data->isOnGround)
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
    if(m_data->isOnGround)
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

  if(sf::Keyboard::isKeyPressed(key_space))
  {
    if(m_data->isOnGround)
    {
      m_data->jumping = true;
    }
  }

  if(!m_data->usingAbility())
  {
    if(sf::Keyboard::isKeyPressed(key_ab1))
    {
      m_data->usingAb1 = true;
    }
    else if(sf::Keyboard::isKeyPressed(key_ab2))
    {
      m_data->usingAb2 = true;
    }
    else if(sf::Keyboard::isKeyPressed(key_ab3))
    {
      m_data->usingAb3 = true;
    }
    else if(sf::Keyboard::isKeyPressed(key_ab4))
    {
      m_data->usingAb4 = true;
    }
  }
  
	return;
}

void PlayerGraphicsComponent::update(GameObject& object, Graphics& graphics, double frameProgress)
{
	return;
}

