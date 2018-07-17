#pragma once

#include "ComponentDependency.h"

class PlayerSpriteSheet : public SpriteSheet
{
private:
	static std::map<std::string, std::string> s_spriteMap;

public:
	std::string operator [](std::string spriteName);
};

class PlayerPhysicsComponent : public PhysicsComponent
{
public:
	virtual void update(GameObject& object, World& world);

	bool isOnGround;

	PlayerPhysicsComponent() : isOnGround(false) {}
};

class PlayerInputComponent : public InputComponent
{
private:
	// Player specific physics properties
	const float WALK_ACCELERATION_GROUND = 0.5;
    const float WALK_ACCELERATION_AIR = 0.25;
    const float IDLE_X_ACCELERATION_GROUND = 0.25;
    const float IDLE_X_ACCELERATION_AIR = 0.1;
    const float JUMP_VELOCITY = 2;

    PlayerPhysicsComponent* m_physics;

public:
	PlayerInputComponent(PlayerPhysicsComponent* physics) : m_physics(physics) {}

	virtual void update(GameObject& object);
};

class PlayerGraphicsComponent : public GraphicsComponent
{
private:
	PlayerPhysicsComponent* m_physics;

	// Player specific animations and sprites
	PlayerSpriteSheet m_spriteSheet;

public:
	PlayerGraphicsComponent(PlayerPhysicsComponent* physics) : m_physics(physics)
	{

	}

	virtual void update(GameObject& object, Graphics& graphics, double frameProgress);
};
