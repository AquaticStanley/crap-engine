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
	
  // Create empty world to fill later
  World world;

  // Spawn timer
  bool spawned = false;
  Stopwatch<std::chrono::milliseconds> spawnClock;
  spawnClock.start();

  // Create view for zoom and camera
  float zoomMultiplier = 1.5;
  sf::View view = window.getDefaultView();
  view.zoom(1 / zoomMultiplier);
  window.setView(view);


  // Main game loop
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

    while(lag >= MS_PER_UPDATE)
    {

      world.updatePhysics();
      vpsCount++;

      lag -= MS_PER_UPDATE;
    }

    window.clear(sf::Color::Black);
    world.render((lag/MS_PER_UPDATE) + (1.0 - lagLeftOver), *graphics);
    lagLeftOver = lag / MS_PER_UPDATE;

    if(spawned)
    {
      view.setCenter(sf::Vector2f(world.entities[0].m_data->m_position.x * 2, view.getSize().y * zoomMultiplier) - world.entities[0].m_data->m_position);
    }
    window.setView(view);
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

  sf::Vector2f startingPos2 = sf::Vector2f(300, 500);
  sf::Vector2f hitBox1 = sf::Vector2f(100, 3);
  object = gameObjectFactory.createPlatform(startingPos2, hitBox1);
  gameObjects.push_back(*object);

  sf::Vector2f startingPos3 = sf::Vector2f(100, 200);
  sf::Vector2f hitBox2 = sf::Vector2f(30, 600);
  object = gameObjectFactory.createPlatform(startingPos3, hitBox2);
  gameObjects.push_back(*object);

  //Create floor
  sf::Vector2f startingPosition4 = sf::Vector2f(100, 200);
  sf::Vector2f hitBox3 = sf::Vector2f(500, 5);
  object = gameObjectFactory.createPlatform(startingPosition4, hitBox3);

  gameObjects.push_back(*object);

  //Create ceiling
  sf::Vector2f startingPosition5 = sf::Vector2f(150, 250);
  sf::Vector2f hitBox4 = sf::Vector2f(300, 4);
  object = gameObjectFactory.createPlatform(startingPosition5, hitBox4);

  gameObjects.push_back(*object);

  //Create other wall
  sf::Vector2f startingPosition6 = sf::Vector2f(600, 200);
  sf::Vector2f hitBox5 = sf::Vector2f(400, 20);
  object = gameObjectFactory.createPlatform(startingPosition6, hitBox5);

  gameObjects.push_back(*object);

  //Create floor to jump to with a gap
  sf::Vector2f startingPosition7 = sf::Vector2f(1100, 200);
  sf::Vector2f hitBox6 = sf::Vector2f(400, 20);
  object = gameObjectFactory.createPlatform(startingPosition7, hitBox6);

  gameObjects.push_back(*object);

  return gameObjects;
}