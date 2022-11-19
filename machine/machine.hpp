#include "audio.hpp"
#include <array>        // for std::array
#include <iostream>     // for std::cerr
#include <SDL2/SDL.h>

extern "C"
{
#include "../emulator/emulator.h"
}

#define SCREEN_HEIGHT 256
#define SCREEN_WIDTH  224
#define SCREEN_TITLE "Space Invaders"

namespace space_invaders
{

class Machine
{
public:
	Machine();
	void run();
	void load_program();

private:
	State_8080 *cpu_;
	SDL_Window *window_;
	SDL_Surface *surface_;
	int audio_;
	std::array<Mixer_Wav, 10> sounds_;

	bool running_{true};

	// I/O ports
	uint8_t in_port1{0}, in_port2{0};
	uint8_t shift0{0}, shift1{0}, shift_offset{0};
	uint8_t sound_port_3{0}, last_sound_3{0};
	uint8_t sound_port_5{0}, last_sound_5{0};

	void execute_cpu(uint64_t cyc_to_run);
	uint8_t in(uint8_t port);
	void out(uint8_t port, uint8_t write_val);
	void key_down(SDL_Keycode keycode);
	void key_up(SDL_Keycode keycode);
	void update_screen();
	void play_sound();
	void free_machine();
};

}
