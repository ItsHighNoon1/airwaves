#include "TextureGenerator.h"

const void* TextureGenerator::shinyTile(int width, int height) {
	// Generates triangular tiles
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

const void* TextureGenerator::generateCircle(int width, int height) {
	// TODO make a circle
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