#include "machine.hpp"

namespace space_invaders
{

Machine::Machine()
	: cpu_{init_8080()}
	, window_{SDL_CreateWindow(SCREEN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE)}
	, surface_{SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0)}
	, audio_{Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 4096)}
	, sounds_{
		  Mixer_Wav("audio/0"),            // ufo on screen (looping sound)
		  Mixer_Wav("audio/1"),            // player shoot
		  Mixer_Wav("audio/2"),            // player explode
		  Mixer_Wav("audio/3"),            // invader explode
		  Mixer_Wav("audio/4"),            // invader move 1
		  Mixer_Wav("audio/5"),            // invader move 2
		  Mixer_Wav("audio/6"),            // invader move 3
		  Mixer_Wav("audio/7"),            // invader move 4
		  Mixer_Wav("audio/8"),            // ufo hit
		  Mixer_Wav("audio/9")             // extra life
	}
{
	if (!surface_)
		throw std::runtime_error(std::string("SDL could not create surface! SDL Error: ") + SDL_GetError());
	if (!window_)
		throw std::runtime_error(std::string("SDL could not create window! SDL Error: ") + SDL_GetError());
	if (audio_ == -1)
		throw std::runtime_error(std::string("SDL_Mixer could not open default audio device! Mix Error: ") + Mix_GetError());
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
			cyc_ran += 10;     // cycles for IN instruction
		}
		else if (*opcode == 0xD3)     // machine handling for OUT instruction
		{
			out(opcode[1], cpu_->a);
			cpu_->pc += 2;
			cyc_ran += 10;     // cycles for OUT instruction
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

	SDL_Event event;

	uint64_t now_tic = SDL_GetTicks();
	uint64_t last_tic = now_tic;
	uint64_t next_int_tic = last_tic + tic;
	uint8_t next_int_num = 1;

	while (running_)
	{
		// process any queued events
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				running_ = false;
			else if (event.type == SDL_KEYDOWN)
				key_down(event.key.keysym.sym);
			else if (event.type == SDL_KEYUP)
				key_up(event.key.keysym.sym);
		}

		// check if it's time for an interrupt
		if ((cpu_->int_enable) && (SDL_GetTicks() > next_int_tic))
		{
			if (next_int_num == 1)
				update_screen();     // draw screen every other interrupt (60Hz)

			generate_interrupt(cpu_, next_int_num);
			next_int_num ^= 3;
			next_int_tic += half_tic;     // next interrupt
		}

		now_tic = SDL_GetTicks();

		// execute instructions until we catch up
		execute_cpu((now_tic - last_tic) * cycles_per_ms);
		last_tic = now_tic;
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
/**
 * Frees machine memory
 */
void Machine::free_machine()
{
	for (int i = 0; i < 10; i++)        // free sounds_
		sounds_[i].~Mixer_Wav();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_FreeSurface(surface_);          // free surface_
	SDL_DestroyWindow(window_);         // free window_
	free_8080(cpu_);                    // free cpu_
}

}
