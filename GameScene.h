#pragma once

#include <vector>

#include "Random.h"
#include "Scene.h"

class GameScene : public Scene {
	// Scene that the game is played on
public:
	GameScene(Renderer& renderer);
	void render(Renderer& renderer);
	void update(AudioManager& am, WindowManager& wm);
private:
	// Game random
	Random rand = Random();

	// Camera things
	float cameraX = 0.0f;
	float cameraY = 0.0f;
	float aspect = 0.0f;

	// Game objects
	float wavePosition = 0.0f;
	std::vector<glm::vec2> speedLines;

	// Textures
	int greenSine = 0;
	int white = 0;
	int sky = 0;
};