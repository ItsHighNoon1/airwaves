#include "Renderer.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Loader.h"
#include "Shader.h"

Renderer::Renderer() {
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

void Renderer::render(float x, float y, float w, float h, float r, unsigned int texture) {
	// Generate a transformation matrix
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, r, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(w, h, 0.0f));

	// Calculate mvp matrix
	modelMatrix = projectionMatrix * (viewMatrix * modelMatrix);

	// Set the sprite texture
	if (currentTex != texture) {
		currentTex = texture;
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	// Render a sprite
	shader.start();
	shader.uploadMatrix(glm::value_ptr(modelMatrix));
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
