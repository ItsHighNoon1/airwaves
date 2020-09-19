#pragma once

class TextureGenerator {
	// Generate raw texture data
public:
	static const void* shinyTile(int width, int height);
	static const void* checker(int width, int height, int r, int g, int b);
	static const void* circle(int width, int height, int r, int g, int b, int widthFactor);
	static const void* sineWave(int width, int height, int r, int g, int b);
	static const void* squareWave(int width, int height, int r, int g, int b);
	static const void* sawWave(int width, int height, int r, int g, int b);
	static const void* solidColor(int width, int height, int r, int g, int b);
	static const void* sky(int width, int height);
};