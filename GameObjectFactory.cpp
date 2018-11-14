#include "GameObjectFactory.h"

GameObject* GameObjectFactory::createPlayer(sf::Vector2f position)
{
    PlayerDataComponent* data = new PlayerDataComponent(position, sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT), EntityType::Player, false);
    PlayerPhysicsComponent* physics = new PlayerPhysicsComponent(data);
    return new GameObject(new PlayerInputComponent(data), physics, new PlayerGraphicsComponent(data), data);
}