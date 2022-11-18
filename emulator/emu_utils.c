#include "emu_utils.h"

// Number of cycles per instruction
// Referenced from Intel 8080 CPU User Manual
unsigned char cycles_8080[256] = {
	4, 10, 7, 5, 5, 5, 7, 4, 4, 10, 7, 5, 5, 5, 7, 4,       //0x00..0x0f
	4, 10, 7, 5, 5, 5, 7, 4, 4, 10, 7, 5, 5, 5, 7, 4,       //0x10..0x1f
	4, 10, 16, 5, 5, 5, 7, 4, 4, 10, 16, 5, 5, 5, 7, 4,     //etc
	4, 10, 13, 5, 10, 10, 10, 4, 4, 10, 13, 5, 5, 5, 7, 4,

	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5,     //0x40..0x4f
	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5,
	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5,
	7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 7, 5,     //0x70..0x7f

	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,     //0x80..8x4f
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,     //0xb0..0xbf

	11, 10, 10, 10, 17, 11, 7, 11, 11, 10, 10, 10, 10, 17, 7, 11,     //0xc0..0xcf
	11, 10, 10, 10, 17, 11, 7, 11, 11, 10, 10, 10, 10, 17, 7, 11,
	11, 10, 10, 18, 17, 11, 7, 11, 11, 5, 10, 5, 17, 17, 7, 11,
	11, 10, 10, 4, 17, 11, 7, 11, 11, 5, 10, 4, 17, 17, 7, 11,     //0xf0..0xff
};

/*
	parity:
	Sets parity flag when the input has an even parity and unsets it it has an odd parity
	x: integer value
	size: the size of the math instruction, in bits
	return: the value of the parity flag: 1 if set, 0 if unset
*/
int parity(int x, int size)
{
	int i;
	int p = 0;
	x = (x & ((1 << size) - 1));
	for (i = 0; i < size; i++)
	{
		if (x & 0x1) p++;
		x = x >> 1;
	}
	return (0 == (p & 0x1));
}

/*
	logic_flags_a:
	Update Zero, Sign, Parity, Carry and Auxiliary Carry flags upon using
	logical instructions
	state: state of registers and memory
*/
void logic_flags_a(State_8080 *state)
{
	state->cc.cy = state->cc.ac = 0;
	state->cc.z = (state->a == 0);
	state->cc.s = (0x80 == (state->a & 0x80));
	state->cc.p = parity(state->a, 8);
}

/*
	arith_flags_a:
	Update Zero, Sign and Parity flags upon updating A register using
	addition and subtraction instructions
	state: state of registers and memory
	res: result of arithmetic operation
*/
void arith_flags_a(State_8080 *state, uint16_t res)
{
	state->cc.cy = (res > 0xff);
	state->cc.z = ((res & 0xff) == 0);
	state->cc.s = (0x80 == (res & 0x80));
	state->cc.p = parity(res & 0xff, 8);
}

/*
	unimplemented_instruction:
	Generates error when an unimplemented instruction is found
	state: state of registers and memory
*/
void unimplemented_instruction(State_8080 *state)
{
	//pc will have advanced one, so undo that
	printf("Error: Unimplemented instruction\n");
	state->pc--;
	exit(1);
}

/*
	write_mem:
	Stores input value directly in specified memory location
	state: state of registers and memory
	address: direct location in memory
	value: value to store in memory
*/
void write_mem(State_8080 *state, uint16_t address, uint8_t value)
{
	if (address >= 0x2000 && address < 0x4000)
	{
		state->memory[address] = value;
	}
	else
	{
		printf("\n\tERROR: INVALID WRITE LOCATION");
		return;
	}
}

/*
	read_from_hl:
	Read value from memory
	state: state of registers and memory
*/
uint8_t read_from_hl(State_8080 *state)
{
	uint16_t offset = (state->h << 8) | state->l;
	return state->memory[offset];
}

/*
	write_to_hl:
	Write input value from memory
	state: state of registers and memory
	value: input value to write to memory
*/
void write_to_hl(State_8080 *state, uint8_t value)
{
	uint16_t offset = (state->h << 8) | state->l;
	write_mem(state, offset, value);
}

/*
	push:
	Push register pair into memory
	*state: state of registers and memory
	high: high bit register
	low: low bit register
*/
void push(State_8080 *state, uint8_t high, uint8_t low)
{
	write_mem(state, state->sp - 1, high);
	write_mem(state, state->sp - 2, low);
	state->sp = state->sp - 2;
}

/*
	pop:
	Pop topmost two bytes from the stack into the specified register pair
	*state: state of registers and memory
	*high: location of high bit register
	*low: location of low bit register
*/
void pop(State_8080 *state, uint8_t *high, uint8_t *low)
{
	*low = state->memory[state->sp];
	*high = state->memory[state->sp + 1];
	state->sp += 2;
}

/*
	flags_zsp:
	Update Zero, Sign and Parity flags upon adding immediate
	state: state of registers and memory
	value: ...
*/
void flags_zsp(State_8080 *state, uint8_t value)
{
	state->cc.z = (value == 0);
	state->cc.s = (0x80 == (value & 0x80));
	state->cc.p = parity(value, 8);
}

/*
	read_file_into_memory_at:
	Reads input file into processor memory
	state: state of registers and memory
	filename: name of the input file
	offset: location to read to in memory
*/
void read_file_into_memory_at(State_8080 *state, char *filename, uint32_t offset)
{
	FILE *f = fopen(filename, "rb");
	if (f == NULL)
	{
		printf("error: Couldn't open %s\n", filename);
		exit(1);
	}
	fseek(f, 0L, SEEK_END);
	int fsize = ftell(f);
	fseek(f, 0L, SEEK_SET);

	uint8_t *buffer = &state->memory[offset];
	fread(buffer, fsize, 1, f);
	fclose(f);
}

/*
	init_8080:
	Initialize the state of the registers and memory of the processor
*/
State_8080 *init_8080(void)
{
	State_8080 *state = calloc(1, sizeof(State_8080));
	state->memory = malloc(0x10000);     //16K
	return state;
}

void free_8080(State_8080 *state)
{
	free(state->memory);
	free(state);
}
