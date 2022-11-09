#include "machine.hpp"

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
	if (sound_port_3 != last_sound_3) // bit changed
	{
		// UFO on screen
		if ( (sound_port_3 & 0x1) && !(last_sound_3 & 0x1) )
		{
			// TODO: UFO on screen (loop 0.wav)
		}
		else if ( !(out_port3 & 0x1) && (last_out_port3 & 0x1))    
		{
			// TODO: UFO not on screen (stop loop 0.wav)
		}
		}
		// Player shot
		if ( (sound_port_3 & 0x2) && !(last_sound_3 & 0x2) )
			sounds_[1].play();

		// Player blown up
        if ( (sound_port_3 & 0x4) && !(last_sound_3 & 0x4) )
            sounds_[2].play();

		// Invader blown up
        if ( (sound_port_3 & 0x8) && !(last_sound_3 & 0x8) )
			sounds_[3].play();
		
		// Extra life
        if ( (sound_port_3 & 0x10) && !(last_sound_3 & 0x10) )
			sounds_[9].play();

		last_sound_3 = sound_port_3;
	}

	if (sound_port_5 != last_sound_5)
	{
		// Invader movement sound 1
		if ( (sound_port_5 & 0x1) && !(last_sound_5 & 0x1) )
			sounds_[4].play();
		
		// Invader movement sound 2
		if ( (sound_port_5 & 0x2) && !(last_sound_5 & 0x2) )
			sounds_[5].play();
		
		// Invader movement sound 3
		if ( (sound_port_5 & 0x4) && !(last_sound_5 & 0x4) )
			sounds_[6].play();
		
		// Invader movement sound 4
		if ( (sound_port_5 & 0x8) && !(last_sound_5 & 0x8) )
			sounds_[7].play();
		
		// UFO hit
		if ( (sound_port_5 & 0x10) && !(last_sound_5 & 0x10) )
			sounds_[8].play();
		last_sound_5 = sound_port_5;
	}
}
