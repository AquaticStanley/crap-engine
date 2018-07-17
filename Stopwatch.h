#pragma once

#include <chrono>

template <class T>
class Stopwatch
{
private:
	typedef std::chrono::high_resolution_clock clock;
	clock::time_point start_time;

public:
	// Starts the stopwatch
	void start();

	// Returns the elapsed time as a number of T's without restarting the stopwatch (split)
	int elapsed();

	// Returns the elapsed time as a number of T's and restarts the stopwatch
	int restart();
};

#include "Stopwatch.hpp"