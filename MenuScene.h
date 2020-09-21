#pragma once

#include <vector>

#include "Random.h"
#include "Scene.h"

class MenuScene : public Scene {
	// Scene that acts as a menu
public:
	MenuScene(Renderer& renderer, AudioManager& audio, void (*exit)(int));
	void init(int score);
	void render(Renderer& renderer);
	void update(AudioManager& am, WindowManager& wm);
private:
	void (*endFunction)(int);
	float aspect = 0.0f;
	bool mouseClicked = false;
	int highScore = 0;

	// Textures
	int title = 0;
	int startButton = 0;
	int sky = 0;
	int num0 = 0;
	int num1 = 0;
	int num2 = 0;
	int num3 = 0;
	int num4 = 0;
	int num5 = 0;
	int num6 = 0;
	int num7 = 0;
	int num8 = 0;
	int num9 = 0;
};