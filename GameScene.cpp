#include "GameScene.h"

#include "TextureGenerator.h"

GameScene::GameScene(Renderer& renderer, AudioManager& audio) {
	// Load textures
	// TODO there is a heap error happening here
	const void* textureData;
	// Red waves
	textureData = TextureGenerator::sineWave(16, 16, 255, 0, 0);
	redSine = renderer.loadTexture(16, 16, textureData);
	delete[] textureData;
	textureData = TextureGenerator::squareWave(16, 16, 255, 0, 0);
	redSquare = renderer.loadTexture(16, 16, textureData);
	delete[] textureData;
	textureData = TextureGenerator::sawWave(16, 16, 255, 0, 0);
	redSaw = renderer.loadTexture(16, 16, textureData);
	delete[] textureData;
	// Green waves
	textureData = TextureGenerator::sineWave(16, 16, 0, 255, 0);
	greenSine = renderer.loadTexture(16, 16, textureData);
	delete[] textureData;
	textureData = TextureGenerator::squareWave(16, 16, 0, 255, 0);
	greenSquare = renderer.loadTexture(16, 16, textureData);
	delete[] textureData;
	textureData = TextureGenerator::sawWave(16, 16, 0, 255, 0);
	greenSaw = renderer.loadTexture(16, 16, textureData);
	delete[] textureData;
	// Blue waves
	textureData = TextureGenerator::sineWave(16, 16, 0, 0, 255);
	blueSine = renderer.loadTexture(16, 16, textureData);
	delete[] textureData;
	textureData = TextureGenerator::squareWave(16, 16, 0, 0, 255);
	blueSquare = renderer.loadTexture(16, 16, textureData);
	delete[] textureData;
	textureData = TextureGenerator::sawWave(16, 16, 0, 0, 255);
	blueSaw = renderer.loadTexture(16, 16, textureData);
	delete[] textureData;
	// Background elements
	textureData = TextureGenerator::solidColor(1, 1, 255, 255, 255);
	white = renderer.loadTexture(1, 1, textureData);
	delete[] textureData;
	textureData = TextureGenerator::sky(16, 16);
	sky = renderer.loadTexture(16, 16, textureData);
	delete[] textureData;

	// Load audio
	playerSound = audio.newWave(0);

	// Spawn some speed particles
	for (int i = 0; i < 100; i++) {
		speedLines.push_back(glm::vec2(35.0f * rand.randFloat() - 15.0f, 20.0f * rand.randFloat() - 10.0f));
	}
}

void GameScene::render(Renderer& renderer) {
	// Set camera positiom
	renderer.setCamera(glm::vec2(cameraX, cameraY), 0.0f, aspect, cameraScale);

	// Draw the sky
	renderer.render(cameraX, cameraY, 2.0f / cameraScale / aspect, 2.0f / cameraScale, 0.0f, sky);

	// Draw speed lines
	for (auto& particle : speedLines) {
		renderer.render(particle.x, particle.y, 1.0f, 0.1f, 0.0f, white);
	}

	// Player's wave
	renderer.setOffset(waveOffset);
	for (int i = 0; i < WAVELENGTH; i++) {
		float waveWidth = 1.0f;
		float waveHeight = 2.0f * sinf(3.14159f * (float)i / (float)WAVELENGTH);
		float rot = 0.0f;
		if (i != 0) {
			waveWidth = wavePositions[i].x - wavePositions[i - 1].x;
			rot = atan2f(wavePositions[i].y - wavePositions[i - 1].y, wavePositions[i].x - wavePositions[i - 1].x);
		}

		// Different wave types
		switch (currentWaveType) {
		case 0:
			renderer.render(wavePositions[i].x - waveWidth / 2.0f, wavePositions[i].y, waveWidth, waveHeight, rot, greenSine);
			break;
		case 1:
			renderer.render(wavePositions[i].x - waveWidth / 2.0f, wavePositions[i].y, waveWidth, waveHeight, rot, greenSquare);
			break;
		case 2:
			renderer.render(wavePositions[i].x - waveWidth / 2.0f, wavePositions[i].y, waveWidth, waveHeight, rot, greenSaw);
			break;
		}
	}
}

void GameScene::update(AudioManager& am, WindowManager& wm) {
	// Calculate the camera aspect ratio based on screen size
	aspect = (float)wm.getWidth() / (float)wm.getHeight();

	// Get mouse position
	float x;
	float y;
	wm.getMousePos(&x, &y);
	x /= cameraScale * aspect;
	y /= cameraScale;

	// Move speed lines
	for (auto& particle : speedLines) {
		particle.x -= 30.0f * wm.getLastDeltaTime();
		if (particle.x < -15.0f) {
			particle.x = 15.0f + 5.0f * rand.randFloat();
			particle.y = 20.0f * rand.randFloat() - 10.0f;
		}
	}

	// Recalculate wave
	for (int i = 0; i < WAVELENGTH - 1; i++) {
		wavePositions[i] = wavePositions[i + 1];
		wavePositions[i].x -= 60.0f * wm.getLastDeltaTime();
	}
	wavePositions[WAVELENGTH - 1] = glm::vec2(x, y);

	// Wave offset so it looks like its rippling
	waveOffset += 10.0f * wm.getLastDeltaTime();
	if (waveOffset > 1.0f) {
		waveOffset -= 1.0f;
	}

	// Update the wave type and sound
	if (wm.getMouseButton(GLFW_MOUSE_BUTTON_1)) {
		currentWaveType = 1;
	} else if (wm.getMouseButton(GLFW_MOUSE_BUTTON_2)) {
		currentWaveType = 2;
	} else {
		currentWaveType = 0;
	}
	am.setWaveAttribs(playerSound, currentWaveType, 440 + 300 * y / 10.0f, 0.1f);
}