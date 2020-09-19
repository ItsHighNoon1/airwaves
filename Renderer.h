#pragma once

#include <glm/glm.hpp>

#include "Loader.h"
#include "Shader.h"

class Renderer {
	// Abstract rendering operations away from the user
public:
	Renderer();
	~Renderer();
	void render(float x, float y, float w, float h, float r, unsigned int texture);
	void setCamera(glm::vec2 pos, float rot, float aspectRatio, float size);
	unsigned int loadTexture(int width, int height, const void* data);
	void clear();
private:
	unsigned int currentTex = 0;
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	Loader loader = Loader();
	Shader shader = Shader();
};