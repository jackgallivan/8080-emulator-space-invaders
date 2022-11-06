#include "machine.hpp"

namespace space_invaders
{
    void Machine::update_screen()
    {
        uint32_t *pix {(uint32_t *) disp_->pixels};
        int i {0x2400}; // start of video ram
        for (int col {0}; col < SCREEN_WIDTH; ++col)
        {
            for (int row {SCREEN_HEIGHT}; row > 0; row -= 8)
            {
                for (int j {0}; j < 8; ++j)
                {	
                    int idx = (row - j) * SCREEN_WIDTH + col;
                    if (cpu_.memory[i] & 1 << j)
                        pix[idx] = 0xFFFFFF;
                    else
                        pix[idx] = 0x000000;
                }
                ++i;
            }
        }
        SDL_Surface *winsurf = SDL_GetWindowSurface(window_);
        SDL_BlitScaled(disp_, NULL, winsurf, NULL);
        if (SDL_UpdateWindowSurface(window_))
            std::cerr << SDL_GetError();
    }
}
