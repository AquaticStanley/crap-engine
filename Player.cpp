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
  // This function is to determine which functions the player will
  // actually accomplish when the time comes to update physics
  



  // if(sf::Keyboard::isKeyPressed(key_right))
  // {
  //   if(m_data->isOnGround)
  //   {
  //     m_data->m_velocity.x += WALK_ACCELERATION_GROUND;
  //   }
  //   else
  //   {
  //     m_data->m_velocity.x += WALK_ACCELERATION_AIR;
  //   }
  // }
  // else if(sf::Keyboard::isKeyPressed(key_left))
  // {
  //   if(m_data->isOnGround)
  //   {
  //     m_data->m_velocity.x -= WALK_ACCELERATION_GROUND;
  //   }
  //   else
  //   {
  //     m_data->m_velocity.x -= WALK_ACCELERATION_AIR;
  //   }
  // }
  // // Neither right or left are held
  // else
  // {
  //   if(m_data->m_velocity.x > 0)
  //   {
  //     if(m_data->isOnGround)
  //     {
  //       m_data->m_velocity.x = std::max(m_data->m_velocity.x - IDLE_X_ACCELERATION_GROUND, 0.0);
  //     }
  //     else
  //     {
  //       m_data->m_velocity.x = std::max(m_data->m_velocity.x - IDLE_X_ACCELERATION_AIR, 0.0);
  //     }
  //   }
  //   else
  //   {
  //     if(m_data->isOnGround)
  //     {
  //       m_data->m_velocity.x = std::min(m_data->m_velocity.x + IDLE_X_ACCELERATION_GROUND, 0.0);
  //     }
  //     else
  //     {
  //       m_data->m_velocity.x = std::min(m_data->m_velocity.x + IDLE_X_ACCELERATION_AIR, 0.0);
  //     }
  //   }
  // }

  // if(sf::Keyboard::isKeyPressed(key_space) && m_data->isOnGround)
  // {
  //   m_data->m_velocity.y += JUMP_VELOCITY;
  //   m_data->isOnGround = false;
  // }
  
	return;
}

void PlayerGraphicsComponent::update(GameObject& object, Graphics& graphics, double frameProgress)
{
	int i = 1;
	return;
}

