#pragma once

#include "Loader.h"
#include "Shader.h"

class Renderer {
	// Abstract rendering operations away from the user
public:
	Renderer();
	~Renderer();
	void render(unsigned int texture);
	unsigned int loadTexture(int width, int height, const void* data);
	void clear();
private:
	unsigned int currentTex = 0;
	Loader loader;
	Shader shader;
};