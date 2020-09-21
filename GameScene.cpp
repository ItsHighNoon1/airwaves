#include "GameScene.h"

#include <string>

#include "TextureGenerator.h"

GameScene::GameScene(Renderer& renderer, AudioManager& audio, void (*exit)(int)) : endFunction(exit) {
	// Load textures
	// Waves
	const void* redSineData = TextureGenerator::sineWave(16, 16, 255, 0, 0);
	redSine = renderer.loadTexture(16, 16, redSineData);
	const void* greenSquareData = TextureGenerator::squareWave(16, 16, 0, 255, 0);
	greenSquare = renderer.loadTexture(16, 16, greenSquareData);
	const void* blueSawData = TextureGenerator::sawWave(16, 16, 0, 0, 255);
	blueSaw = renderer.loadTexture(16, 16, blueSawData);
	// Health bar quads
	const void* greenData = TextureGenerator::solidColor(1, 1, 0, 80, 0);
	green = renderer.loadTexture(1, 1, greenData);
	const void* redData = TextureGenerator::solidColor(1, 1, 80, 0, 0);
	red = renderer.loadTexture(1, 1, redData);
	// Background elements
	const void* whiteData = TextureGenerator::solidColor(1, 1, 255, 255, 255);
	white = renderer.loadTexture(1, 1, whiteData);
	const void* skyData = TextureGenerator::sky(256, 256);
	sky = renderer.loadTexture(256, 256, skyData);
	// Numbers
	int w;
	int h;
	const void* num0Data = TextureGenerator::realTexture(&w, &h, "res/0.png");
	num0 = renderer.loadTexture(w, h, num0Data);
	const void* num1Data = TextureGenerator::realTexture(&w, &h, "res/1.png");
	num1 = renderer.loadTexture(w, h, num1Data);
	const void* num2Data = TextureGenerator::realTexture(&w, &h, "res/2.png");
	num2 = renderer.loadTexture(w, h, num2Data);
	const void* num3Data = TextureGenerator::realTexture(&w, &h, "res/3.png");
	num3 = renderer.loadTexture(w, h, num3Data);
	const void* num4Data = TextureGenerator::realTexture(&w, &h, "res/4.png");
	num4 = renderer.loadTexture(w, h, num4Data);
	const void* num5Data = TextureGenerator::realTexture(&w, &h, "res/5.png");
	num5 = renderer.loadTexture(w, h, num5Data);
	const void* num6Data = TextureGenerator::realTexture(&w, &h, "res/6.png");
	num6 = renderer.loadTexture(w, h, num6Data);
	const void* num7Data = TextureGenerator::realTexture(&w, &h, "res/7.png");
	num7 = renderer.loadTexture(w, h, num7Data);
	const void* num8Data = TextureGenerator::realTexture(&w, &h, "res/8.png");
	num8 = renderer.loadTexture(w, h, num8Data);
	const void* num9Data = TextureGenerator::realTexture(&w, &h, "res/9.png");
	num9 = renderer.loadTexture(w, h, num9Data);

	// Clean up, if I clean up right after loading sometimes there will be a heap error
	delete[] redSineData;
	delete[] greenSquareData;
	delete[] blueSawData;
	delete[] greenData;
	delete[] redData;
	delete[] whiteData;
	delete[] skyData;
	// These textures were loaded with stbi, so they have different cleanup
	TextureGenerator::freeLoaded(num0Data);
	TextureGenerator::freeLoaded(num1Data);
	TextureGenerator::freeLoaded(num2Data);
	TextureGenerator::freeLoaded(num3Data);
	TextureGenerator::freeLoaded(num4Data);
	TextureGenerator::freeLoaded(num5Data);
	TextureGenerator::freeLoaded(num6Data);
	TextureGenerator::freeLoaded(num7Data);
	TextureGenerator::freeLoaded(num8Data);
	TextureGenerator::freeLoaded(num9Data);

	// Load audio
	playerSound = audio.newWave(0);

	// Spawn some speed particles
	for (int i = 0; i < 100; i++) {
		speedLines.push_back(glm::vec2(35.0f * rand.randFloat() - 15.0f, 20.0f * rand.randFloat() - 10.0f));
	}
}

void GameScene::init(int) {
	// Set some things to 0 for the next game
	secondTimer = 0.0f;
	speed = 20.0f;
	score = 0.0f;
	iFrames = 0.0f;
}

void GameScene::render(Renderer& renderer) {
	// Set camera positiom
	renderer.setCamera(glm::vec2(0.0f, 0.0f), 0.0f, aspect, cameraScale);

	// Draw the sky
	renderer.render(0.0f, 0.0f, 2.0f / cameraScale / aspect, 2.0f / cameraScale, 0.0f, sky);

	// Draw speed lines
	for (auto& particle : speedLines) {
		renderer.render(particle.x, particle.y, 1.0f, 0.05f, 0.0f, white);
	}

	// Player's wave
	renderer.setOffset(waveOffset);
	// If we're getting hit, blink the player
	if (iFrames < 0.0f || (int)(iFrames * 20.0f) % 2) {
		for (int i = 0; i < WAVELENGTH; i++) {
			// Draw the wave
			float waveWidth = 1.0f;
			float waveHeight = 2.0f * sinf(3.14159f * (float)i / (float)WAVELENGTH);
			float rot = 0.0f;
			if (i != 0) {
				waveWidth = wavePositions[i].x - wavePositions[i - 1].x;
				rot = atan2f(wavePositions[i].y - wavePositions[i - 1].y, waveWidth) / 4.0f;
			}

			// Different wave types
			switch (currentWaveType) {
			case 0:
				renderer.render(wavePositions[i].x - waveWidth / 2.0f, wavePositions[i].y, waveWidth, waveHeight, rot, redSine);
				break;
			case 1:
				renderer.render(wavePositions[i].x - waveWidth / 2.0f, wavePositions[i].y, waveWidth, waveHeight, rot, greenSquare);
				break;
			case 2:
				renderer.render(wavePositions[i].x - waveWidth / 2.0f, wavePositions[i].y, waveWidth, waveHeight, rot, blueSaw);
				break;
			}
		}
	}

	// Obstacle waves
	for (auto& wave : obstacles) {
		float x = wave.start.x;
		float y = wave.start.y;
		float dx = (wave.end.x - wave.start.x) / 10.0f;
		float dy = (wave.end.y - wave.start.y) / 10.0f;
		float d = sqrtf(dx * dx + dy * dy);
		float rot = atan2f(dy, dx);
		for (int i = 0; i < 11; i++) {
			switch (wave.type) {
			case 0:
				renderer.render(x, y, d, wave.width, rot, redSine);
				break;
			case 1:
				renderer.render(x, y, d, wave.width, rot, greenSquare);
				break;
			case 2:
				renderer.render(x, y, d, wave.width, rot, blueSaw);
				break;
			}
			x += dx;
			y += dy;
		}
	}
	renderer.setOffset(0.0f);

	// Health bar
	float lostHealth = 1.0f - health;
	renderer.render(-3.0f * lostHealth, 9.0f, 6.0f * health, 1.0f, 0.0f, green);
	renderer.render(3.0f * health, 9.0f, 6.0f * lostHealth, 1.0f, 0.0f, red);

	// Score
	std::string scoreString = std::to_string((int)score);
	scoreString.insert(scoreString.begin(), 10 - scoreString.length(), '0');
	float x = -2.5f;
	for (int i = 0; i <= 10; i++) {
		// Render the character
		switch (scoreString.c_str()[i]) {
			case '1': renderer.render(x, 8.0f, 0.5f, -0.5f, 0.0f, num1); break;
			case '2': renderer.render(x, 8.0f, 0.5f, -0.5f, 0.0f, num2); break;
			case '3': renderer.render(x, 8.0f, 0.5f, -0.5f, 0.0f, num3); break;
			case '4': renderer.render(x, 8.0f, 0.5f, -0.5f, 0.0f, num4); break;
			case '5': renderer.render(x, 8.0f, 0.5f, -0.5f, 0.0f, num5); break;
			case '6': renderer.render(x, 8.0f, 0.5f, -0.5f, 0.0f, num6); break;
			case '7': renderer.render(x, 8.0f, 0.5f, -0.5f, 0.0f, num7); break;
			case '8': renderer.render(x, 8.0f, 0.5f, -0.5f, 0.0f, num8); break;
			case '9': renderer.render(x, 8.0f, 0.5f, -0.5f, 0.0f, num9); break;
			default: renderer.render(x, 8.0f, 0.5f, -0.5f, 0.0f, num0);
		}
		x += 0.5f;
	}
}

void GameScene::update(AudioManager& am, WindowManager& wm) {
	// Calculate the camera aspect ratio based on screen size
	aspect = (float)wm.getWidth() / (float)wm.getHeight();

	// Get mouse position
	glm::vec2 mousePos = glm::vec2(0.0f, 0.0f);
	wm.getMousePos(&mousePos.x, &mousePos.y);
	if (mousePos.x > 1.0f) {
		mousePos.x = 1.0f;
	} else if (mousePos.x < -1.0f) {
		mousePos.x = -1.0f;
	}
	if (mousePos.y > 1.0f) {
		mousePos.y = 1.0f;
	} else if (mousePos.y < -1.0f) {
		mousePos.y = -1.0f;
	}
	mousePos.x /= cameraScale * aspect;
	mousePos.y /= cameraScale;

	// If a second has passed, tick the second function
	secondTimer += wm.getLastDeltaTime();
	if (secondTimer > 1.0f) {
		everySecond(am);
		secondTimer -= 1.0f;
	}

	// Move speed lines
	for (auto& particle : speedLines) {
		particle.x -= speed * wm.getLastDeltaTime();
		if (particle.x < -15.0f) {
			particle.x = 15.0f + 5.0f * rand.randFloat();
			particle.y = 20.0f * rand.randFloat() - 10.0f;
		}
	}

	// Recalculate wave
	for (int i = 0; i < WAVELENGTH - 1; i++) {
		wavePositions[i] = wavePositions[i + 1];
		wavePositions[i].x -= 2.0f * speed * wm.getLastDeltaTime();
	}
	wavePositions[WAVELENGTH - 1] = mousePos;

	// Wave offset so it looks like its rippling
	waveOffset -= 7.0f * wm.getLastDeltaTime();
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
	am.setWaveAttribs(playerSound, currentWaveType, 440 + (int)(330.0f * mousePos.y / 10.0f), 0.1f);
	
	for (auto& wave : obstacles) {
		// If the wave is offscreen, ignore it
		if (wave.start.x <= -30.0f) {
			am.setWaveAttribs(wave.audioWave, 0, 1, 0.0f);
			wave.type = -1;
			continue;
		}

		// Move the waves
		wave.start.x -= speed * wm.getLastDeltaTime();
		wave.end.x -= speed * wm.getLastDeltaTime();

		// Adjust wave sound
		if (wave.audioWave >= 0) {
			float volume = 20.0f - fabs(wave.start.x);
			volume *= 0.001f;
			am.setWaveAttribs(wave.audioWave, wave.type, 440 + (int)(330.0f * (wave.start.y + wave.end.y) / 20.0f), volume);
		}

		// Check if you are colliding with the wave
		if (iFrames < 0.0f) {
			glm::vec2 segmentVector = wave.end - wave.start;
			float length2 = segmentVector.x * segmentVector.x + segmentVector.y * segmentVector.y;
			float t = glm::max(0.0f, glm::min(1.0f, glm::dot(mousePos - wave.start, segmentVector) / length2));
			glm::vec2 proj = wave.start + t * segmentVector;
			if (glm::distance(mousePos, proj) < wave.width) {
				// You are colliding with the wave
				if (wave.type == currentWaveType) {
					health -= 0.334f;
					// If you have 0 health, die
					if (health <= 0.0f) {
						die(am);
						break;
					}
					iFrames = 1.0f;
				}
			}
		}
	}

	// Iterate over waves again, but this time destroy any waves that are offscreen
	for (int i = 0; i < obstacles.size(); i++) {
		if (obstacles[i].type == -1) {
			obstacles.erase(obstacles.begin() + i);
			break; // Less likely to break the program if we break and wait till next frame to deal with more
		}
	}

	// Play a sound while recovering from immunity
	iFrames -= wm.getLastDeltaTime();
	if (iFrames > 0.0f) {
		am.setWaveAttribs(playerSound, 2, 50, 0.1f);
	}

	// Since we haven't died, add to score
	score += 100.0f * speed * wm.getLastDeltaTime();
}

void GameScene::everySecond(AudioManager& am) {
	// Happens every second, spawn some enemies
	for (int i = 0; i < 5; i++) {
		BarrierWave wave;
		float x = 20.0f + speed * rand.randFloat();
		float y = 10.0f * rand.randFloat();
		if (rand.randInt(0, 1)) {
			wave.start = glm::vec2(x, y);
			wave.end = glm::vec2(x, y + 5.0f);
		} else {
			wave.start = glm::vec2(x, -y);
			wave.end = glm::vec2(x, -y - 5.0f);
		}
		wave.width = 1.0f;
		wave.type = rand.randInt(0, 2);
		wave.audioWave = am.newWave(wave.type);
		obstacles.push_back(wave);
		audioToCleanUp.push_back(wave.audioWave);
	}

	// Increase the sped
	speed += 0.1f;
}

void GameScene::die(AudioManager& am) {
	// Die
	health = 1.0f;
	obstacles.clear();
	stopSounds(am);
	endFunction(score);
}

void GameScene::stopSounds(AudioManager& am) {
	// Delete sounds
	am.stop();
	for (int& wave : audioToCleanUp) {
		am.deleteWave(wave);
	}
	audioToCleanUp.clear();
	am.setWaveAttribs(playerSound, 0, 1, 0.0f);
	am.start();
}