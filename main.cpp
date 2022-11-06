#include "machine/machine.hpp"

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		throw;
	}
	space_invaders::Machine cabinet {};
	cabinet.load_program();
	cabinet.run();
	SDL_Quit();
	return 0;
}
