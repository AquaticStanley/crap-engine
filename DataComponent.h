#pragma once

#include <SFML/System.hpp>
#include "EntityTypes.h"
#include "MathFunctions.h"

class DataComponent
{
public:
  DataComponent(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f hitbox, EntityType::Type type, bool isOnGround) : 
  m_position(position), m_velocity(velocity), m_hitbox(hitbox), m_type(type), m_isOnGround(isOnGround)
  {
    m_id = getNewID();
  }

  sf::Vector2f m_position;
  sf::Vector2f m_velocity;
  sf::Vector2f m_hitbox;
  EntityType::Type m_type;
  bool m_isOnGround;
  unsigned int m_id;
};