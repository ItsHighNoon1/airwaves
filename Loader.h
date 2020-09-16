#pragma once

#include <vector>

class Loader {
	// Manage VRAM
public:
	Loader();
	unsigned int getQuadVAO();
	unsigned int loadTexture(int width, int height, const void* data);
	void cleanUp();
private:
	unsigned int loadQuad();
	unsigned int storeDataInVBO(void* data, int size);
	unsigned int quadVAO;
	std::vector<unsigned int> vbos;
	std::vector<unsigned int> textures;
};

