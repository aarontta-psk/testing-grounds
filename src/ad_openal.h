#pragma once
#ifndef AUDIO_SYSTEM_AL_H
#define AUDIO_SYSTEM_AL_H

#include <stdint.h>
#include <string>

struct ALCdevice;
struct ALCcontext;
typedef unsigned int ALuint;

class AudioSystemAL {
public:
	enum class AudioDevice : uint8_t { AUDIO_DEVICE, CAPTURE_DEVICE }; 
	
	AudioSystemAL(const std::string& sndfile);
	~AudioSystemAL();

private:
	ALCdevice* audioDevice;
	ALCdevice* captureDevice;
	ALCcontext* audioContext;

	const char* currentDevices;

	void printSupportedFiles();
	bool checkExtensions();
	bool openAudioContext();

	ALuint openAudioFile(const char* file_path);
	void playAudio(const std::string& sndfile);

	void deleteAudioContext();
};
#endif // AUDIO_SYSTEM_AL_H