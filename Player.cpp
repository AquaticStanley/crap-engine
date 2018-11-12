#include "Player.h"

std::map<std::string, std::string> PlayerSpriteSheet::s_spriteMap = {
	{ "STANDING", "grillStandingSprite.png" }
};

std::string PlayerSpriteSheet::operator[](std::string spriteName)
{
	return s_spriteMap[spriteName];
}

void PlayerPhysicsComponent::update(GameObject& object, World& world)
{

	return;
}

void PlayerInputComponent::update(GameObject& object)
{
  if(sf::Keyboard::isKeyPressed(key_right))
  {
    if(m_physics->isOnGround)
    {
      object.m_velocity.x += WALK_ACCELERATION_GROUND;
    }
    else
    {
      object.m_velocity.x += WALK_ACCELERATION_AIR;
    }
  }
  else if(sf::Keyboard::isKeyPressed(key_left))
  {
    if(m_physics->isOnGround)
    {
      object.m_velocity.x -= WALK_ACCELERATION_GROUND;
    }
    else
    {
      object.m_velocity.x -= WALK_ACCELERATION_AIR;
    }
  }
  // Neither right or left are held
  else
  {
    if(object.m_velocity.x > 0)
    {
      if(m_physics->isOnGround)
      {
        object.m_velocity.x = std::max(object.m_velocity.x - IDLE_X_ACCELERATION_GROUND, 0.0);
      }
      else
      {
        object.m_velocity.x = std::max(object.m_velocity.x - IDLE_X_ACCELERATION_AIR, 0.0);
      }
    }
    else
    {
      if(m_physics->isOnGround)
      {
        object.m_velocity.x = std::min(object.m_velocity.x + IDLE_X_ACCELERATION_GROUND, 0.0);
      }
      else
      {
        object.m_velocity.x = std::min(object.m_velocity.x + IDLE_X_ACCELERATION_AIR, 0.0);
      }
    }
  }

  if(sf::Keyboard::isKeyPressed(key_space) && m_physics->isOnGround)
  {
    object.m_velocity.y += JUMP_VELOCITY;
    m_physics->isOnGround = false;
  }
  
	return;
}

void PlayerGraphicsComponent::update(GameObject& object, Graphics& graphics, double frameProgress)
{
	int i = 1;
	return;
}

