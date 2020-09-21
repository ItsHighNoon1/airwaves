#pragma once

#include <map>

#include <portaudio/portaudio.h>

class AudioManager {
	// Manages PortAudio
public:
	AudioManager();
	~AudioManager();
	void start();
	void stop();
	void setVolume(float volume);
	int newWave(int type);
	void deleteWave(int wave);
	void setWaveAttribs(int wave, int type, int frequency, float volume);
private:
	struct Wave {
		int type;
		float x;
		float dx;
		float volume;
	};
	static int streamCallback(const void* input, void* output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData);
	int newWaveIndex = 0;
	float playbackVolume = 1.0f;
	std::map<int, Wave> wavesPlaying;
	PaStream* stream = nullptr;
};