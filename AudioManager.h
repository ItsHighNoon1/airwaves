#pragma once

#include <map>

#include <portaudio/portaudio.h>

class AudioManager {
public:
	AudioManager();
	~AudioManager();
	void start();
	void stop();
	int newWave(int type);
	void setWaveAttribs(int wave, int frequency, float volume);
private:
	struct Wave {
		int type;
		float x;
		float dx;
		float volume;
	};
	static int streamCallback(const void* input, void* output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData);
	int newWaveIndex = 0;
	std::map<int, Wave> wavesPlaying;
	PaStream* stream = nullptr;
};