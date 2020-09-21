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
	// Structures
	struct BarrierWave {
		glm::vec2 start;
		glm::vec2 end;
		float width;
		int type;
		int audioWave;
	};

	// Misc. variables
	float secondTimer = 0.0f;
	float speed = 20.0f;

	// Functions
	void everySecond(AudioManager& am);
	void die();

	// Constants
	static const int WAVELENGTH = 10;

	// Game random
	Random rand = Random();

	// Camera
	float cameraScale = 0.1f;
	float aspect = 0.0f;

	// Game objects
	float health = 1.0f;
	float iFrames = 0.0f;
	float waveOffset = 0.0f;
	int currentWaveType = 0;
	glm::vec2 wavePositions[WAVELENGTH] = {};
	std::vector<BarrierWave> obstacles;
	std::vector<glm::vec2> speedLines;

	// Textures
	int redSine = 0;
	int greenSquare = 0;
	int blueSaw = 0;
	int white = 0;
	int green = 0;
	int red = 0;
	int sky = 0;

	// Sounds
	int playerSound = 0;
};