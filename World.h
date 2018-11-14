#pragma once

#include "Graphics.h"
#include "GameObject.h"
#include <vector>
#include <cmath>
// #include "MathFunctions.h"

// World Constants
// Units/second
const float WORLD_X_SPEED_LIMIT = 3.0;

// Units/second
const float WORLD_Y_SPEED_LIMIT = 7.0;

// Units/second^2
const float WORLD_GRAVITY_ACCELERATION = -0.05;

class World
{
public:
	std::vector<GameObject> entities;

  void processInput();

  void updatePhysics();

  void render(double frameProgress, Graphics& graphics);

  void resolveCollision(DataComponent* data);

  void resolveBulletCollision(DataComponent* data);

  World();
  
  World(std::vector<GameObject> entitiesInLevel);

  void addEntities(std::vector<GameObject> entitiesToAdd);

  bool canPassThrough(const EntityType::Type type1, const EntityType::Type type2);

  bool isOccupied(DataComponent* data);
};