#include "machine.hpp"

namespace space_invaders
{

Machine::Machine()
	: cpu_{init_8080()},
	  window_{
		  SDL_CreateWindow("Space Invaders!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE)},
	  surface_{
		  SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0)},
	  sounds_{
		  Wav("audio/0"),     // ufo moving (looping sound)
		  Wav("audio/1"),     // player shoot
		  Wav("audio/2"),     // player explode
		  Wav("audio/3"),     // invader explode
		  Wav("audio/4"),     // invader move 1
		  Wav("audio/5"),     // invader move 2
		  Wav("audio/6"),     // invader move 3
		  Wav("audio/7"),     // invader move 4
		  Wav("audio/8"),     // ufo hit
		  Wav("audio/9")      // extra life
	  }
{
	if (!cpu_)
		throw std::runtime_error("Could not create CPU!");
	if (!window_)
		throw std::runtime_error(std::string("SDL could not create window! SDL Error: ") + SDL_GetError());
	if (!surface_)
		throw std::runtime_error(std::string("SDL could not create surface! SDL Error: ") + SDL_GetError());
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
	constexpr double tic = 1000.0 / 60.0;      // ms per tic (1/60 second)
	constexpr int cycles_per_ms = 2000;        // assume CPU is 2 MHz
	constexpr double half_tic = tic / 2.0;     // ms between interrupts

	SDL_Event e;

	uint64_t now_tic = SDL_GetTicks64();
	uint64_t last_tic = now_tic;
	uint64_t next_int_tic = last_tic + tic;
	uint8_t next_int_num = 1;
	try
	{
		while (running_)
		{
			now_tic = SDL_GetTicks64();

			// check if it's time for an interrupt
			if ((cpu_->int_enable) && (now_tic > next_int_tic))
			{
				generate_interrupt(cpu_, next_int_num);
				next_int_num ^= 3;                     // switch between 1 and 2
				next_int_tic = now_tic + half_tic;     // next interrupt
			}

			// execute instructions until we catch up
			execute_cpu((now_tic - last_tic) * cycles_per_ms);
			last_tic = now_tic;

			// process any queued events
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
					running_ = false;
				else if (e.type == SDL_KEYDOWN)
					key_down(e.key.keysym.sym);
				else if (e.type == SDL_KEYUP)
					key_up(e.key.keysym.sym);
			}

			// update screen
			update_screen();
		}
	}
	catch(const std::exception& e)
	{
		free_machine();
		throw e;
	}

	free_machine();
}

/**
 * Read contents of ROM files into memory
 */
void Machine::load_program()
{
	read_file_into_memory_at(cpu_, (char *)"invaders/invaders.h", 0);
	read_file_into_memory_at(cpu_, (char *)"invaders/invaders.g", 0x800);
	read_file_into_memory_at(cpu_, (char *)"invaders/invaders.f", 0x1000);
	read_file_into_memory_at(cpu_, (char *)"invaders/invaders.e", 0x1800);
}

void Machine::free_machine()
{
	free_8080(cpu_);                // free cpu_
	SDL_DestroyWindow(window_);     // free window_
	SDL_FreeSurface(surface_);      // free surface_
	for (Wav sound : sounds_)       // free sounds_
		sound.~Wav();
}

}
