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

namespace space_invaders
{
	
void Machine::play_sound()
{
	if (sound1_ != last_sound1_) // bit changed
	{
		if ( (sound1_ & 0x2) && !(last_sound1_ & 0x2) )
			sounds_[1].play();
        if ( (sound1_ & 0x4) && !(last_sound1_ & 0x4) )
            sounds_[2].play();
        if ( (sound1_ & 0x8) && !(last_sound1_ & 0x8) )
			sounds_[3].play();
		last_sound1_ = sound1_;
	}
	if (sound2_ != last_sound2_)
	{
		if ( (sound2_ & 0x1) && !(last_sound2_ & 0x1) )
			sounds_[4].play();
		if ( (sound2_ & 0x2) && !(last_sound2_ & 0x2) )
			sounds_[5].play();
		if ( (sound2_ & 0x4) && !(last_sound2_ & 0x4) )
			sounds_[6].play();
		if ( (sound2_ & 0x8) && !(last_sound2_ & 0x8) )
			sounds_[7].play();
		if ( (sound2_ & 0x10) && !(last_sound2_ & 0x10) )
			sounds_[8].play();
		last_sound2_ = sound2_;
	}
}
}