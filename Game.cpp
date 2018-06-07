#include "Game.h"
#include "SFML/System.hpp"
#include <chrono>

void GameLoop()
{
	std::cout << "Game Started" << std::endl;

	// Variables for frame progression
	int MS_PER_UPDATE = 10;

	// SFML Window Initialization
	sf::RenderWindow window(sf::VideoMode(1200, 600), "GameWindow", sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	//Variables for dealing with time and delta time
}