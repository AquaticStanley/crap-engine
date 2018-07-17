#pragma once

#include <SFML/Graphics.hpp>

class Graphics
{
private:
	sf::RenderWindow* m_window;

public:
	Graphics(sf::RenderWindow* window) : m_window(window) {}

	void draw(sf::Vector2f position, sf::Vector2f hitbox, sf::Color color);
};