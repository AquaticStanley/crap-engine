#pragma once

#include <SFML/System.hpp>
#include "Graphics.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"
#include "EntityTypes.h"

class World;

class GameObject
{
private:
	InputComponent* m_input;
	PhysicsComponent* m_physics;
	GraphicsComponent* m_graphics;

public:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_hitbox;

	EntityType::Type m_type;

	bool m_toBeRemoved;

	GameObject(InputComponent* input, 
		PhysicsComponent* physics, 
		GraphicsComponent* graphics, 
		sf::Vector2f position,
		sf::Vector2f hitbox,
		EntityType::Type entityType)
		: m_input(input), m_physics(physics), m_graphics(graphics), m_position(position), m_hitbox(hitbox), m_type(entityType) 
		{
			m_toBeRemoved = false;
		}

	void updateInput();

	std::vector<GameObject> updatePhysics(World& world);

	void updateGraphics(World& world, Graphics& graphics, double frameProgress);
};