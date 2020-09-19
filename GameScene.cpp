#include "GameScene.h"

#include "TextureGenerator.h"

GameScene::GameScene(Renderer& renderer) {
	// Load textures
	const void* greenSineTexture = TextureGenerator::squareWave(16, 16, 0, 255, 0);
	greenSine = renderer.loadTexture(16, 16, greenSineTexture);
	delete[] greenSineTexture;
	const void* whiteTexture = TextureGenerator::solidColor(1, 1, 255, 255, 255);
	white = renderer.loadTexture(1, 1, whiteTexture);
	delete[] whiteTexture;
	const void* skyTexture = TextureGenerator::sky(1024, 1024);
	sky = renderer.loadTexture(1024, 1024, skyTexture);
	delete[] skyTexture;

	// Spawn some speed particles
	for (int i = 0; i < 100; i++) {
		speedLines.push_back(glm::vec2(35.0f * rand.randFloat() - 15.0f, 20.0f * rand.randFloat() - 10.0f));
	}
}

void GameScene::render(Renderer& renderer) {
	// Set camera positiom
	renderer.setCamera(glm::vec2(cameraX, cameraY), 0.0f, aspect, 0.1f);

	// Draw the sky
	renderer.render(cameraX, cameraY, 20.0f, 20.0f, 0.0f, sky);

	// Draw speed lines
	for (auto& particle : speedLines) {
		renderer.render(particle.x, particle.y, 1.0f, 0.1f, 0.0f, white);
	}

	// Wave
	for (int i = -10; i < 10; i++) {
		renderer.render(0.5f * i + wavePosition, 0.0f, 0.5f, 5.0f - fabs(0.5f * i + wavePosition), 0.0f, greenSine);
	}
}

void GameScene::update(AudioManager& am, WindowManager& wm) {
	// Calculate the camera aspect ratio based on screen size
	aspect = (float)wm.getWidth() / (float)wm.getHeight();

	// Move speed lines
	for (auto& particle : speedLines) {
		particle.x -= 30.0f * wm.getLastDeltaTime();
		if (particle.x < -15.0f) {
			particle.x = 15.0f + 5.0f * rand.randFloat();
			particle.y = 20.0f * rand.randFloat() - 10.0f;
		}
	}

	// Do some other stuff
	wavePosition += 5.0f * wm.getLastDeltaTime();
	if (wavePosition > 0.5f) {
		wavePosition -= 0.5f;
	}
}