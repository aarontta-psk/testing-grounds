#include "ad_openal.h"

#include <vector>
#include <iostream>
#include <fstream>

#include <sndfile.hh>

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"

AudioSystemAL::AudioSystemAL(const std::string& sndfile) {
	printSupportedFiles();
	checkExtensions();

	openAudioContext();

	playAudio(sndfile);
}

AudioSystemAL::~AudioSystemAL() {
	deleteAudioContext();
}

void AudioSystemAL::playAudio(const std::string& sndfile)
{
	ALuint audioBuffer = openAudioFile(sndfile.c_str());

	ALuint source;
	alGenSources(1, &source);

	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1.0f);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_FALSE);
	alSourcei(source, AL_BUFFER, audioBuffer);

	alSourcePlay(source);

	ALint state = AL_PLAYING;
	while (state == AL_PLAYING)
		alGetSourcei(source, AL_SOURCE_STATE, &state);

	alDeleteSources(1, &source);
	alDeleteBuffers(1, &audioBuffer);
}

bool AudioSystemAL::openAudioContext()
{
	if (!(audioDevice = alcOpenDevice(nullptr)))
		std::cerr << "ERROR: Could not create audio device" << std::endl;

	if (!(audioContext = alcCreateContext(audioDevice, nullptr)))
		std::cerr << "ERROR: Could not create audio context" << std::endl;

	if (!alcMakeContextCurrent(audioContext))
		std::cerr << "ERROR: Could not make audio context current" << std::endl;

	return true;
}

ALuint AudioSystemAL::openAudioFile(const char* filename)
{
	SndfileHandle audioFile = SndfileHandle(filename, SFM_READ);
	ALenum format = ((audioFile.channels() == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16);

	short* membuf = static_cast<short*>(malloc((size_t)(audioFile.frames() * audioFile.channels()) * sizeof(short)));
	sf_count_t num_frames = audioFile.readf(membuf, int(audioFile.frames()));
	ALsizei num_bytes = (ALsizei)(num_frames * audioFile.channels()) * (ALsizei)sizeof(short);

	ALuint audioBuffer;
	alGenBuffers(1, &audioBuffer);
	alBufferData(audioBuffer, format, membuf, num_bytes, audioFile.samplerate());

	free(membuf);

	return audioBuffer;
}

void AudioSystemAL::deleteAudioContext()
{
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(audioContext);

	alcCloseDevice(audioDevice);
}

void AudioSystemAL::printSupportedFiles()
{
	SF_FORMAT_INFO	info;
	SF_INFO 		sfinfo;
	int format, major_count, subtype_count, m, s;

	memset(&sfinfo, 0, sizeof(sfinfo));
	printf("Version : %s\n\n", sf_version_string());

	sf_command(NULL, SFC_GET_FORMAT_MAJOR_COUNT, &major_count, sizeof(int));
	sf_command(NULL, SFC_GET_FORMAT_SUBTYPE_COUNT, &subtype_count, sizeof(int));

	sfinfo.channels = 1;
	for (m = 0; m < major_count; m++)
	{
		info.format = m;
		sf_command(NULL, SFC_GET_FORMAT_MAJOR, &info, sizeof(info));
		printf("%s  (extension \"%s\")\n", info.name, info.extension);

		format = info.format;

		for (s = 0; s < subtype_count; s++)
		{
			info.format = s;
			sf_command(NULL, SFC_GET_FORMAT_SUBTYPE, &info, sizeof(info));

			format = (format & SF_FORMAT_TYPEMASK) | info.format;

			sfinfo.format = format;
			if (sf_format_check(&sfinfo))
				printf("   %s\n", info.name);
		};
		puts("");
	};
	puts("");
}

bool AudioSystemAL::checkExtensions()
{
	ALCboolean flag = alcIsExtensionPresent(nullptr, "ALC_ENUMERATION_EXT");
	if (!flag)
		std::cerr << "ERROR: Not extension something" << std::endl;
	else {
		const ALCchar* devices = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);
		const ALCchar* captureDevice = alcGetString(nullptr, ALC_CAPTURE_DEVICE_SPECIFIER);
		const ALCchar* defaultDeviceName = alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);
		const ALCchar* defaultCaptureDeviceName = alcGetString(nullptr, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER);
		std::cerr << devices << std::endl << defaultDeviceName << std::endl << captureDevice << std::endl << defaultCaptureDeviceName << std::endl;
	}
	return flag;
}