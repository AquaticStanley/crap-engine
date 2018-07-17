#include "GameObjectFactory.h"

GameObject* GameObjectFactory::createPlayer(sf::Vector2f position)
{
    PlayerPhysicsComponent* physics = new PlayerPhysicsComponent;
    return new GameObject(new PlayerInputComponent(physics), physics, new PlayerGraphicsComponent(physics), position, sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT), EntityType::Player);
}