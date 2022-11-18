#include "machine/machine.hpp"

int main(int argc, char *argv[])
{
	try
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
			throw std::runtime_error(SDL_GetError());
		space_invaders::Machine cabinet{};
		cabinet.load_program();
		cabinet.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what();
		exit(1);
	}
	SDL_Quit();
	return 0;
}
