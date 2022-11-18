#include "machine.hpp"

#define KEY_COIN     SDLK_c
#define KEY_P2_START SDLK_2
#define KEY_P1_START SDLK_1
#define KEY_P1_FIRE  SDLK_w
#define KEY_P1_LEFT  SDLK_a
#define KEY_P1_RIGHT SDLK_d
#define KEY_P2_FIRE  SDLK_UP
#define KEY_P2_LEFT  SDLK_LEFT
#define KEY_P2_RIGHT SDLK_RIGHT

namespace space_invaders
{

/**
 * Reads the input port specified
 *
 * @param port the input port number to read from
 * @returns the value read from the specified input port.
 */
uint8_t Machine::in(uint8_t port)
{
	uint8_t read_val;
	uint16_t v;
	switch (port)
	{
		case 1:
			read_val = in_port1;
			break;

		case 2:
			read_val = in_port2;
			break;

		case 3:
			v = (shift1 << 8) | shift0;
			read_val = ((v >> (8 - shift_offset)) & 0xFF);
			break;

		default:
			throw std::runtime_error(std::string("Error: invalid in port ") + std::string(1, (char)port));
	}
	return read_val;
}

/**
 * Writes the shift value or shift offset value according
 * to the output port and value specified
 *
 * @param port the output port to write to
 * @param write_val the value to write
 */
void Machine::out(uint8_t port, uint8_t write_val)
{
	switch (port)
	{
		case 2:
			shift_offset = write_val & 0x7;
			break;

		case 3:
			sound_port_3 = write_val;
			break;

		case 4:
			shift0 = shift1;
			shift1 = write_val;
			break;

		case 5:
			sound_port_5 = write_val;
			break;

		default:
			break;
	}
	play_sound();
}

/**
 * Set input port bits for pressed key
 *
 * @param keycode the SDL virtual key being pressed
 */
void Machine::key_down(SDL_Keycode keycode)
{
	switch (keycode)
	{
		case KEY_COIN:     // Insert coin
			in_port1 |= 1;
			break;

		case KEY_P2_START:     // P2 start
			in_port1 |= 1 << 1;
			break;

		case KEY_P1_START:     // P1 start
			in_port1 |= 1 << 2;
			break;

		case KEY_P1_FIRE:     // P1 fire
			in_port1 |= 1 << 4;
			break;

		case KEY_P1_LEFT:     // P1 left
			in_port1 |= 1 << 5;
			break;

		case KEY_P1_RIGHT:     // P1 right
			in_port1 |= 1 << 6;
			break;

		case KEY_P2_FIRE:     // P2 fire
			in_port2 |= 1 << 4;
			break;

		case KEY_P2_LEFT:     // P2 left
			in_port2 |= 1 << 5;
			break;

		case KEY_P2_RIGHT:     // P2 right
			in_port2 |= 1 << 6;
			break;

		default:
			break;
	}
}

/**
 * Unset input port bits for released key
 *
 * @param keycode the SDL virtual key being released
 */
void Machine::key_up(SDL_Keycode keycode)
{
	switch (keycode)
	{
		case KEY_COIN:     // Insert coin
			in_port1 &= ~1;
			break;

		case KEY_P2_START:     // P2 start
			in_port1 &= ~(1 << 1);
			break;

		case KEY_P1_START:     // P1 start
			in_port1 &= ~(1 << 2);
			break;

		case KEY_P1_FIRE:     // P1 fire
			in_port1 &= ~(1 << 4);
			break;

		case KEY_P1_LEFT:     // P1 left
			in_port1 &= ~(1 << 5);
			break;

		case KEY_P1_RIGHT:     // P1 right
			in_port1 &= ~(1 << 6);
			break;

		case KEY_P2_FIRE:     // P2 fire
			in_port2 &= ~(1 << 4);
			break;

		case KEY_P2_LEFT:     // P2 left
			in_port2 &= ~(1 << 5);
			break;

		case KEY_P2_RIGHT:     // P2 right
			in_port2 &= ~(1 << 6);
			break;

		default:
			break;
	}
}

}
