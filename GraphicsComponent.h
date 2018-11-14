#pragma once

#include "Graphics.h"

class GameObject;

class GraphicsComponent
{
public:
	// virtual SpriteSheet* spritesheet;
	virtual void update(Graphics& graphics, double frameProgress) = 0;
};