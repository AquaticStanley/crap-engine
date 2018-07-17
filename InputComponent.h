#pragma once

class GameObject;

class InputComponent
{
public:
	virtual void update(GameObject& object) = 0;
};