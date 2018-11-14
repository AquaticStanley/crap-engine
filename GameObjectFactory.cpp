#include "GameObjectFactory.h"

GameObject* GameObjectFactory::createPlayer(sf::Vector2f position)
{
  PlayerDataComponent* data = new PlayerDataComponent(position, sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT), EntityType::Player, false);
  return new GameObject(new PlayerInputComponent(data), new PlayerPhysicsComponent(data), new PlayerGraphicsComponent(data), data);
}

GameObject* GameObjectFactory::createPlatform(sf::Vector2f position, sf::Vector2f hitbox)
{
  PlatformDataComponent* data = new PlatformDataComponent(position, hitbox);
  return new GameObject(new PlatformInputComponent(), new PlatformPhysicsComponent(), new PlatformGraphicsComponent(data), data);
}

GameObject* GameObjectFactory::createBullet(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f hitbox)
{
  BulletDataComponent* data = new BulletDataComponent(position, velocity, hitbox);
  return new GameObject(new BulletInputComponent(), new BulletPhysicsComponent(data), new BulletGraphicsComponent(data), data);
}