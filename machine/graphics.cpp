#include "machine.hpp"

namespace space_invaders
{

/**
 * Updates the screen
 */
void Machine::update_screen()
{
	if (SDL_MUSTLOCK(surface_))
		throw std::runtime_error("Error! Surface must be locked before reading/writing");
	uint32_t *pix = (uint32_t *)surface_->pixels;
	int i = 0x2400;     // start of video ram
	for (int col = 0; col < SCREEN_WIDTH; col++)
	{
		for (int row = SCREEN_HEIGHT; row > 0; row -= 8)
		{
			for (int j = 0; j < 8; j++)
			{
				int idx = (row - (j + 1)) * SCREEN_WIDTH + col;
				if (cpu_->memory[i] & (1 << j))
					pix[idx] = 0xFFFFFF;
				else
					pix[idx] = 0x000000;
			}
			i++;
		}
	}
	SDL_Surface *winsurf = SDL_GetWindowSurface(window_);
	if (!winsurf)
		throw std::runtime_error(std::string("SDL_GetWindowSurface failed! SDL Error: ") + SDL_GetError());
	if (SDL_BlitScaled(surface_, NULL, winsurf, NULL))
		throw std::runtime_error(std::string("SDL_BlitScaled failed! SDL Error: ") + SDL_GetError());
	if (SDL_UpdateWindowSurface(window_))
		throw std::runtime_error(std::string("SDL_UpdateWindowSurface failed! SDL Error: ") + SDL_GetError());
}

}
