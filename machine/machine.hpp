#include <array>        // for std::array
#include <iostream>     // for std::cerr
#include <SDL2/SDL.h>

extern "C"
{
#include "../emulator/emulator.h"
}

#define SCREEN_HEIGHT 256
#define SCREEN_WIDTH  224

namespace space_invaders
{

class Machine
{
public:
	Machine();
	void run();
	void load_program();
	void update_screen();

	uint8_t in(uint8_t);
	void out(uint8_t, uint8_t);
	void key_down(SDL_Keycode);
	void key_up(SDL_Keycode);

private:
	State_8080 *cpu_{init_8080()};

	uint8_t in_port1{0};
	uint8_t in_port2{0};
    uint8_t shift0{0};
    uint8_t shift1{0};
    uint8_t shift_offset{0};

	bool done_{false};
	std::array<std::array<std::array<uint8_t, 3>, SCREEN_WIDTH>, SCREEN_HEIGHT> screen_buf_{};
	SDL_Window *window_;
	SDL_Surface *disp_;

	void execute_cpu(uint64_t);
};

}
