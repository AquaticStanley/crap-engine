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
  // Update graphics of each entity
  for(unsigned int i = 0; i < entities.size(); i++)
  {
    entities.at(i).updateGraphics(*this, graphics, frameProgress);
  }
}

// void World::resolveCollision(const sf::Vector2f& hitbox, sf::Vector2f& position, sf::Vector2f
//       & velocity, const EntityType::Type type, bool& isOnGround)
// {

// }

void World::resolveCollision(DataComponent* data)
{
  sf::Vector2f previousPosition = data->m_position - data->m_velocity;
  data->m_isOnGround = false;

  // Check if space is occupied
  for(unsigned int i = 0; i < entities.size(); i++)
  {
    // Check to make sure entity being examined is not same entity being passed in
    if(entities[i].m_data->m_id != data->m_id)
    {
      bool sameXLevel = valueInRange(entities[i].m_data->m_position.x, data->m_position.x, data->m_position.x + data->m_hitbox.x + 1) ||
        valueInRange(data->m_position.x, entities[i].m_data->m_position.x, entities[i].m_data->m_position.x + entities[i].m_data->m_hitbox.x + 1);

      bool sameYLevel = valueInRange(entities[i].m_data->m_position.y, data->m_position.y, data->m_position.y + data->m_hitbox.y + 1) ||
        valueInRange(data->m_position.y, entities[i].m_data->m_position.y, entities[i].m_data->m_position.y + entities[i].m_data->m_hitbox.y + 1);
    
      if(sameXLevel && sameYLevel)
      {
        // Collision detected
        if(previousPosition.y > entities[i].m_data->m_position.y + entities[i].m_data->m_hitbox.y)
        {
          // Was above object before collision

          // Move up until no collision
          data->m_position.y = entities[i].m_data->m_position.y + entities[i].m_data->m_hitbox.y + 1;

          // Stop pushing into object
          data->m_velocity.y = 0;
        }
      
        else if(previousPosition.y + data->m_hitbox.y < entities[i].m_data->m_position.y)
        {
          // Was below object before collision

          // Move down until no collision
          data->m_position.y = entities[i].m_data->m_position.y - data->m_hitbox.y - 1;

          // Stop pushing into object
          data->m_velocity.y = 0;
        }
        else
        {
          // Was same level as object before collision - horizontal collision
          if(previousPosition.x > entities[i].m_data->m_position.x + entities[i].m_data->m_hitbox.x)
          {
            // Was to the right of object before collision

            // Move to the right until no collision
            data->m_position.x = entities[i].m_data->m_position.x + entities[i].m_data->m_hitbox.x + 1;

            // Stop pushing into object
            data->m_velocity.x = 0;
          }
          else if(previousPosition.x + data->m_hitbox.x < entities[i].m_data->m_position.x)
          {
            // Was to the left of object before collision

            // Move to the left until no collision
            data->m_position.x = entities[i].m_data->m_position.x - data->m_hitbox.x - 1;

            // Stop pushing into object
            data->m_velocity.x = 0;
          }
        }
      }

      if(sameXLevel && data->m_position.y == entities[i].m_data->m_position.y + entities[i].m_data->m_hitbox.y + 1)
      {
        // Object is on ground
        data->m_isOnGround = true;
      }
    }
  }

  return;
}

World::World()
{

}

World::World(std::vector<GameObject> entitiesInLevel)
{
  entities = entitiesInLevel;
}

void World::addEntities(std::vector<GameObject> entitiesToAdd)
{
  entities.insert(entities.end(), entitiesToAdd.begin(), entitiesToAdd.end());
}
