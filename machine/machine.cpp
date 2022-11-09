#include "machine.hpp"

namespace space_invaders
{

Machine::Machine()
	: window_{
		  SDL_CreateWindow("Space Invaders!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE),
	  },
	  disp_{
		  SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0),
	  },
	  sounds_{
		  Wav("audio/0"),  // ufo moving (looping sound)
		  Wav("audio/1"),  // player shoot
		  Wav("audio/2"),  // player explode
		  Wav("audio/3"),  // invader explode
		  Wav("audio/4"),  // invader move 1
		  Wav("audio/5"),  // invader move 2
		  Wav("audio/6"),  // invader move 3
		  Wav("audio/7"),  // invader move 4
		  Wav("audio/8"),  // ufo hit
		  Wav("audio/9")   // extra life
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

/**
 * Execute CPU operation and update state accordingly.
 *
 * @param cyc_to_run the number of cycles to be executed
 */
void Machine::execute_cpu(uint64_t cyc_to_run)
{
	uint64_t cyc_ran = 0;
	while (cyc_ran < cyc_to_run)
	{
		uint8_t *opcode = &cpu_->memory[cpu_->pc];
		if (*opcode == 0xDB)     // machine handling for IN instruction
		{
			cpu_->a = in(opcode[1]);
			cpu_->pc += 2;
			cyc_ran += 3;
		}
		else if (*opcode == 0xD3)     // machine handling for OUT instruction
		{
			out(opcode[1], cpu_->a);
			cpu_->pc += 2;
			cyc_ran += 3;
		}
		else
			cyc_ran += emulate_8080_op(cpu_);
	}
}

/**
 * Runs the machine
 */
void Machine::run()
{
	constexpr double tic = 1000.0 / 60.0;
	constexpr double cycles_per_tic = 2000 * tic;

	SDL_Event e;
	uint64_t now_tic = SDL_GetTicks64();
	uint64_t last_tic = now_tic;
	uint64_t next_int_tic = last_tic + (cycles_per_tic / 2);
	uint8_t next_int_num = 1;

	while (!done_)
	{
		now_tic = SDL_GetTicks64();

		// check if it's time for an interrupt
		if ((cpu_->int_enable) && (now_tic > next_int_tic))
		{
			if (next_int_num == 1)
			{
				generate_interrupt(cpu_, 1);
				next_int_num = 2;
			}
			else
			{
				generate_interrupt(cpu_, 2);
				next_int_num = 1;
			}
			next_int_tic = now_tic + cycles_per_tic / 4;
		}

		// execute instructions until we catch up
		execute_cpu(2 * (now_tic - last_tic));
		last_tic = now_tic;

		// process any queued events
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				done_ = true;
			else if (e.type == SDL_KEYDOWN)
				key_down(e.key.keysym.sym);
			else if (e.type == SDL_KEYUP)
				key_up(e.key.keysym.sym);
		}

		// update screen
		update_screen();
	}
}

/**
 * Read contents of ROM files into memory
 */
void Machine::load_program()
{
	read_file_into_memory_at(cpu_, (char *)"../invaders/invaders.h", 0);
	read_file_into_memory_at(cpu_, (char *)"../invaders/invaders.g", 0x800);
	read_file_into_memory_at(cpu_, (char *)"../invaders/invaders.f", 0x1000);
	read_file_into_memory_at(cpu_, (char *)"../invaders/invaders.e", 0x1800);
}

}
