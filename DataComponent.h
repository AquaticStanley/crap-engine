#pragma once

#include <SFML/System.hpp>
#include "EntityTypes.h"

class DataComponent
{
public:
  DataComponent(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f hitbox, EntityType::Type type) : m_position(position), m_velocity(velocity), m_hitbox(hitbox), m_type(type) {}

  sf::Vector2f m_position;
  sf::Vector2f m_velocity;
  sf::Vector2f m_hitbox;
  EntityType::Type m_type;
};