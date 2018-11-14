#include "Game.h"

void GameLoop()
{
	std::cout << "Game Started" << std::endl;

	// Variables for frame progression
	int MS_PER_UPDATE = 10;

	// SFML Window Initialization
	sf::RenderWindow window(sf::VideoMode(1200, 600), "GameWindow", sf::Style::Close);
	// window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(60);

	// Variables for dealing with time and delta time
	Stopwatch<std::chrono::milliseconds> deltaClock;
	double lag = 0.0;
	double lagLeftOver = 1.0;

	// Variables for tracking framerate
	Stopwatch<std::chrono::milliseconds> framerateClock;
	framerateClock.start();
	int frameCount = 0;
  int vpsCount = 0;

	// Object for graphics manipulation
	sf::RenderWindow* windowPtr = &window;
	Graphics* graphics = new Graphics(windowPtr);

	// Create test level
	// std::vector<GameObject> gameObjects = getTestLevel();
	
  World world;

  // Spawn timer
  bool spawned = false;
  Stopwatch<std::chrono::milliseconds> spawnClock;
  spawnClock.start();

  // First time render

  // sf::CircleShape shape(100.f);
  // shape.setFillColor(sf::Color::Green);
  // sf::Vector2f position(10.f, 50.f);
  // double velocity = 0.0;
  while(window.isOpen())
  {
    sf::Event event;
    while(window.pollEvent(event))
    {
      // Close requested
      if(event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    // Check if it's time to spawn initial objects
    if(!spawned && spawnClock.elapsed() >= 1000)
    {
      spawned = true;
      std::vector<GameObject> gameObjects = getTestLevel();
      world.addEntities(gameObjects);
    }

    // Track framerate
    if(framerateClock.elapsed() >= 1000)
    {
      std::cout << "Entities: " << world.entities.size() << std::endl;
      std::cout << "FPS: " << frameCount << std::endl;
      std::cout << "VPS: " << vpsCount << std::endl << std::endl;

      framerateClock.restart();
      frameCount = 0;
      vpsCount = 0;
      // std::cout << world.entities.size() << std::endl;
      if(world.entities.size() > 0)
      {
        std::cout << "(" << world.entities[0].m_data->m_position.x << ", " << world.entities[0].m_data->m_position.y << ")\n";
      }
    }
    frameCount++;

    // Get delta time
    lag += deltaClock.restart();

    world.processInput();
    // bool increaseXAndY = false;
    // bool decreaseXAndY = false;
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    // {
    //   increaseXAndY = true;
    // }
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    // {
    //   decreaseXAndY = true;
    // }
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    // {
    //   velocity += 0.1;
    // }
    // else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    // {
    //   velocity -= 0.1;
    // }

    while(lag >= MS_PER_UPDATE)
    {

      world.updatePhysics();
      vpsCount++;
      // shape.setPosition(position);
      // if(increaseXAndY)
      // {
      //   shape.move(1.f, 1.f);
      // }
      // else if(decreaseXAndY)
      // {
      //   shape.move(-1.f, -1.f);
      // }
      // shape.move(velocity, velocity);

      lag -= MS_PER_UPDATE;
    }

    window.clear(sf::Color::Black);
    // window.draw(shape);
    world.render((lag/MS_PER_UPDATE) + (1.0 - lagLeftOver), *graphics);
    lagLeftOver = lag / MS_PER_UPDATE;

    window.display();
  }

  return;
}

std::vector<GameObject> getTestLevel()
{
  std::vector<GameObject> gameObjects;
  GameObjectFactory gameObjectFactory;

  // Create Player
  sf::Vector2f startingPos1 = sf::Vector2f(300, 600);
  GameObject* object = gameObjectFactory.createPlayer(startingPos1);
  
  gameObjects.push_back(*object);
  return gameObjects;
}