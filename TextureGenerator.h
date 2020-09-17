#pragma once

class TextureGenerator {
	// Generate raw texture data
public:
	static const void* shinyTile(int width, int height);
	static const void* checker(int width, int height, int r, int g, int b);
	static const void* generateCircle(int width, int height);
	static const void* wave(int width, int height, int r, int g, int b);
};