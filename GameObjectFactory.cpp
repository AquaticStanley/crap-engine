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

GameObject* GameObjectFactory::createPellet(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f hitbox)
{
  BulletDataComponent* data = new BulletDataComponent(position, velocity, hitbox);
  return new GameObject(new BulletInputComponent(), new BulletPhysicsComponent(data), new PelletGraphicsComponent(data), data);
}

GameObject* GameObjectFactory::createCamera(DataComponent* dataToFollow)
{
  CameraDataComponent* data = new CameraDataComponent(dataToFollow);
  return new GameObject(new CameraInputComponent(), new CameraPhysicsComponent(data), new CameraGraphicsComponent(), data);
}
