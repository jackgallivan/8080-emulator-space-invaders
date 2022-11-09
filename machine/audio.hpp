#include <SDL2/SDL.h>
#include <cstdint>
#include <string>

class Wav
{
	public:
	explicit Wav(const std::string &s);
	~Wav();
	
	bool play();
	void loop();
	
	private:
	SDL_AudioSpec spec_;
	SDL_AudioDeviceID dev_;
	uint8_t *buf_;
	uint32_t len_;
};
