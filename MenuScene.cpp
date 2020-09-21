#include "MenuScene.h"

#include <string>

#include "TextureGenerator.h"

MenuScene::MenuScene(Renderer& renderer, AudioManager& audio, void (*exit)(int)) : endFunction(exit) {
	// Load texutres
	int w;
	int h;
	const void* skyData = TextureGenerator::sky(256, 256);
	sky = renderer.loadTexture(256, 256, skyData);
	const void* titleData = TextureGenerator::realTexture(&w, &h, "res/title.png");
	title = renderer.loadTexture(w, h, titleData);
	const void* startButtonData = TextureGenerator::realTexture(&w, &h, "res/start.png");
	startButton = renderer.loadTexture(w, h, startButtonData);
	// Numbers
	const void* num0Data = TextureGenerator::realTexture(&w, &h, "res/0.png");
	num0 = renderer.loadTexture(w, h, num0Data);
	const void* num1Data = TextureGenerator::realTexture(&w, &h, "res/1.png");
	num1 = renderer.loadTexture(w, h, num1Data);
	const void* num2Data = TextureGenerator::realTexture(&w, &h, "res/2.png");
	num2 = renderer.loadTexture(w, h, num2Data);
	const void* num3Data = TextureGenerator::realTexture(&w, &h, "res/3.png");
	num3 = renderer.loadTexture(w, h, num3Data);
	const void* num4Data = TextureGenerator::realTexture(&w, &h, "res/4.png");
	num4 = renderer.loadTexture(w, h, num4Data);
	const void* num5Data = TextureGenerator::realTexture(&w, &h, "res/5.png");
	num5 = renderer.loadTexture(w, h, num5Data);
	const void* num6Data = TextureGenerator::realTexture(&w, &h, "res/6.png");
	num6 = renderer.loadTexture(w, h, num6Data);
	const void* num7Data = TextureGenerator::realTexture(&w, &h, "res/7.png");
	num7 = renderer.loadTexture(w, h, num7Data);
	const void* num8Data = TextureGenerator::realTexture(&w, &h, "res/8.png");
	num8 = renderer.loadTexture(w, h, num8Data);
	const void* num9Data = TextureGenerator::realTexture(&w, &h, "res/9.png");
	num9 = renderer.loadTexture(w, h, num9Data);
	
	// Clean up
	delete[] skyData;
	// These textures were loaded with stbi, so they have different cleanup
	TextureGenerator::freeLoaded(titleData);
	TextureGenerator::freeLoaded(startButtonData);
	TextureGenerator::freeLoaded(num0Data);
	TextureGenerator::freeLoaded(num1Data);
	TextureGenerator::freeLoaded(num2Data);
	TextureGenerator::freeLoaded(num3Data);
	TextureGenerator::freeLoaded(num4Data);
	TextureGenerator::freeLoaded(num5Data);
	TextureGenerator::freeLoaded(num6Data);
	TextureGenerator::freeLoaded(num7Data);
	TextureGenerator::freeLoaded(num8Data);
	TextureGenerator::freeLoaded(num9Data);
}

void MenuScene::init(int score) {
	// Set high score
	if (score > highScore) {
		highScore = score;
	}
}

void MenuScene::render(Renderer& renderer) {
	// Set camera positiom
	renderer.setCamera(glm::vec2(0.0f, 0.0f), 0.0f, aspect, 1.0f);

	// Draw the sky
	renderer.render(0.0f, 0.0f, 2.0f / aspect, 2.0f, 0.0f, sky);

	// Draw the GUI
	renderer.render(0.0f, 0.7f, 1.0f, -0.5f, 0.0f, title);
	renderer.render(0.0f, 0.0f, 0.5f, -0.5f, 0.0f, startButton);

	// High score
	std::string scoreString = std::to_string((int)highScore);
	scoreString.insert(scoreString.begin(), 10 - scoreString.length(), '0');
	float x = -0.5f;
	for (int i = 0; i <= 10; i++) {
		// Render the character
		switch (scoreString.c_str()[i]) {
		case '1': renderer.render(x, -0.8f, 0.1f, -0.1f, 0.0f, num1); break;
		case '2': renderer.render(x, -0.8f, 0.1f, -0.1f, 0.0f, num2); break;
		case '3': renderer.render(x, -0.8f, 0.1f, -0.1f, 0.0f, num3); break;
		case '4': renderer.render(x, -0.8f, 0.1f, -0.1f, 0.0f, num4); break;
		case '5': renderer.render(x, -0.8f, 0.1f, -0.1f, 0.0f, num5); break;
		case '6': renderer.render(x, -0.8f, 0.1f, -0.1f, 0.0f, num6); break;
		case '7': renderer.render(x, -0.8f, 0.1f, -0.1f, 0.0f, num7); break;
		case '8': renderer.render(x, -0.8f, 0.1f, -0.1f, 0.0f, num8); break;
		case '9': renderer.render(x, -0.8f, 0.1f, -0.1f, 0.0f, num9); break;
		default: renderer.render(x, -0.8f, 0.1f, -0.1f, 0.0f, num0);
		}
		x += 0.1f;
	}
}

void MenuScene::update(AudioManager& am, WindowManager& wm) {
	// Calculate the camera aspect ratio based on screen size
	aspect = (float)wm.getWidth() / (float)wm.getHeight();

	// Get mouse position
	float x;
	float y;
	wm.getMousePos(&x, &y);
	x /= aspect;

	// Mouse click events
	if (wm.getMouseButton(GLFW_MOUSE_BUTTON_1)) {
		if (!mouseClicked) {
			if (x < 0.25f && x > -0.25f) {
				if (y < 0.25f && y > -0.25f) {
					endFunction(0);
				}
			}
		}
		mouseClicked = true;
	} else {
		mouseClicked = false;
	}
}