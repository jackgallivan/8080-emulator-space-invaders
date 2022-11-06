#include <SDL2/SDL.h>
#include <array>  // for std::array
#include <iostream>  // for std::cerr

extern "C" {
    #include "../emulator/emulator.h"
}

#define SCREEN_HEIGHT 256
#define SCREEN_WIDTH 224

namespace space_invaders
{
    class Machine
    {
        public:
        Machine();
        void run();
	    void load_program();
        void update_screen();

        private:
        State_8080 *cpu_ {init_8080()};

        bool done_ {false};
        std::array<std::array<std::array<uint8_t, 3>, SCREEN_WIDTH>, SCREEN_HEIGHT> screen_buf_ {};
        SDL_Window *window_;
        SDL_Surface *disp_;

        void execute_cpu();    // TODO: add cycles variable as a long
    };

}
