#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Some code cares that these flags are in exact
// right bits when.  For instance, some code
// "pops" values into the PSW that they didn't push.
//
typedef struct Condition_codes
{
	uint8_t cy : 1;
	uint8_t pad : 1;
	uint8_t p : 1;
	uint8_t pad2 : 1;
	uint8_t ac : 1;
	uint8_t pad3 : 1;
	uint8_t z : 1;
	uint8_t s : 1;
} Condition_codes;

/*
	Data structure representing the state of the registers
	and memory of the processor.
*/
typedef struct State_8080
{
	uint8_t a;
	uint8_t b;
	uint8_t c;
	uint8_t d;
	uint8_t e;
	uint8_t h;
	uint8_t l;
	uint16_t sp;
	uint16_t pc;
	uint8_t *memory;
	struct Condition_codes cc;
	uint8_t int_enable;

} State_8080;

extern unsigned char cycles_8080[];

int parity(int x, int size);
void logic_flags_a(State_8080 *state);
void arith_flags_a(State_8080 *state, uint16_t res);
void unimplemented_instruction(State_8080 *state);
void write_mem(State_8080 *state, uint16_t address, uint8_t value);
uint8_t read_from_hl(State_8080 *state);
void write_to_hl(State_8080 *state, uint8_t value);
void push(State_8080 *state, uint8_t high, uint8_t low);
void pop(State_8080 *state, uint8_t *high, uint8_t *low);
void flags_zsp(State_8080 *state, uint8_t value);
void read_file_into_memory_at(State_8080 *state, char *filename, uint32_t offset);
State_8080 *init_8080(void);
void free_8080(State_8080 *state);
