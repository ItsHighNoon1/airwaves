#include "Renderer.h"

#include <glad/glad.h>

#include "Loader.h"
#include "Shader.h"

Renderer::Renderer() : loader(Loader()), shader(Shader()) {
#ifdef _DEBUG
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
#else
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
#endif
}

Renderer::~Renderer() {
	// Clean up resources
	shader.cleanUp();
	loader.cleanUp();
}

void Renderer::render(unsigned int texture) {
	// Set the sprite texture
	if (currentTex != texture) {
		currentTex = texture;
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	// Render a sprite
	shader.start();
	glBindVertexArray(loader.getQuadVAO());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

unsigned int Renderer::loadTexture(int width, int height, const void* data) {
	// Wrapper
	return loader.loadTexture(width, height, data);
}

void Renderer::clear() {
	// Clear the screen, we don't need to clear depth buffer because it isn't real
	glClear(GL_COLOR_BUFFER_BIT);
}
