#include "Loader.h"

#include <glad/glad.h>

Loader::Loader() : quadVAO(loadQuad()) {
	// Initialize quadVAO using an initializer list so Visual Studio won't yell at me
}

unsigned int Loader::getQuadVAO() {
	// Getter for quadVAO
	return quadVAO;
}

unsigned int Loader::loadTexture(int width, int height, const void* data) {
	// Generate a texture in VRAM
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	textures.push_back(texture);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// This is where we would use stbi load if we wanted to
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	return texture;
}

void Loader::cleanUp() {
	// Delete VBOs and VAOs from memory
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers((GLsizei)vbos.size(), vbos.data());
	glDeleteTextures((GLsizei)textures.size(), textures.data());
}

unsigned int Loader::loadQuad() {
	// Load a 1x1 quad into a VAO, since this engine is 2D that's the only vertex data we need
	float VERTICES[] = {
		-0.5f, 0.5f, // NW
		-0.5f, -0.5f, // SW
		0.5f, 0.5f, // NE
		0.5f, -0.5f // SE
	};
	float TEXTURE_COORDINATES[] = {
		0.0f, 1.0f, // NW
		0.0f, 0.0f, // SW
		1.0f, 1.0f, // NE
		1.0f, 0.0f // SE
	};
	// We can get away with not using an index buffer here because a quad can be drawn with triangle strips

	// Create a new VAO to hold all the relevant drawing info
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Upload vertex data to GPU memory
	unsigned int vBuffer = storeDataInVBO(VERTICES, sizeof(VERTICES));
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	unsigned int tcBuffer = storeDataInVBO(TEXTURE_COORDINATES, sizeof(TEXTURE_COORDINATES));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	
	// Enable buffers 0 and 1 (positions and textures)
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	return vao;
}

unsigned int Loader::storeDataInVBO(void* data, int size) {
	// Generate a VBO
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Store this to clean up later
	vbos.push_back(vbo);

	// Load the data into the buffer
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	return vbo;
}