#include <cstdint>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_Mixer.h>     // for looping ufo audio

class Wav
{
public:
	explicit Wav(const std::string &s);
	~Wav();

	void play();

private:
	SDL_AudioSpec spec_{};
	SDL_AudioDeviceID dev_{};
	uint8_t *buf_{nullptr};
	uint32_t len_{0};
};

class Mixer_Wav
{
public:
	explicit Mixer_Wav(const std::string &s);
	~Mixer_Wav();

	void play();
	void start_loop();
	void stop_loop();

private:
	Mix_Chunk *sound_{};
};
