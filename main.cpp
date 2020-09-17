#include <iostream>

#include <glad/glad.h>

#include "TextureGenerator.h"
#include "Renderer.h"
#include "WindowManager.h"

int main() {
	// Initialize window and renderer
	WindowManager wm = WindowManager(800, 500, "First window");
	Renderer renderer = Renderer();

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
	textureData = TextureGenerator::shinyTile(256, 256);
	unsigned int tileTexture = renderer.loadTexture(256, 256, textureData);
	delete[] textureData;

	// Main loop
	int i = 0;
	while (!wm.update()) {
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
		i++;
		if (i == 600) {
			std::cout << "Going fullscreen" << std::endl;
			//wm.fullscreen(true);
		}
	}
	return 0;
}