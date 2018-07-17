#include "Player.h"

std::map<std::string, std::string> PlayerSpriteSheet::s_spriteMap = {
	{ "STANDING", "grillStandingSprite.png" }
};

std::string PlayerSpriteSheet::operator[](std::string spriteName)
{
	return s_spriteMap[spriteName];
}

void PlayerPhysicsComponent::update(GameObject& object, World& world)
{
	return;
}

void PlayerInputComponent::update(GameObject& object)
{
	return;
}

void PlayerGraphicsComponent::update(GameObject& object, Graphics& graphics, double frameProgress)
{
	int i = 1;
	return;
}

