#pragma once

class TextureGenerator {
	// Generate raw texture data
public:
	static const void* shinyTile(int width, int height);
	static const void* generateCircle(int width, int height);
};