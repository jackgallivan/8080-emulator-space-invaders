#include "machine.hpp"

namespace space_invaders
{
    Machine::Machine()
        : window_
        {
            SDL_CreateWindow("Space Invaders!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE)
        },
        disp_
        {
            SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0)
        }
    {
        if (!window_)
        {
            std::cerr << "Could not create SDL_Window!\n";
            throw;
        }
        if (!disp_)
        {
            std::cerr << "Could not create SDL_Surface!\n";
            throw;
        }
    }

    /*
        void Machine::execute_cpu()

        Execute CPU operation and update state accordingly.
        TODO: implement cycles in CPU code and machine code
    */
    void Machine::execute_cpu()
    {
        emulate_8080_op(cpu_);
    }

    /*
        void Machine::run()

        Runs the machine
    */
    void Machine::run()
    {
        while (!done_)
        {
            execute_cpu();
            update_screen();
        }
    }

    /*
        bool Machine::load_program(const std::string &in)

        Read contents of ROM files into memory
    */
    void Machine::load_program()
    {
        read_file_into_memory_at(cpu_, "../invaders/invaders.h", 0);
		read_file_into_memory_at(cpu_, "../invaders/invaders.g", 0x800);
		read_file_into_memory_at(cpu_, "../invaders/invaders.f", 0x1000);
		read_file_into_memory_at(cpu_, "../invaders/invaders.e", 0x1800);
    }
}
