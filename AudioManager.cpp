#include "AudioManager.h"

#include <iostream>

AudioManager::AudioManager() {
	// Wrapper
	Pa_Initialize();

	// We shove all of our audio into one stream
	Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, 44100, paFramesPerBufferUnspecified, streamCallback, this);
}

AudioManager::~AudioManager() {
	// Wrapper
	Pa_Terminate();
}

void AudioManager::start() {
	// Wrapper
	Pa_StartStream(stream);
}

void AudioManager::stop() {
	// Wrapper
	Pa_StopStream(stream);
}

int AudioManager::newWave(int type) {
	// Create a new wave
	Wave w;
	w.type = type;
	w.x = 0.0f;
	w.dx = 0.0f;
	w.volume = 0.0f;
	wavesPlaying[newWaveIndex] = w;
	return newWaveIndex++;
}

void AudioManager::deleteWave(int wave) {
	// Remove wave key/value from map
	wavesPlaying.erase(wave);
}

void AudioManager::setWaveAttribs(int wave, int type, int frequency, float volume) {
	// Set some things that we don't need a calculation for
	wavesPlaying[wave].volume = volume;
	wavesPlaying[wave].type = type;

	// dx depends on the type of wave we're dealing with
	switch (wavesPlaying[wave].type) {
	case 0:
		// Sine wave
		wavesPlaying[wave].dx = 3.14159f * 2.0f * frequency / 44100.0f;
		break;
	case 1:
		// Square wave
		wavesPlaying[wave].dx = 2.0f * frequency / 44100.0f;
		break;
	case 2:
		// Sawtooth wave
		wavesPlaying[wave].dx = frequency / 44100.0f;
		break;
	}

}

float x;

int AudioManager::streamCallback(const void* input, void* output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData) {
	// Cast output to a float* so we can use it, then store it for backup
	float* out = (float*)output;
	float* startOfFrame = out;

	// Clear the output buffer
	for (unsigned long i = 0; i < frameCount; i++) {
		*(out++) = 0.0f;
	}
	
	// Iterate over the list of waves
	AudioManager* currentManager = (AudioManager*)userData;
	for (std::map<int, Wave>::iterator it = currentManager->wavesPlaying.begin(); it != currentManager->wavesPlaying.end(); it++) {
		if (it->second.volume <= 0.0f) continue;
		out = startOfFrame;
		for (unsigned long i = 0; i < frameCount; i++) {
			float intensity = 0.0f;
			it->second.x += it->second.dx;
			switch (it->second.type) {
			case 0:
				// Sine wave, just get the sin of x
				if (it->second.x >= 2.0f * 3.14159f) {
					it->second.x -= 2.0f * 3.14159f;
				}
				intensity = sinf(it->second.x);
				break;
			case 1:
				// Square wave, off from 0-1, on from 0-2
				if (it->second.x >= 2.0f) {
					it->second.x = 0.0f;
				}
				intensity = (int)it->second.x;
				break;
			case 2:
				// Sawtooth wave
				if (it->second.x > 1.0f) {
					it->second.x = 0.0f;
				}
				intensity = it->second.x;
				break;
			}
			// Output wave volume to audio buffer
			*(out++) += (intensity * it->second.volume);
		}
	}
	return 0;
}