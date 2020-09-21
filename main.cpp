#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "AudioManager.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "Renderer.h"
#include "Scene.h"
#include "TextureGenerator.h"
#include "WindowManager.h"

// Function declarations
void goToGame(int);
void returnToMenu(int score);

// Backend interfaces
WindowManager wm = WindowManager(800, 500, "Airwaves");
Renderer renderer = Renderer();
AudioManager audio = AudioManager();

// Scenes
MenuScene menuScene = MenuScene(renderer, audio, goToGame);
GameScene gameScene = GameScene(renderer, audio, returnToMenu);
bool inGame;

// Fullscreen toggle variable
bool fullscreenToggle = false;
bool fullscreenTogglePressed = false;

// Callback to start playing
void goToGame(int) {
	gameScene.init(0);
	inGame = true;
}

// Callback for when you die
void returnToMenu(int score) {
	menuScene.init(score);
	inGame = false;
}

int main() {
	// Start audio playback
	audio.start();

	// Main loop
	while (!wm.update()) {
		// Close the game instantly on escape press
		if (wm.getKey(GLFW_KEY_ESCAPE)) {
			break;
		}

		// Toggle fullscreen on F11 press
		if (wm.getKey(GLFW_KEY_F11)) {
			if (!fullscreenTogglePressed) {
				fullscreenToggle = !fullscreenToggle;
				wm.fullscreen(fullscreenToggle);
			}
			fullscreenTogglePressed = true;
		} else {
			fullscreenTogglePressed = false;
		}

		// Update and render the scene
		renderer.clear();
		if (inGame) {
			gameScene.update(audio, wm);
			gameScene.render(renderer);
		} else {
			menuScene.update(audio, wm);
			menuScene.render(renderer);
		}
	}
	wm.fullscreen(false);

	// Stop audio playback
	audio.stop();

	return 0;
}