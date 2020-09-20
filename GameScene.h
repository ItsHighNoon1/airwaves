#pragma once

#include <vector>

#include "Random.h"
#include "Scene.h"

class GameScene : public Scene {
	// Scene that the game is played on
public:
	GameScene(Renderer& renderer, AudioManager& audio);
	void render(Renderer& renderer);
	void update(AudioManager& am, WindowManager& wm);
private:
	// Constants
	static const int WAVELENGTH = 10;

	// Game random
	Random rand = Random();

	// Camera
	float cameraX = 0.0f;
	float cameraY = 0.0f;
	float cameraScale = 0.1f;
	float aspect = 0.0f;

	// Game objects
	float waveOffset = 0.0f;
	int currentWaveType = 0;
	glm::vec2 wavePositions[WAVELENGTH];
	std::vector<glm::vec2> speedLines;

	// Textures
	int redSine = 0;
	int redSquare = 0;
	int redSaw = 0;
	int greenSine = 0;
	int greenSquare = 0;
	int greenSaw = 0;
	int blueSine = 0;
	int blueSquare = 0;
	int blueSaw = 0;
	int white = 0;
	int sky = 0;

	// Sounds
	int playerSound = 0;
};