#pragma once

class GameObject;
class World;

class PhysicsComponent
{
public:
	virtual void update(GameObject& object, World& world) = 0;
};