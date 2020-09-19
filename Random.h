#pragma once

#include <random>

class Random {
	// Class that generates random numbers
public:
	Random();
	int randInt(int a, int b);
	float randFloat();
private:
	std::default_random_engine generator;
};