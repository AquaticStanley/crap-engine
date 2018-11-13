#pragma once

#include <SFML/System.hpp>
#include "Graphics.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"
#include "DataComponent.h"
#include "EntityTypes.h"

class World;

class GameObject
{
private:
	InputComponent* m_input;
	PhysicsComponent* m_physics;
	GraphicsComponent* m_graphics;
  DataComponent* m_data;

public:
	bool m_toBeRemoved;

	GameObject(InputComponent* input,
		PhysicsComponent* physics,
		GraphicsComponent* graphics,
    DataComponent* data)
		: m_input(input), m_physics(physics), m_graphics(graphics), m_data(data)
		{
			m_toBeRemoved = false;
		}

	void updateInput();

	void updatePhysics(World& world);

	void updateGraphics(World& world, Graphics& graphics, double frameProgress);
};