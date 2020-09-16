#include <iostream>

#include <glad/glad.h>

#include "TextureGenerator.h"
#include "Renderer.h"
#include "WindowManager.h"

int main() {
	// Initialize window and renderer
	WindowManager wm = WindowManager(800, 500, "First window");
	Renderer renderer = Renderer();

	// Generate the forbidden texture
	const void* textureData = TextureGenerator::generateCircle(64, 64);
	unsigned int texture = renderer.loadTexture(64, 64, textureData);
	delete[] textureData;

	// Main loop
	int i = 0;
	while (!wm.update()) {
		renderer.clear();
		renderer.render(texture);
		i++;
		if (i == 600) {
			std::cout << "Going fullscreen" << std::endl;
			//wm.fullscreen(true);
		}
	}
	return 0;
}