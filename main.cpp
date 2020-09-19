#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "AudioManager.h"
#include "TextureGenerator.h"
#include "Renderer.h"
#include "WindowManager.h"

int main() {
	// Initialize backend interfaces
	WindowManager wm = WindowManager(800, 500, "First window");
	Renderer renderer = Renderer();
	AudioManager audio = AudioManager();

	// Generate a 440 Hz sine wave
	int wave = audio.newWave(0);
	audio.setWaveAttribs(wave, 440, 0.5f);
	int wave2 = audio.newWave(1);
	audio.setWaveAttribs(wave2, 100, 0.1f);

	// Generate the textures
	// Yellow wave
	const void* textureData = TextureGenerator::wave(128, 128, 255, 255, 0);
	unsigned int waveTexture = renderer.loadTexture(128, 128, textureData);
	delete[] textureData;

	// Blue checkerboard
	textureData = TextureGenerator::checker(16, 16, 0, 0, 255);
	unsigned int checkerTexture = renderer.loadTexture(16, 16, textureData);
	delete[] textureData;

	// Shiny tiles
	textureData = TextureGenerator::shinyTile(512, 512);
	unsigned int tileTexture = renderer.loadTexture(512, 512, textureData);
	delete[] textureData;

	// Camera pos
	glm::vec2 cameraPosition = glm::vec2(0.0f);

	// Toggle variables
	bool fullscreenToggle = false;
	bool fullscreenTogglePressed = false;

	// Main loop
	audio.start();
	while (!wm.update()) {
		// Close the game on escape press
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

		// Control camera with WASD
		if (wm.getKey(GLFW_KEY_W)) cameraPosition.y += 1.0f * wm.getLastDeltaTime();
		if (wm.getKey(GLFW_KEY_A)) cameraPosition.x -= 1.0f * wm.getLastDeltaTime();
		if (wm.getKey(GLFW_KEY_S)) cameraPosition.y -= 1.0f * wm.getLastDeltaTime();
		if (wm.getKey(GLFW_KEY_D)) cameraPosition.x += 1.0f * wm.getLastDeltaTime();

		renderer.setCamera(cameraPosition, 0.0f, (float)wm.getHeight() / (float)wm.getWidth(), .5f);
		renderer.clear();
		// Test some sprites
		renderer.render(1.0f, -1.0f, 1.0f, 1.0f, 0.0f, tileTexture);
		renderer.render(1.0f, 0.0f, 1.0f, 1.0f, 0.0f, tileTexture);
		renderer.render(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, tileTexture);
		renderer.render(-1.0f, -1.0f, 1.0f, 1.0f, 0.0f, tileTexture);
		renderer.render(-1.0f, 0.0f, 1.0f, 1.0f, 0.0f, tileTexture);
		renderer.render(-1.0f, 1.0f, 1.0f, 1.0f, 0.0f, tileTexture);
		renderer.render(0.0f, -1.0f, 1.0f, 1.0f, 0.0f, checkerTexture);
		renderer.render(0.0f, 0.0f, 1.0f, 1.0f, 0.0f, checkerTexture);
		renderer.render(0.0f, 1.0f, 1.0f, 1.0f, 0.0f, checkerTexture);
		renderer.render(0.0f, 0.0f, 3.0f, 1.0f, -0.5f, waveTexture);
	}
	audio.stop();

	return 0;
}