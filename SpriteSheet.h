#pragma once

class SpriteSheet
{
public:
	virtual std::string operator [](std::string spriteName) = 0;
};