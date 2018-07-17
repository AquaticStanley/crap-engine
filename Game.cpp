#include "Game.h"

void GameLoop()
{
	std::cout << "Game Started" << std::endl;

	// Variables for frame progression
	int MS_PER_UPDATE = 10;

	// SFML Window Initialization
	sf::RenderWindow window(sf::VideoMode(1200, 600), "GameWindow", sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	// Variables for dealing with time and delta time
	Stopwatch<std::chrono::milliseconds> deltaClock;
	double lag = 0.0;
	double lagLeftOver = 1.0;

	// Variables for tracking framerate
	Stopwatch<std::chrono::milliseconds> framerateClock;
	framerateClock.start();
	int frameCount = 0;

	// Object for graphics manipulation
	sf::RenderWindow* windowPtr = &window;
	Graphics* graphics = new Graphics(windowPtr);

	// Create test level
	std::vector<GameObject> gameObjects;
	
}