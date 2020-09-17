#include "TextureGenerator.h"

#include <math.h>

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

const void* TextureGenerator::checker(int width, int height, int r, int g, int b) {
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

const void* TextureGenerator::generateCircle(int width, int height) {
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
			if (x * x + y * y < halfWidth * halfHeight) {
				data[pixelIndex] = x * y;
				data[pixelIndex + 1] = x * y + 85;
				data[pixelIndex + 2] = x * y + 170;
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

const void* TextureGenerator::wave(int width, int height, int r, int g, int b) {
	// Generates a wave
	unsigned char* data = new unsigned char[width * height * 3];

	// Fill the texture with transparent
	for (int i = 0; i < width * height * 3; i++) {
		data[i] = 0;
	}

	// Go over a sin wave and draw pixels
	float x = 0.0f;
	float twoPi = 2 * 3.14159f;
	float increment = twoPi / width / 10.0f;
	while (x < twoPi) {
		// Get x and calculate i
		x += increment;
		int i = x / twoPi * width;
		if (i > width) continue;

		// Find y and calculate j
		float y = sinf(x);
		y = y / 2.0f + 0.5f;
		int j = y * height;
		if (j > height) continue;

		// Set pixel
		int pixelIndex = (i + j * width) * 3;
		data[pixelIndex] = r;
		data[pixelIndex + 1] = g;
		data[pixelIndex + 2] = b;
	}

	return data;
}