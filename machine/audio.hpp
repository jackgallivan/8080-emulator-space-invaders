#include <cstdint>
#include <string>
#include <SDL2/SDL_Mixer.h>     // for looping ufo audio

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
