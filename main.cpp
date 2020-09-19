#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <portaudio/portaudio.h>

#include "TextureGenerator.h"
#include "Renderer.h"
#include "WindowManager.h"

int squareWave = 0;

int paStreamCallback(const void* input, void* output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData) {
	// Cast output to a float* so we can use it
	float* out = (float*)output;
	std::cout << "Filling buffer: " << frameCount << std::endl;
	for (unsigned int i = 0; i < frameCount; i++) {
		squareWave++;
		float intensity = squareWave / 500;
		squareWave %= 1000;
		*(out++) = intensity;
		*(out++) = intensity; // Seems left and right are packed
	}
	return 0;
}

int main() {
	// Initialize PortAudio
	// TODO move this
	Pa_Initialize();

	// Open an audio stream
	// TODO move this
	PaStream* stream;
	Pa_OpenDefaultStream(&stream, 0, 2, paFloat32, 44100, paFramesPerBufferUnspecified, paStreamCallback, nullptr);

	// Start the audio stream
	// TODO move this
	auto paErr = Pa_StartStream(stream);
	if (paErr != paNoError) {
		std::cout << "PortAudio crashed!" << std::endl;
		return -1;
	}

	// Initialize window and renderer
	WindowManager wm = WindowManager(800, 500, "First window");
	Renderer renderer = Renderer();

	// Generate the textures
	// Yellow wave
	const void* textureData = TextureGenerator::wave(128, 128, 255, 255, 0);
	unsigned int waveTexture = renderer.loadTexture(128, 128, textureData);
	delete[] textureData;

	// Blue checkerboard
	textureData = TextureGenerator::checker(16, 16, 0, 0, 255);
	unsigned int checkerTexture = renderer.loadTexture(16, 16, textureData);
	delete[] textureData;

	// Shiny tiles
	textureData = TextureGenerator::shinyTile(512, 512);
	unsigned int tileTexture = renderer.loadTexture(512, 512, textureData);
	delete[] textureData;

	// Camera pos
	glm::vec2 cameraPosition = glm::vec2(0.0f);

	// Toggle variables
	bool fullscreenToggle = false;
	bool fullscreenTogglePressed = false;

	// Main loop
	while (!wm.update()) {
		// Close the game on escape press
		if (wm.getKey(GLFW_KEY_ESCAPE)) {
			break;
		}

		// Toggle fullscreen on F11 press
		if (wm.getKey(GLFW_KEY_F11)) {
			if (!fullscreenTogglePressed) {
				fullscreenToggle = !fullscreenToggle;
				wm.fullscreen(fullscreenToggle);
			}
			fullscreenTogglePressed = true;
		} else {
			fullscreenTogglePressed = false;
		}

		// Control camera with WASD
		if (wm.getKey(GLFW_KEY_W)) cameraPosition.y += 1.0f * wm.getLastDeltaTime();
		if (wm.getKey(GLFW_KEY_A)) cameraPosition.x -= 1.0f * wm.getLastDeltaTime();
		if (wm.getKey(GLFW_KEY_S)) cameraPosition.y -= 1.0f * wm.getLastDeltaTime();
		if (wm.getKey(GLFW_KEY_D)) cameraPosition.x += 1.0f * wm.getLastDeltaTime();

		renderer.setCamera(cameraPosition, 0.0f, (float)wm.getHeight() / (float)wm.getWidth(), .5f);
		renderer.clear();
		// Test some sprites
		renderer.render(1.0f, -1.0f, 1.0f, 1.0f, 0.0f, tileTexture);
		renderer.render(1.0f, 0.0f, 1.0f, 1.0f, 0.0f, tileTexture);
		renderer.render(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, tileTexture);
		renderer.render(-1.0f, -1.0f, 1.0f, 1.0f, 0.0f, tileTexture);
		renderer.render(-1.0f, 0.0f, 1.0f, 1.0f, 0.0f, tileTexture);
		renderer.render(-1.0f, 1.0f, 1.0f, 1.0f, 0.0f, tileTexture);
		renderer.render(0.0f, -1.0f, 1.0f, 1.0f, 0.0f, checkerTexture);
		renderer.render(0.0f, 0.0f, 1.0f, 1.0f, 0.0f, checkerTexture);
		renderer.render(0.0f, 1.0f, 1.0f, 1.0f, 0.0f, checkerTexture);
		renderer.render(0.0f, 0.0f, 3.0f, 1.0f, -0.5f, waveTexture);
	}

	// Terminate PortAudio
	// TODO move this
	Pa_StopStream(stream);
	Pa_Terminate();

	return 0;
}