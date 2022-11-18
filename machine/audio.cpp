#include "machine.hpp"

Wav::Wav(const std::string &s)
{
	std::string path{s + ".wav"};
	if (!SDL_LoadWAV(path.c_str(), &spec_, &buf_, &len_))
		throw std::runtime_error(std::string("SDL_LoadWAV failed! SDL Error: ") + SDL_GetError());

	dev_ = SDL_OpenAudioDevice(nullptr, 0, &spec_, nullptr, 0);
	if (!dev_)
		throw std::runtime_error(std::string("SDL_OpenAudioDevice failed! SDL Error: ") + SDL_GetError());
	SDL_PauseAudioDevice(dev_, 0);
}

/**
 * Close the object's audio device and free its audio buffer
 */
Wav::~Wav()
{
	SDL_CloseAudioDevice(dev_);
	SDL_FreeWAV(buf_);
}

/**
 * Queue audio to play once
 */
void Wav::play()
{
	if (SDL_QueueAudio(dev_, buf_, len_))
		throw std::runtime_error(std::string("SDL_QueueAudio failed! SDL Error: ") + SDL_GetError());
}

Mixer_Wav::Mixer_Wav(const std::string &s)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		throw std::runtime_error(Mix_GetError());

	std::string path{s + ".wav"};
	sound_ = Mix_LoadWAV(path.c_str());
	if(sound_ == NULL)
		throw std::runtime_error(std::string("Mix_LoadWAV failed! Mix Error: ") + Mix_GetError());
}

/**
 * Close the object's audio device and free chunk
 */
Mixer_Wav::~Mixer_Wav()
{
	Mix_FreeChunk(sound_);
	Mix_CloseAudio();
	Mix_Quit();
}

/**
 * Play sound bite in an available channel in a loop.
 * Audio loop stops when stop_loop() is called.
*/
void Mixer_Wav::start_loop()
{
	if(Mix_PlayChannel(-1, sound_, -1) == -1)
		throw std::runtime_error(std::string("Mix_PlayChannel failed! Mix Error: ") + Mix_GetError());
}

/**
 * Stops looping audio.
*/
void Mixer_Wav::stop_loop()
{
	if(Mix_HaltChannel(-1) == -1)
		throw std::runtime_error(std::string("Mix_HaltChannel failed! Mix Error: ") + Mix_GetError());
}

namespace space_invaders
{

/**
 * Plays the sounds corresponding to sound port values
 */
void Machine::play_sound()
{
	if (sound_port_3 != last_sound_3)
	{
		// UFO sounds (0.wav)
		if ((sound_port_3 & 0x1) && !(last_sound_3 & 0x1))
			ufo_.start_loop();
		else if (!(sound_port_3 & 0x1) && (last_sound_3 & 0x1))
			ufo_.stop_loop();

		// Player shot (1.wav)
		if ((sound_port_3 & 0x2) && !(last_sound_3 & 0x2))
			sounds_[0].play();

		// Player blown up (2.wav)
		if ((sound_port_3 & 0x4) && !(last_sound_3 & 0x4))
			sounds_[1].play();

		// Invader blown up (3.wav)
		if ((sound_port_3 & 0x8) && !(last_sound_3 & 0x8))
			sounds_[2].play();

		// Extra life (9.wav)
		if ((sound_port_3 & 0x10) && !(last_sound_3 & 0x10))
			sounds_[8].play();

		last_sound_3 = sound_port_3;
	}

	if (sound_port_5 != last_sound_5)
	{
		// Invader movement sound 1 (4.wav)
		if ((sound_port_5 & 0x1) && !(last_sound_5 & 0x1))
			sounds_[3].play();

		// Invader movement sound 2 (5.wav)
		if ((sound_port_5 & 0x2) && !(last_sound_5 & 0x2))
			sounds_[4].play();

		// Invader movement sound 3 (6.wav)
		if ((sound_port_5 & 0x4) && !(last_sound_5 & 0x4))
			sounds_[5].play();

		// Invader movement sound 4 (7.wav)
		if ((sound_port_5 & 0x8) && !(last_sound_5 & 0x8))
			sounds_[6].play();

		// UFO hit (8.wav)
		if ((sound_port_5 & 0x10) && !(last_sound_5 & 0x10))
			sounds_[7].play();

		last_sound_5 = sound_port_5;
	}
}
}
