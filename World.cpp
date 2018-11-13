#include "World.h"

void World::processInput()
{
  for(unsigned int i = 0; i < entities.size(); i++)
  {
    entities.at(i).updateInput();
  }
}

void World::updatePhysics()
{
  // Update physics of each entity and add spawned entities to world
  for(unsigned int i = 0; i < entities.size(); i++)
  {
    // std::vector<GameObject> spawnedObjects = entities.at(i).updatePhysics(*this);
    entities.at(i).updatePhysics(*this);
  }

  // Remove dead entities
  for(unsigned int i = 0; i < entities.size(); i++)
  {
    if(entities.at(i).m_toBeRemoved)
    {
      entities.erase(entities.begin() + i);
      i--;
    }
  }
}

void World::render(double frameProgress, Graphics& graphics)
{

}

void World::resolveCollision(const sf::Vector2f& hitbox, sf::Vector2f& position, sf::Vector2f
      & velocity, const EntityType::Type type, bool& isOnGround)
{

}


World::World(std::vector<GameObject> entitiesInLevel)
{
  entities = entitiesInLevel;
}