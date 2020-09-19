#include "Random.h"

#include <ctime>

Random::Random() {
	// Create random generator
	generator = std::default_random_engine();
	generator.seed(time(0));
}

int Random::randInt(int a, int b) {
	// Generate random int
	std::uniform_int_distribution<int> distribution(a, b);
	return distribution(generator);
}

float Random::randFloat() {
	// Generate random float
	std::uniform_real_distribution<float> distribution;
	return distribution(generator);
}