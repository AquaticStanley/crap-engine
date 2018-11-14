#pragma once

#include <iostream>
#include <SFML/System.hpp>
#include "Stopwatch.h"
#include "Graphics.h"
#include "World.h"
#include "GameObjectFactory.h"

void GameLoop();

std::vector<GameObject> getTestLevel();