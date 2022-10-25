#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Some code cares that these flags are in exact
// right bits when.  For instance, some code
// "pops" values into the PSW that they didn't push.
//
typedef struct ConditionCodes
{
	uint8_t cy : 1;
	uint8_t pad : 1;
	uint8_t p : 1;
	uint8_t pad2 : 1;
	uint8_t ac : 1;
	uint8_t pad3 : 1;
	uint8_t z : 1;
	uint8_t s : 1;
} ConditionCodes;

/*
	Data structure representing the state of the registers
	and memory of the processor.
*/
typedef struct State8080
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
	struct ConditionCodes cc;
	uint8_t int_enable;

} State8080;

extern unsigned char cycles8080[];

int parity(int x, int size);
void LogicFlagsA(State8080 *state);
void ArithFlagsA(State8080 *state, uint16_t res);
void UnimplementedInstruction(State8080 *state);
void WriteMem(State8080 *state, uint16_t address, uint8_t value);
uint8_t ReadFromHL(State8080 *state);
void WriteToHL(State8080 *state, uint8_t value);
void Push(State8080 *state, uint8_t high, uint8_t low);
void Pop(State8080 *state, uint8_t *high, uint8_t *low);
void FlagsZSP(State8080 *state, uint8_t value);
void ReadFileIntoMemoryAt(State8080 *state, char *filename, uint32_t offset);
State8080 *Init8080(void);
