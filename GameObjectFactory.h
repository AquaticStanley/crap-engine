#pragma once

#include "GameObject.h"

// Entity Dependencies
#include "Player.h"
#include "Platform.h"
#include "Bullet.h"
#include "Pellet.h"

//Big list of constants for dimensions and characteristics
const int PLAYER_HEIGHT = 30;
const int PLAYER_WIDTH = 15;

class GameObjectFactory
{
public:
	// Factory Methods
	GameObject* createPlayer(sf::Vector2f position);

	GameObject* createPlatform(sf::Vector2f position, sf::Vector2f hitbox);

  GameObject* createBullet(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f hitbox);

  GameObject* createPellet(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f hitbox);
};