/*
	#define PRINTOPS: print every emulated opcode instruction
	#define PRINTPSW: print PSW after every emulated instruction
*/
#include "emulator.h"

#ifdef PRINTOPS
#include "../disassembler/disassembler.h"
#endif

int emulate_8080_op(State_8080 *state)
{
	uint8_t *opcode = &state->memory[state->pc];

	uint8_t data8, reg_1, reg_2;
	uint16_t data16, offset;
	uint32_t data32, reg_pair_1, reg_pair_2;

	uint8_t alt_cycles = 0;

#ifdef PRINTOPS
	disassemble_8080_op(state->memory, state->pc);
#ifndef PRINTPSW
	printf("\n");
#else
	printf("\t");
#endif
#endif

	state->pc++;

	switch (*opcode)
	{

		/* DATA TRANSFER GROUP */

		// MOV r1,r2 - Move between registers
		case 0x7F: state->a = state->a; break;     // MOV A,A
		case 0x78: state->a = state->b; break;     // MOV A,B
		case 0x79: state->a = state->c; break;     // MOV A,C
		case 0x7A: state->a = state->d; break;     // MOV A,D
		case 0x7B: state->a = state->e; break;     // MOV A,E
		case 0x7C: state->a = state->h; break;     // MOV A,H
		case 0x7D: state->a = state->l; break;     // MOV A,L
		case 0x47: state->b = state->a; break;     // MOV B,A
		case 0x40: state->b = state->b; break;     // MOV B,B
		case 0x41: state->b = state->c; break;     // MOV B,C
		case 0x42: state->b = state->d; break;     // MOV B,D
		case 0x43: state->b = state->e; break;     // MOV B,E
		case 0x44: state->b = state->h; break;     // MOV B,H
		case 0x45: state->b = state->l; break;     // MOV B,L
		case 0x4F: state->c = state->a; break;     // MOV C,A
		case 0x48: state->c = state->b; break;     // MOV C,B
		case 0x49: state->c = state->c; break;     // MOV C,C
		case 0x4A: state->c = state->d; break;     // MOV C,D
		case 0x4B: state->c = state->e; break;     // MOV C,E
		case 0x4C: state->c = state->h; break;     // MOV C,H
		case 0x4D: state->c = state->l; break;     // MOV C,L
		case 0x57: state->d = state->a; break;     // MOV D,A
		case 0x50: state->d = state->b; break;     // MOV D,B
		case 0x51: state->d = state->c; break;     // MOV D,C
		case 0x52: state->d = state->d; break;     // MOV D,D
		case 0x53: state->d = state->e; break;     // MOV D,E
		case 0x54: state->d = state->h; break;     // MOV D,H
		case 0x55: state->d = state->l; break;     // MOV D,L
		case 0x5F: state->e = state->a; break;     // MOV E,A
		case 0x58: state->e = state->b; break;     // MOV E,B
		case 0x59: state->e = state->c; break;     // MOV E,C
		case 0x5A: state->e = state->d; break;     // MOV E,D
		case 0x5B: state->e = state->e; break;     // MOV E,E
		case 0x5C: state->e = state->h; break;     // MOV E,H
		case 0x5D: state->e = state->l; break;     // MOV E,L
		case 0x67: state->h = state->a; break;     // MOV H,A
		case 0x60: state->h = state->b; break;     // MOV H,B
		case 0x61: state->h = state->c; break;     // MOV H,C
		case 0x62: state->h = state->d; break;     // MOV H,D
		case 0x63: state->h = state->e; break;     // MOV H,E
		case 0x64: state->h = state->h; break;     // MOV H,H
		case 0x65: state->h = state->l; break;     // MOV H,L
		case 0x6F: state->l = state->a; break;     // MOV L,A
		case 0x68: state->l = state->b; break;     // MOV L,B
		case 0x69: state->l = state->c; break;     // MOV L,C
		case 0x6A: state->l = state->d; break;     // MOV L,D
		case 0x6B: state->l = state->e; break;     // MOV L,E
		case 0x6C: state->l = state->h; break;     // MOV L,H
		case 0x6D: state->l = state->l; break;     // MOV L,L

		// MOV r,M - Move from memory to register
		case 0x7E: state->a = read_from_hl(state); break;     // MOV A,M
		case 0x46: state->b = read_from_hl(state); break;     // MOV B,M
		case 0x4E: state->c = read_from_hl(state); break;     // MOV C,M
		case 0x56: state->d = read_from_hl(state); break;     // MOV D,M
		case 0x5E: state->e = read_from_hl(state); break;     // MOV E,M
		case 0x66: state->h = read_from_hl(state); break;     // MOV H,M
		case 0x6E: state->l = read_from_hl(state); break;     // MOV L,M

		// MOV M,r - Move to memory from register
		case 0x77: write_to_hl(state, state->a); break;     // MOV M,A
		case 0x70: write_to_hl(state, state->b); break;     // MOV M,B
		case 0x71: write_to_hl(state, state->c); break;     // MOV M,C
		case 0x72: write_to_hl(state, state->d); break;     // MOV M,D
		case 0x73: write_to_hl(state, state->e); break;     // MOV M,E
		case 0x74: write_to_hl(state, state->h); break;     // MOV M,H
		case 0x75: write_to_hl(state, state->l); break;     // MOV M,L

		// MVI r,data - Move to register immediate
		case 0x3E:     // MVI A,data
			state->a = opcode[1];
			state->pc++;
			break;
		case 0x06:     // MVI B,data
			state->b = opcode[1];
			state->pc++;
			break;
		case 0x0E:     // MVI C,data
			state->c = opcode[1];
			state->pc++;
			break;
		case 0x16:     // MVI D,data
			state->d = opcode[1];
			state->pc++;
			break;
		case 0x1E:     // MVI E,data
			state->e = opcode[1];
			state->pc++;
			break;
		case 0x26:     // MVI H,data
			state->h = opcode[1];
			state->pc++;
			break;
		case 0x2E:     // MVI L,data
			state->l = opcode[1];
			state->pc++;
			break;

		// MVI M,data - Move to memory immediate
		case 0x36:     // MVI M,data
			write_to_hl(state, opcode[1]);
			state->pc++;
			break;

		// LXI rp,data16 - Load register pair immediate
		case 0x01:     // LXI B,data16
			state->b = opcode[2];
			state->c = opcode[1];
			state->pc += 2;
			break;
		case 0x11:     // LXI D,data16
			state->d = opcode[2];
			state->e = opcode[1];
			state->pc += 2;
			break;
		case 0x21:     // LXI H,data16
			state->h = opcode[2];
			state->l = opcode[1];
			state->pc += 2;
			break;
		case 0x31:     // LXI SP,data16
			state->sp = (opcode[2] << 8) | opcode[1];
			state->pc += 2;
			break;

		// LDA addr - Load accumulator direct
		case 0x3A:     // LDA addr
			offset = (opcode[2] << 8) | (opcode[1]);
			state->a = state->memory[offset];
			state->pc += 2;
			break;

		// STA addr - Store accumulator direct
		case 0x32:     // STA addr
			offset = (opcode[2] << 8) | (opcode[1]);
			write_mem(state, offset, state->a);
			state->pc += 2;
			break;

		// LHLD addr - Load H and L direct
		case 0x2A:     // LHLD addr
			offset = opcode[1] | (opcode[2] << 8);
			state->l = state->memory[offset];
			state->h = state->memory[offset + 1];
			state->pc += 2;
			break;

		// SHLD addr - Store H and L direct
		case 0x22:     // SHLD addr
			offset = opcode[1] | (opcode[2] << 8);
			write_mem(state, offset, state->l);
			write_mem(state, offset + 1, state->h);
			state->pc += 2;
			break;

		// LDAX rp - Load accumulator indirect
		case 0x0A:     // LDAX B
			offset = (state->b << 8) | state->c;
			state->a = state->memory[offset];
			break;
		case 0x1A:     // LDAX D
			offset = (state->d << 8) | state->e;
			state->a = state->memory[offset];
			break;

		// STAX rp - Store accumulator indirect
		case 0x02:     // STAX B
			offset = (state->b << 8) | state->c;
			write_mem(state, offset, state->a);
			break;
		case 0x12:     // STAX D
			offset = (state->d << 8) | state->e;
			write_mem(state, offset, state->a);
			break;

		// XCHG - Exchange H and L with D and E
		case 0xEB:     // XCHG
			reg_1 = state->d;
			reg_2 = state->e;
			state->d = state->h;
			state->e = state->l;
			state->h = reg_1;
			state->l = reg_2;
			break;

		/* ARITHMETIC GROUP */

		// ADD r - Add register
		case 0x87:     // ADD A
			data16 = (uint16_t)state->a + (uint16_t)state->a;
			// state->cc.ac = (state->a & 0x0f) + (state->a & 0x0f) > 0x0f ? 1 : 0;
			state->cc.ac = ((state->a & 0x0f) + (state->a & 0x0f)) > 0x0f;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x80:     // ADD B
			data16 = (uint16_t)state->a + (uint16_t)state->b;
			state->cc.ac = ((state->a & 0x0f) + (state->b & 0x0f)) > 0x0f;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x81:     // ADD C
			data16 = (uint16_t)state->a + (uint16_t)state->c;
			state->cc.ac = ((state->a & 0x0f) + (state->c & 0x0f)) > 0x0f;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x82:     // ADD D
			data16 = (uint16_t)state->a + (uint16_t)state->d;
			state->cc.ac = ((state->a & 0x0f) + (state->d & 0x0f)) > 0x0f;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x83:     // ADD E
			data16 = (uint16_t)state->a + (uint16_t)state->e;
			state->cc.ac = ((state->a & 0x0f) + (state->e & 0x0f)) > 0x0f;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x84:     // ADD H
			data16 = (uint16_t)state->a + (uint16_t)state->h;
			state->cc.ac = ((state->a & 0x0f) + (state->h & 0x0f)) > 0x0f;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x85:     // ADD L
			data16 = (uint16_t)state->a + (uint16_t)state->l;
			state->cc.ac = ((state->a & 0x0f) + (state->l & 0x0f)) > 0x0f;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;

		// ADD M - Add memory
		case 0x86:     // ADD M
			data8 = read_from_hl(state);
			data16 = (uint16_t)state->a + (uint16_t)data8;
			state->cc.ac = ((state->a & 0x0f) + (data8 & 0x0f)) > 0x0f;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;

		// ADI data - Add immediate
		case 0xC6:     // ADI data
			data8 = opcode[1];
			data16 = (uint16_t)state->a + (uint16_t)data8;
			state->cc.ac = ((state->a & 0x0f) + (data8 & 0x0f)) > 0x0f;
			flags_zsp(state, data16 & 0xff);
			state->cc.cy = (data16 > 0xff);
			state->a = data16 & 0xff;
			state->pc++;
			break;

		// ADC r - Add register with carry
		case 0x8F:     // ADC A
			data16 = (uint16_t)state->a + (uint16_t)state->a + state->cc.cy;
			state->cc.ac = ((state->a & 0x0f) + (state->a & 0x0f) + state->cc.cy) > 0x0f;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x88:     // ADC B
			data16 = (uint16_t)state->a + (uint16_t)state->b + state->cc.cy;
			state->cc.ac = ((state->a & 0x0f) + (state->b & 0x0f) + state->cc.cy) > 0x0f;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x89:     // ADC C
			data16 = (uint16_t)state->a + (uint16_t)state->c + state->cc.cy;
			state->cc.ac = ((state->a & 0x0f) + (state->c & 0x0f) + state->cc.cy) > 0x0f;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x8A:     // ADC D
			data16 = (uint16_t)state->a + (uint16_t)state->d + state->cc.cy;
			state->cc.ac = ((state->a & 0x0f) + (state->d & 0x0f) + state->cc.cy) > 0x0f;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x8B:     // ADC E
			data16 = (uint16_t)state->a + (uint16_t)state->e + state->cc.cy;
			state->cc.ac = ((state->a & 0x0f) + (state->e & 0x0f) + state->cc.cy) > 0x0f;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x8C:     // ADC H
			data16 = (uint16_t)state->a + (uint16_t)state->h + state->cc.cy;
			state->cc.ac = ((state->a & 0x0f) + (state->h & 0x0f) + state->cc.cy) > 0x0f;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x8D:     // ADC L
			data16 = (uint16_t)state->a + (uint16_t)state->l + state->cc.cy;
			state->cc.ac = ((state->a & 0x0f) + (state->l & 0x0f) + state->cc.cy) > 0x0f;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;

		// ADC M - Add memory with carry
		case 0x8E:     // ADC M
			data8 = read_from_hl(state);
			data16 = (uint16_t)state->a + (uint16_t)data8 + state->cc.cy;
			state->cc.ac = ((state->a & 0x0f) + (data8 & 0x0f) + state->cc.cy) > 0x0f;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;

		// ACI data - Add immediate with carry
		case 0xCE:     // ACI data
			data8 = opcode[1];
			data16 = (uint16_t)state->a + (uint16_t)data8 + state->cc.cy;
			state->cc.ac = ((state->a & 0x0f) + (data8 & 0x0f) + state->cc.cy) > 0x0f;
			flags_zsp(state, data16 & 0xff);
			state->cc.cy = (data16 > 0xff);
			state->a = data16 & 0xff;
			state->pc++;
			break;

		// SUB r - Subtract register
		case 0x97:     // SUB A
			data16 = (uint16_t)state->a - (uint16_t)state->a;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x90:     // SUB B
			data16 = (uint16_t)state->a - (uint16_t)state->b;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x91:     // SUB C
			data16 = (uint16_t)state->a - (uint16_t)state->c;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x92:     // SUB D
			data16 = (uint16_t)state->a - (uint16_t)state->d;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x93:     // SUB E
			data16 = (uint16_t)state->a - (uint16_t)state->e;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x94:     // SUB H
			data16 = (uint16_t)state->a - (uint16_t)state->h;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x95:     // SUB L
			data16 = (uint16_t)state->a - (uint16_t)state->l;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;

		// SUB M - Subtract memory
		case 0x96:     // SUB M
			data16 = (uint16_t)state->a - (uint16_t)read_from_hl(state);
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;

		// SUI data - Subtract immediate
		case 0xD6:     // SUI data
			data8 = state->a - opcode[1];
			flags_zsp(state, data8 & 0xff);
			state->cc.cy = (state->a < opcode[1]);
			state->a = data8;
			state->pc++;
			break;

		// SBB r - Subtract register with borrow
		case 0x9F:     // SBB A
			data16 = (uint16_t)state->a - (uint16_t)state->a - state->cc.cy;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x98:     // SBB B
			data16 = (uint16_t)state->a - (uint16_t)state->b - state->cc.cy;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x99:     // SBB C
			data16 = (uint16_t)state->a - (uint16_t)state->c - state->cc.cy;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x9A:     // SBB D
			data16 = (uint16_t)state->a - (uint16_t)state->d - state->cc.cy;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x9B:     // SBB E
			data16 = (uint16_t)state->a - (uint16_t)state->e - state->cc.cy;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x9C:     // SBB H
			data16 = (uint16_t)state->a - (uint16_t)state->h - state->cc.cy;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;
		case 0x9D:     // SBB L
			data16 = (uint16_t)state->a - (uint16_t)state->l - state->cc.cy;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;

		// SBB M - Subtract memory with borrow
		case 0x9E:     // SBB M
			data16 = (uint16_t)state->a - (uint16_t)read_from_hl(state) - state->cc.cy;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;

		// SBI data - Subtract immediate with borrow
		case 0xDE:     // SBI data
			data16 = state->a - opcode[1] - state->cc.cy;
			flags_zsp(state, data16 & 0xff);
			state->cc.cy = (data16 > 0xff);
			state->a = data16 & 0xff;
			state->pc++;
			break;

		// INR r - Increment register
		case 0x3C:     // INR A
			state->cc.ac = (state->a & 0x0f) == 0x0f;
			state->a += 1;
			flags_zsp(state, state->a);
			break;
		case 0x04:     // INR B
			state->cc.ac = (state->b & 0x0f) == 0x0f;
			state->b += 1;
			flags_zsp(state, state->b);
			break;
		case 0x0C:     // INR C
			state->cc.ac = (state->c & 0x0f) == 0x0f;
			state->c += 1;
			flags_zsp(state, state->c);
			break;
		case 0x14:     // INR D
			state->cc.ac = (state->d & 0x0f) == 0x0f;
			state->d += 1;
			flags_zsp(state, state->d);
			break;
		case 0x1C:     // INR E
			state->cc.ac = (state->e & 0x0f) == 0x0f;
			state->e += 1;
			flags_zsp(state, state->e);
			break;
		case 0x24:     // INR H
			state->cc.ac = (state->h & 0x0f) == 0x0f;
			state->h += 1;
			flags_zsp(state, state->h);
			break;
		case 0x2C:     // INR L
			state->cc.ac = (state->l & 0x0f) == 0x0f;
			state->l += 1;
			flags_zsp(state, state->l);
			break;

		// INR M - Increment memory
		case 0x34:     // INR M
			data8 = read_from_hl(state);
			state->cc.ac = (data8 & 0x0f) == 0x0f;
			data8 += 1;
			flags_zsp(state, data8);
			write_to_hl(state, data8);
			break;

		// DCR r - Decrement register
		case 0x3D:     // DCR A
			state->a -= 1;
			flags_zsp(state, state->a);
			break;
		case 0x05:     // DCR B
			state->b -= 1;
			flags_zsp(state, state->b);
			break;
		case 0x0D:     // DCR C
			state->c -= 1;
			flags_zsp(state, state->c);
			break;
		case 0x15:     // DCR D
			state->d -= 1;
			flags_zsp(state, state->d);
			break;
		case 0x1D:     // DCR E
			state->e -= 1;
			flags_zsp(state, state->e);
			break;
		case 0x25:     // DCR H
			state->h -= 1;
			flags_zsp(state, state->h);
			break;
		case 0x2D:     // DCR L
			state->l -= 1;
			flags_zsp(state, state->l);
			break;

		// DCR M - Decrement memory
		case 0x35:     // DCR M
			data8 = read_from_hl(state) - 1;
			flags_zsp(state, data8);
			write_to_hl(state, data8);
			break;

		// INX rp - Increment register pair
		case 0x03:     // INX B
			state->c++;
			if (state->c == 0)
				state->b++;
			break;
		case 0x13:     // INX D
			state->e++;
			if (state->e == 0)
				state->d++;
			break;
		case 0x23:     // INX H
			state->l++;
			if (state->l == 0)
				state->h++;
			break;
		case 0x33:     // INX SP
			state->sp++;
			break;

		// DCX rp - Decrement register pair
		case 0x0B:     // DCX B
			state->c -= 1;
			if (state->c == 0xff)
				state->b -= 1;
			break;
		case 0x1B:     // DCX D
			state->e -= 1;
			if (state->e == 0xff)
				state->d -= 1;
			break;
		case 0x2B:     // DCX H
			state->l -= 1;
			if (state->l == 0xff)
				state->h -= 1;
			break;
		case 0x3B:     // DCX SP
			state->sp--;
			break;

		// DAD rp - Add register pair to H and L
		case 0x09:     // DAD B
			reg_pair_1 = (state->h << 8) | state->l;
			reg_pair_2 = (state->b << 8) | state->c;
			data32 = reg_pair_1 + reg_pair_2;
			state->h = (data32 & 0xff00) >> 8;
			state->l = data32 & 0xff;
			state->cc.cy = ((data32 & 0xffff0000) != 0);
			break;
		case 0x19:     // DAD D
			reg_pair_1 = (state->h << 8) | state->l;
			reg_pair_2 = (state->d << 8) | state->e;
			data32 = reg_pair_1 + reg_pair_2;
			state->h = (data32 & 0xff00) >> 8;
			state->l = data32 & 0xff;
			state->cc.cy = ((data32 & 0xffff0000) != 0);
			break;
		case 0x29:     // DAD H
			reg_pair_1 = (state->h << 8) | state->l;
			data32 = reg_pair_1 + reg_pair_1;
			state->h = (data32 & 0xff00) >> 8;
			state->l = data32 & 0xff;
			state->cc.cy = ((data32 & 0xffff0000) != 0);
			break;
		case 0x39:     // DAD SP
			reg_pair_1 = (state->h << 8) | state->l;
			data32 = reg_pair_1 + state->sp;
			state->h = (data32 & 0xff00) >> 8;
			state->l = data32 & 0xff;
			state->cc.cy = ((data32 & 0xffff0000) != 0);
			break;

		// DAA - Decimal adjust accumulator
		case 0x27:     // DAA
			data16 = (state->a & 0x0f);
			if (data16 > 9 || state->cc.ac)
			{
				data16 += 6;
				state->cc.ac |= (data16 > 0x0f);
			}
			data16 += (state->a & 0xf0);
			if ((data16 & 0xf0) > 0x90 || state->cc.cy)
				data16 += 0x60;
			arith_flags_a(state, data16);
			state->a = (data16 & 0xff);
			break;

		/* LOGICAL GROUP */

		// ANA r - AND register
		case 0xA7:     // ANA A
			state->a = (state->a & state->a);
			logic_flags_a(state);
			break;
		case 0xA0:     // ANA B
			state->a = (state->a & state->b);
			logic_flags_a(state);
			break;
		case 0xA1:     // ANA C
			state->a = (state->a & state->c);
			logic_flags_a(state);
			break;
		case 0xA2:     // ANA D
			state->a = (state->a & state->d);
			logic_flags_a(state);
			break;
		case 0xA3:     // ANA E
			state->a = (state->a & state->e);
			logic_flags_a(state);
			break;
		case 0xA4:     // ANA H
			state->a = (state->a & state->h);
			logic_flags_a(state);
			break;
		case 0xA5:     // ANA L
			state->a = (state->a & state->l);
			logic_flags_a(state);
			break;

		// ANA M - AND memory
		case 0xA6:     // ANA M
			state->a = (state->a & read_from_hl(state));
			logic_flags_a(state);
			break;

		// ANI data - AND immediate
		case 0xE6:     // ANI data
			state->a = (state->a & opcode[1]);
			logic_flags_a(state);
			state->pc++;
			break;

		// XRA r - Exclusive OR register
		case 0xAF:     // XRA A
			state->a = (state->a ^ state->a);
			logic_flags_a(state);
			break;
		case 0xA8:     // XRA B
			state->a = (state->a ^ state->b);
			logic_flags_a(state);
			break;
		case 0xA9:     // XRA C
			state->a = (state->a ^ state->c);
			logic_flags_a(state);
			break;
		case 0xAA:     // XRA D
			state->a = (state->a ^ state->d);
			logic_flags_a(state);
			break;
		case 0xAB:     // XRA E
			state->a = (state->a ^ state->e);
			logic_flags_a(state);
			break;
		case 0xAC:     // XRA H
			state->a = (state->a ^ state->h);
			logic_flags_a(state);
			break;
		case 0xAD:     // XRA L
			state->a = (state->a ^ state->l);
			logic_flags_a(state);
			break;

		// XRA M - Exclusive OR memory
		case 0xAE:     // XRA M
			state->a = (state->a ^ read_from_hl(state));
			logic_flags_a(state);
			break;

		// XRI data - Exclusive OR immediate
		case 0xEE:     // XRI data
			state->a = (state->a ^ opcode[1]);
			logic_flags_a(state);
			state->pc++;
			break;

		// ORA r - OR register
		case 0xB7:     // ORA A
			state->a = (state->a | state->a);
			logic_flags_a(state);
			break;
		case 0xB0:     // ORA B
			state->a = (state->a | state->b);
			logic_flags_a(state);
			break;
		case 0xB1:     // ORA C
			state->a = (state->a | state->c);
			logic_flags_a(state);
			break;
		case 0xB2:     // ORA D
			state->a = (state->a | state->d);
			logic_flags_a(state);
			break;
		case 0xB3:     // ORA E
			state->a = (state->a | state->e);
			logic_flags_a(state);
			break;
		case 0xB4:     // ORA H
			state->a = (state->a | state->h);
			logic_flags_a(state);
			break;
		case 0xB5:     // ORA L
			state->a = (state->a | state->l);
			logic_flags_a(state);
			break;

		// ORA M - OR memory
		case 0xB6:     // ORA M
			state->a = (state->a | read_from_hl(state));
			logic_flags_a(state);
			break;

		// ORI data - OR immediate
		case 0xF6:     // ORI data
			state->a = (state->a | opcode[1]);
			logic_flags_a(state);
			state->pc++;
			break;

		// CMP r - Compare register
		case 0xBF:     // CMP A
			data16 = (uint16_t)state->a - (uint16_t)state->a;
			arith_flags_a(state, data16);
			break;
		case 0xB8:     // CMP B
			data16 = (uint16_t)state->a - (uint16_t)state->b;
			arith_flags_a(state, data16);
			break;
		case 0xB9:     // CMP C
			data16 = (uint16_t)state->a - (uint16_t)state->c;
			arith_flags_a(state, data16);
			break;
		case 0xBA:     // CMP D
			data16 = (uint16_t)state->a - (uint16_t)state->d;
			arith_flags_a(state, data16);
			break;
		case 0xBB:     // CMP E
			data16 = (uint16_t)state->a - (uint16_t)state->e;
			arith_flags_a(state, data16);
			break;
		case 0xBC:     // CMP H
			data16 = (uint16_t)state->a - (uint16_t)state->h;
			arith_flags_a(state, data16);
			break;
		case 0xBD:     // CMP L
			data16 = (uint16_t)state->a - (uint16_t)state->l;
			arith_flags_a(state, data16);
			break;

		// CMP M - Compare memory
		case 0xBE:     // CMP M
			data16 = (uint16_t)state->a - (uint16_t)read_from_hl(state);
			arith_flags_a(state, data16);
			break;

		// CPI data - Compare immediate
		case 0xFE:     // CPI data
			data16 = (uint16_t)state->a - (uint16_t)opcode[1];
			arith_flags_a(state, data16);
			state->pc++;
			break;

		// RLC - Rotate left
		case 0x07:     // RLC
			data8 = state->cc.cy = state->a >> 7;
			state->a = (state->a << 1) | data8;
			break;

		// RRC - Rotate right
		case 0x0F:     // RRC
			data8 = state->cc.cy = state->a & 0x01;
			state->a = (state->a >> 1) | (data8 << 7);
			break;

		// RAL - Rotate left through carry
		case 0x17:     // RAL
			data8 = state->a >> 7;
			state->a = (state->a << 1) | state->cc.cy;
			state->cc.cy = data8;
			break;

		// RAR - Rotate right through carry
		case 0x1F:     // RAR
			data8 = state->a & 0x01;
			state->a = (state->a >> 1) | (state->cc.cy << 7);
			state->cc.cy = data8;
			break;

		// CMA - Complement accumulator
		case 0x2F:     // CMA
			state->a = ~state->a;
			break;

		// CMC - Complement carry
		case 0x3F:     // CMC
			state->cc.cy = ~state->cc.cy;
			break;

		// STC - Set carry
		case 0x37:     // STC
			state->cc.cy = 0x01;
			break;

		/* BRANCH GROUP */

		// JMP addr - Jump
		case 0xC3:     // JMP addr
			state->pc = (opcode[2] << 8) | opcode[1];
			break;

		// JCondition addr - Conditional jump
		case 0xDA:     // JC addr
			if (state->cc.cy == 1)
				state->pc = (opcode[2] << 8) | opcode[1];
			else
				state->pc += 2;
			break;
		case 0xD2:     // JNC addr
			if (state->cc.cy == 0)
				state->pc = (opcode[2] << 8) | opcode[1];
			else
				state->pc += 2;
			break;
		case 0xCA:     // JZ addr
			if (state->cc.z == 1)
				state->pc = (opcode[2] << 8) | opcode[1];
			else
				state->pc += 2;
			break;
		case 0xC2:     // JNZ addr
			if (state->cc.z == 0)
				state->pc = (opcode[2] << 8) | opcode[1];
			else
				state->pc += 2;
			break;
		case 0xF2:     // JP addr
			if (state->cc.s == 0)
				state->pc = (opcode[2] << 8) | opcode[1];
			else
				state->pc += 2;
			break;
		case 0xFA:     // JM addr
			if (state->cc.s == 1)
				state->pc = (opcode[2] << 8) | opcode[1];
			else
				state->pc += 2;
			break;
		case 0xEA:     // JPE addr
			if (state->cc.p == 1)
				state->pc = (opcode[2] << 8) | opcode[1];
			else
				state->pc += 2;
			break;
		case 0xE2:     // JPO addr
			if (state->cc.p == 0)
				state->pc = (opcode[2] << 8) | opcode[1];
			else
				state->pc += 2;
			break;

		// CALL addr - Call unconditional
		case 0xCD:     // CALL addr
			offset = state->pc + 2;
			push(state, offset >> 8, offset);
			state->pc = (opcode[2] << 8) | opcode[1];
			break;

		// CCondition addr - Conditional call
		case 0xDC:     // CC addr
			if (state->cc.cy == 1)
			{
				offset = state->pc + 2;
				push(state, offset >> 8, offset);
				state->pc = (opcode[2] << 8) | opcode[1];
			}
			else
			{
				state->pc += 2;
				alt_cycles = 11;
			}
			break;
		case 0xD4:     // CNC addr
			if (state->cc.cy == 0)
			{
				offset = state->pc + 2;
				push(state, offset >> 8, offset);
				state->pc = (opcode[2] << 8) | opcode[1];
			}
			else
			{
				state->pc += 2;
				alt_cycles = 11;
			}
			break;
		case 0xCC:     // CZ addr
			if (state->cc.z == 1)
			{
				offset = state->pc + 2;
				push(state, offset >> 8, offset);
				state->pc = (opcode[2] << 8) | opcode[1];
			}
			else
			{
				state->pc += 2;
				alt_cycles = 11;
			}
			break;
		case 0xC4:     // CNZ addr
			if (state->cc.z == 0)
			{
				offset = state->pc + 2;
				push(state, offset >> 8, offset);
				state->pc = (opcode[2] << 8) | opcode[1];
			}
			else
			{
				state->pc += 2;
				alt_cycles = 11;
			}
			break;
		case 0xF4:     // CP addr
			if (state->cc.s == 0)
			{
				offset = state->pc + 2;
				push(state, offset >> 8, offset);
				state->pc = (opcode[2] << 8) | opcode[1];
			}
			else
			{
				state->pc += 2;
				alt_cycles = 11;
			}
			break;
		case 0xFC:     // CM addr
			if (state->cc.s == 1)
			{
				offset = state->pc + 2;
				push(state, offset >> 8, offset);
				state->pc = (opcode[2] << 8) | opcode[1];
			}
			else
			{
				state->pc += 2;
				alt_cycles = 11;
			}
			break;
		case 0xEC:     // CPE addr
			if (state->cc.p == 1)
			{
				offset = state->pc + 2;
				push(state, offset >> 8, offset);
				state->pc = (opcode[2] << 8) | opcode[1];
			}
			else
			{
				state->pc += 2;
				alt_cycles = 11;
			}
			break;
		case 0xE4:     // CPO addr
			if (state->cc.p == 0)
			{
				offset = state->pc + 2;
				push(state, offset >> 8, offset);
				state->pc = (opcode[2] << 8) | opcode[1];
			}
			else
			{
				state->pc += 2;
				alt_cycles = 11;
			}
			break;

		// RET - Return
		case 0xC9:     // RET
			pop(state, (uint8_t *)&state->pc + 1, (uint8_t *)&state->pc);
			break;

		// RCondition - Conditional return
		case 0xD8:     // RC
			if (state->cc.cy == 1)
				pop(state, (uint8_t *)&state->pc + 1, (uint8_t *)&state->pc);
			else
				alt_cycles = 5;
			break;
		case 0xD0:     // RNC
			if (state->cc.cy == 0)
				pop(state, (uint8_t *)&state->pc + 1, (uint8_t *)&state->pc);
			else
				alt_cycles = 5;
			break;
		case 0xC8:     // RZ
			if (state->cc.z == 1)
				pop(state, (uint8_t *)&state->pc + 1, (uint8_t *)&state->pc);
			else
				alt_cycles = 5;
			break;
		case 0xC0:     // RNZ
			if (state->cc.z == 0)
				pop(state, (uint8_t *)&state->pc + 1, (uint8_t *)&state->pc);
			else
				alt_cycles = 5;
			break;
		case 0xF0:     // RP
			if (state->cc.s == 0)
				pop(state, (uint8_t *)&state->pc + 1, (uint8_t *)&state->pc);
			else
				alt_cycles = 5;
			break;
		case 0xF8:     // RM
			if (state->cc.s == 1)
				pop(state, (uint8_t *)&state->pc + 1, (uint8_t *)&state->pc);
			else
				alt_cycles = 5;
			break;
		case 0xE8:     // RPE
			if (state->cc.p == 1)
				pop(state, (uint8_t *)&state->pc + 1, (uint8_t *)&state->pc);
			else
				alt_cycles = 5;
			break;
		case 0xE0:     // RPO
			if (state->cc.p == 0)
				pop(state, (uint8_t *)&state->pc + 1, (uint8_t *)&state->pc);
			else
				alt_cycles = 5;
			break;

		// RST n - Restart
		case 0xC7:     // RST 0
			offset = state->pc + 2;
			push(state, offset >> 8, offset);
			state->pc = 8 * 0;
			break;
		case 0xCF:     // RST 1
			offset = state->pc + 2;
			push(state, offset >> 8, offset);
			state->pc = 8 * 1;
			break;
		case 0xD7:     // RST 2
			offset = state->pc + 2;
			push(state, offset >> 8, offset);
			state->pc = 8 * 2;
			break;
		case 0xDF:     // RST 3
			offset = state->pc + 2;
			push(state, offset >> 8, offset);
			state->pc = 8 * 3;
			break;
		case 0xE7:     // RST 4
			offset = state->pc + 2;
			push(state, offset >> 8, offset);
			state->pc = 8 * 4;
			break;
		case 0xEF:     // RST 5
			offset = state->pc + 2;
			push(state, offset >> 8, offset);
			state->pc = 8 * 5;
			break;
		case 0xF7:     // RST 6
			offset = state->pc + 2;
			push(state, offset >> 8, offset);
			state->pc = 8 * 6;
			break;
		case 0xFF:     // RST 7
			offset = state->pc + 2;
			push(state, offset >> 8, offset);
			state->pc = 8 * 7;
			break;

		// PCHL - Jump H and L indirect - move H and L to PC
		case 0xE9:     // PCHL
			state->pc = (state->h << 8) | state->l;
			break;

		/* STACK, I/O, AND MACHINE CONTROL GROUP */

		// PUSH rp - Push register pair to stack
		case 0xC5:     // PUSH B
			push(state, state->b, state->c);
			break;
		case 0xD5:     // PUSH D
			push(state, state->d, state->e);
			break;
		case 0xE5:     // PUSH H
			push(state, state->h, state->l);
			break;

		// PUSH PSW - Push processor status word
		case 0xF5:     // PUSH PSW
			push(state, state->a, *(uint8_t *)&state->cc);
			break;

		// POP rp - Pop top 2 bytes of stack to register pair
		case 0xC1:     // POP B
			pop(state, &state->b, &state->c);
			break;
		case 0xD1:     // POP D
			pop(state, &state->d, &state->e);
			break;
		case 0xE1:     // POP H
			pop(state, &state->h, &state->l);
			break;

		// POP PSW - Pop processor status word
		case 0xF1:     // POP PSW
			pop(state, &state->a, (uint8_t *)&state->cc);
			break;

		// XTHL - Exchange data at the top of the stack with data in the HL register pair
		case 0xE3:     // XTHL
			reg_1 = state->h;
			reg_2 = state->l;
			state->l = state->memory[state->sp];
			state->h = state->memory[state->sp + 1];
			write_mem(state, state->sp, reg_2);
			write_mem(state, state->sp + 1, reg_1);
			break;

		// SPHL - Moves the HL register pair to SP
		case 0xF9:     // SPHL
			state->sp = state->l | (state->h << 8);
			break;

		// IN port - Handles input from external hardware
		// not yet implemented
		case 0xDB:     // IN port
			state->pc++;
			break;

		// OUT port - Handles output to external hardware
		// not yet implemented
		case 0xD3:     // OUT port
			state->pc++;
			break;

		// EI - Enable interrupts
		case 0xFB:     // EI
			state->int_enable = 1;
			break;

		// DI - Disable interrupts
		case 0xF3:     // DI
			state->int_enable = 0;
			break;

		// HLT - Halt (terminate program)
		case 0x76:     // HLT
			exit(0);

		// NOP - No operation
		case 0x00:     // NOP
			break;

		default: unimplemented_instruction(state);
	}

#ifdef PRINTPSW
	printf("\tREGISTERS:  "
	       "A=%02x B=%02x C=%02x D=%02x E=%02x H=%02x L=%02x SP=%04x PC=%04x      ",
	       state->a, state->b, state->c, state->d, state->e, state->h, state->l, state->sp, state->pc);
	printf("FLAGS:  %c %c %c %s %s\n",
	       state->cc.z ? 'Z' : '-',
	       state->cc.s ? 'S' : '-',
	       state->cc.p ? 'P' : '-',
	       state->cc.cy ? "CY" : "--",
	       state->cc.ac ? "AC" : "--");
#endif

	// return cycles_8080[*opcode];
	if (alt_cycles)
		return alt_cycles;
	return cycles_8080[*opcode];
}

void generate_interrupt(State_8080 *state, int interrupt_num)
{
	// RST interrupt_num
	push(state, (state->pc >> 8), (state->pc & 0xff));
	state->pc = 8 * interrupt_num;

	state->int_enable = 0;
}

#ifdef MAIN_EMULATOR
int main(int argc, char **argv)
{
	State_8080 *state = init_8080();
	if (argc == 1)
	{
		read_file_into_memory_at(state, "../invaders/invaders.h", 0);
		read_file_into_memory_at(state, "../invaders/invaders.g", 0x800);
		read_file_into_memory_at(state, "../invaders/invaders.f", 0x1000);
		read_file_into_memory_at(state, "../invaders/invaders.e", 0x1800);
	}
	else if (argc == 2)
		read_file_into_memory_at(state, argv[1], 0);
	else
	{
		printf("Invalid Number of arguments\n");
		exit(1);
	}

	while (1)
	{
		emulate_8080_op(state);
	}

	return 0;
}
#endif
