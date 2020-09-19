#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "AudioManager.h"
#include "GameScene.h"
#include "Renderer.h"
#include "Scene.h"
#include "TextureGenerator.h"
#include "WindowManager.h"

int main() {
	// Initialize backend interfaces
	WindowManager wm = WindowManager(800, 500, "Airwaves");
	Renderer renderer = Renderer();
	AudioManager audio = AudioManager();

	// Initialize scenes
	GameScene gameScene = GameScene(renderer);
	Scene& currentScene = gameScene;

	// Fullscreen toggle variable
	bool fullscreenToggle = false;
	bool fullscreenTogglePressed = false;

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
		currentScene.update(audio, wm);
		currentScene.render(renderer);
	}

	wm.fullscreen(false);

	// Stop audio playback
	audio.stop();

	return 0;
}