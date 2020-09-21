#include "TextureGenerator.h"

#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

const void* TextureGenerator::shinyTile(int width, int height) {
	// Generates diamond tiles
	unsigned char* data = new unsigned char[width * height * 3];

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			// Index of the pixel we are currently writing
			int pixelIndex = (i + j * width) * 3;
			data[pixelIndex] = i + j;
			data[pixelIndex + 1] = i - j;
			data[pixelIndex + 2] = j - i;
		}
	}

	return data;
}

const void* TextureGenerator::checker(int width, int height, char r, char g, char b) {
	// Generates square tiles
	unsigned char* data = new unsigned char[width * height * 3];

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			// Calculate color of pixel
			int color = (i + j) % 2;

			// Index of the pixel we are currently writing
			int pixelIndex = (i + j * width) * 3;
			if (color) {
				data[pixelIndex] = r;
				data[pixelIndex + 1] = g;
				data[pixelIndex + 2] = b;
			} else {
				data[pixelIndex] = 1;
				data[pixelIndex + 1] = 1;
				data[pixelIndex + 2] = 1;
			}
		}
	}

	return data;
}

const void* TextureGenerator::circle(int width, int height, char r, char g, char b, int widthFactor) {
	// Generates a circle with some weird coloring
	unsigned char* data = new unsigned char[width * height * 3];
	
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			// Index of the pixel we are currently writing
			int pixelIndex = (i + j * width) * 3;
			int halfWidth = width / 2;
			int halfHeight = height / 2;
			int x = i - halfWidth;
			int y = j - halfHeight;
			int distanceFromEdge = halfWidth * halfHeight - (x * x + y * y);
			if (distanceFromEdge > 0 && distanceFromEdge < widthFactor) {
				data[pixelIndex] = r;
				data[pixelIndex + 1] = g;
				data[pixelIndex + 2] = b;
			} else {
				// Set it to black if we don't want anything there
				data[pixelIndex] = 0;
				data[pixelIndex + 1] = 0;
				data[pixelIndex + 2] = 0;
			}
		}
	}

	return data;
}

const void* TextureGenerator::sineWave(int width, int height, char r, char g, char b) {
	// Generates a sine wave
	unsigned char* data = new unsigned char[width * height * 3];

	// Fill the texture with transparent
	for (int i = 0; i < width * height * 3; i++) {
		data[i] = 0;
	}

	// Go over a sine wave and draw pixels
	float x = 0.0f;
	float twoPi = 2 * 3.14159f;
	float increment = twoPi / width / 10.0f;
	while (x < twoPi) {
		// Get x and calculate i
		x += increment;
		int i = x / twoPi * width;
		if (i >= width || i < 0) continue;

		// Find y and calculate j
		float y = sinf(x);
		y = y / 2.0f + 0.5f;
		int j = y * height;
		if (j >= height || j < 0) continue;

		// Set pixel
		int pixelIndex = (i + j * width) * 3;
		data[pixelIndex] = r;
		data[pixelIndex + 1] = g;
		data[pixelIndex + 2] = b;
	}

	return data;
}

const void* TextureGenerator::squareWave(int width, int height, char r, char g, char b) {
	// Generates a square wave
	unsigned char* data = new unsigned char[width * height * 3];

	// Fill the texture with transparent
	for (int i = 0; i < width * height * 3; i++) {
		data[i] = 0;
	}

	// Draw the vertical sections
	int pixelIndex;
	for (int i = 0; i < height; i++) {
		// Left
		pixelIndex = i * width * 3;
		data[pixelIndex] = r;
		data[pixelIndex + 1] = g;
		data[pixelIndex + 2] = b;

		// Middle
		pixelIndex = (width / 2 + i * width) * 3;
		data[pixelIndex] = r;
		data[pixelIndex + 1] = g;
		data[pixelIndex + 2] = b;
	}

	// Draw the horizontal sections
	for (int i = 0; i < width; i++) {
		pixelIndex = i * 3;
		if (i < width / 2) pixelIndex += 3 * width * (height - 1);
		data[pixelIndex] = r;
		data[pixelIndex + 1] = g;
		data[pixelIndex + 2] = b;
	}

	return data;
}

const void* TextureGenerator::sawWave(int width, int height, char r, char g, char b) {
	// Generates a sawtooth wave
	unsigned char* data = new unsigned char[width * height * 3];

	// Fill the texture with transparent
	for (int i = 0; i < width * height * 3; i++) {
		data[i] = 0;
	}

	// Draw diagonal section
	int pixelIndex;
	for (int i = 0; i < width; i++) {
		pixelIndex = (i + (i + height / 2) % height * width) * 3;
		data[pixelIndex] = r;
		data[pixelIndex + 1] = g;
		data[pixelIndex + 2] = b;
	}

	// Draw vertical section
	for (int i = 0; i < height; i++) {
		pixelIndex = (width / 2 + i * width) * 3;
		data[pixelIndex] = r;
		data[pixelIndex + 1] = g;
		data[pixelIndex + 2] = b;
	}

	return data;
}

const void* TextureGenerator::solidColor(int width, int height, char r, char g, char b) {
	// Generates a solid color
	unsigned char* data = new unsigned char[width * height * 3];

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			// Index of the pixel we are currently writing
			int pixelIndex = (i + j * width) * 3;
			data[pixelIndex] = r;
			data[pixelIndex + 1] = g;
			data[pixelIndex + 2] = b;
		}
	}

	return data;
}

const void* TextureGenerator::sky(int width, int height) {
	// Generates a solid color
	unsigned char* data = new unsigned char[width * height * 3];

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			// Index of the pixel we are currently writing
			int pixelIndex = (i + j * width) * 3;
			float gradient = (float)j / (float)height;
			data[pixelIndex] = 190 - 130 * gradient;
			data[pixelIndex + 1] = 220 - 100 * gradient;
			data[pixelIndex + 2] = 234 - 47 * gradient;
		}
	}

	return data;
}

const void* TextureGenerator::realTexture(int* width, int* height, const char* name) {
	// Wrapper
	return stbi_load(name, width, height, nullptr, 3);
}

void TextureGenerator::freeLoaded(const void* loadedTexture) {
	// Wrapper
	stbi_image_free((void*)loadedTexture);
}