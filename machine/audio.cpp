#include "audio.hpp"
#include <SDL.h>

Wav::Wav(const std::string &s)
	: spec_ {}, buf_ {nullptr}, len_ {0}
{
	std::string path {s + ".wav"};
	auto success {SDL_LoadWAV(path.c_str(), &spec_, &buf_, &len_)};
	if (success == NULL)
		SDL_Log("Failed to load WAV: %s", path.c_str(), SDL_GetError());
	SDL_AudioSpec obtained; // format obtained
	dev_ = SDL_OpenAudioDevice(nullptr, 0, &spec_, &obtained, 0);
	if (dev_ == 0)
		SDL_Log("Failed to open audio: %s", SDL_GetError());
}

Wav::~Wav()
{
	SDL_CloseAudioDevice(dev_);
	SDL_FreeWAV(buf_);
}

bool Wav::play()
{
	int success {SDL_QueueAudio(dev_, buf_, len_)};
	SDL_PauseAudioDevice(dev_, 0);
	return success;
}

void Wav::loop()
{
	
}