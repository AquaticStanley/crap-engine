#pragma once

class GameObject;
class World;

class PhysicsComponent
{
public:
	virtual void update(World& world) = 0;
};