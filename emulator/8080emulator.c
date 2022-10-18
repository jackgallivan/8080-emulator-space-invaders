#include "8080emulator.h"

int Emulate8080Op(State8080* state)
{
	int cycles = 4;
	unsigned char *opcode = &state->memory[state->pc];

	switch(*opcode)
	{

        /* DATA TRANSFER GROUP */

		// MOV r1,r2 - Move between registers
        case 0x7F: state->a = state->a; break;
        case 0x78: state->a = state->b; break;
        case 0x79: state->a = state->c; break;
        case 0x7A: state->a = state->d; break;
        case 0x7B: state->a = state->e; break;
        case 0x7C: state->a = state->h; break;
        case 0x7D: state->a = state->l; break;
        case 0x47: state->b = state->a; break;
        case 0x40: state->b = state->b; break;
        case 0x41: state->b = state->c; break;
        case 0x42: state->b = state->d; break;
        case 0x43: state->b = state->e; break;
        case 0x44: state->b = state->h; break;
        case 0x45: state->b = state->l; break;
        case 0x4F: state->c = state->a; break;
        case 0x48: state->c = state->b; break;
        case 0x49: state->c = state->c; break;
        case 0x4A: state->c = state->d; break;
        case 0x4B: state->c = state->e; break;
        case 0x4C: state->c = state->h; break;
        case 0x4D: state->c = state->l; break;
        case 0x57: state->d = state->a; break;
        case 0x50: state->d = state->b; break;
        case 0x51: state->d = state->c; break;
        case 0x52: state->d = state->d; break;
        case 0x53: state->d = state->e; break;
        case 0x54: state->d = state->h; break;
        case 0x55: state->d = state->l; break;
        case 0x5F: state->e = state->a; break;
        case 0x58: state->e = state->b; break;
        case 0x59: state->e = state->c; break;
        case 0x5A: state->e = state->d; break;
        case 0x5B: state->e = state->e; break;
        case 0x5C: state->e = state->h; break;
        case 0x5D: state->e = state->l; break;
        case 0x67: state->h = state->a; break;
        case 0x60: state->h = state->b; break;
        case 0x61: state->h = state->c; break;
        case 0x62: state->h = state->d; break;
        case 0x63: state->h = state->e; break;
        case 0x64: state->h = state->h; break;
        case 0x65: state->h = state->l; break;
        case 0x6F: state->l = state->a; break;
        case 0x68: state->l = state->b; break;
        case 0x69: state->l = state->c; break;
        case 0x6A: state->l = state->d; break;
        case 0x6B: state->l = state->e; break;
        case 0x6C: state->l = state->h; break;
        case 0x6D: state->l = state->l; break;

		// MOV r,M - Move from memory to register
        case 0x7E: state->a = ReadFromHL(state); break;
        case 0x46: state->b = ReadFromHL(state); break;
        case 0x4E: state->c = ReadFromHL(state); break;
        case 0x56: state->d = ReadFromHL(state); break;
        case 0x5E: state->e = ReadFromHL(state); break;
        case 0x66: state->h = ReadFromHL(state); break;
        case 0x6E: state->l = ReadFromHL(state); break;

		// MOV M,r - Move to memory from register
        case 0x77: WriteToHL(state, state->a); break;
        case 0x70: WriteToHL(state, state->b); break;
        case 0x71: WriteToHL(state, state->c); break;
        case 0x72: WriteToHL(state, state->d); break;
        case 0x73: WriteToHL(state, state->e); break;
        case 0x74: WriteToHL(state, state->h); break;
        case 0x75: WriteToHL(state, state->l); break;

		// MVI r,data - Move to register immediate
        case 0x3E:
			state->a = opcode[1];
			state->pc++;
			break;
        case 0x06:
			state->b = opcode[1];
			state->pc++;
			break;
        case 0x0E:
			state->c = opcode[1];
			state->pc++;
			break;
        case 0x16:
			state->d = opcode[1];
			state->pc++;
			break;
        case 0x1E:
			state->e = opcode[1];
			state->pc++;
			break;
        case 0x26:
			state->h = opcode[1];
			state->pc++;
			break;
        case 0x2E:
			state->l = opcode[1];
			state->pc++;
			break;

		// MVI M,data - Move to memory immediate
        case 0x36:
			WriteToHL(state, opcode[1]);
			state->pc++;
			break;

		// LXI rp,data16 - Load register pair immediate
        case 0x01:
			state->c = opcode[1];
			state->b = opcode[2];
			state->pc += 2;
			break;
        case 0x11:
			state->d = opcode[1];
			state->e = opcode[2];
			state->pc += 2;
			break;
        case 0x21:
			state->h = opcode[1];
			state->l = opcode[2];
			state->pc += 2;
			break;
        case 0x31:
			state->sp = (opcode[2]<<8) | opcode[1];
			state->pc += 2;
			break;

		// LDA addr - Load accumulator direct
        case 0x3A:
			uint16_t offset = (opcode[2]<<8) | (opcode[1]);
			state->a = state->memory[offset];
			state->pc+=2;
			break;

		// STA addr - Store accumulator direct
        case 0x32:
			uint16_t offset = (opcode[2]<<8) | (opcode[1]);
            WriteMem(state, offset, state->a);
			state->pc += 2;
			break;

		// LHLD addr - Load H and L direct
        case 0x2A:
            uint16_t offset = opcode[1] | (opcode[2] << 8);
            state->l = state->memory[offset];
            state->h = state->memory[offset+1];
            state->pc += 2;
			break;

		// SHLD addr - Store H and L direct
        case 0x22:
            uint16_t offset = opcode[1] | (opcode[2] << 8);
            WriteMem(state, offset, state->l);
            WriteMem(state, offset+1, state->h);
            state->pc += 2;
			break;

		// LDAX rp - Load accumulator indirect
        case 0x0A:
			uint16_t offset=(state->b<<8) | state->c;
			state->a = state->memory[offset];
			break;
        case 0x1A:
			uint16_t offset=(state->d<<8) | state->e;
			state->a = state->memory[offset];
			break;

		// LDAX rp - Store accumulator indirect
        case 0x02:
            uint16_t offset=(state->b<<8) | state->c;
            WriteMem(state, offset, state->a);
			break;
        case 0x12:
            uint16_t offset=(state->d<<8) | state->e;
            WriteMem(state, offset, state->a);
			break;

		// XCHG - Exchange H and L with D and E
        case 0xEB:
            uint8_t save1 = state->d;
            uint8_t save2 = state->e;
            state->d = state->h;
            state->e = state->l;
            state->h = save1;
            state->l = save2;
			break;

        /* ARITHMETIC GROUP */

		// ADD r - Add register
        case 0x87:
			uint16_t res = (uint16_t) state->a + (uint16_t) state->a;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x80:
			uint16_t res = (uint16_t) state->a + (uint16_t) state->b;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x81:
			uint16_t res = (uint16_t) state->a + (uint16_t) state->c;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x82:
			uint16_t res = (uint16_t) state->a + (uint16_t) state->d;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x83:
			uint16_t res = (uint16_t) state->a + (uint16_t) state->e;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x84:
			uint16_t res = (uint16_t) state->a + (uint16_t) state->h;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x85:
			uint16_t res = (uint16_t) state->a + (uint16_t) state->l;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;

		// ADD M - Add memory
        case 0x86:
			uint16_t res = (uint16_t) state->a + (uint16_t) ReadFromHL(state);
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;

		// ADI data - Add immediate
        case 0xC6:
			uint16_t x = (uint16_t) state->a + (uint16_t) opcode[1];
            FlagsZSP(state, x&0xff);
			state->cc.cy = (x > 0xff);
			state->a = x&0xff;
			state->pc++;
			break;

		// ADC r - Add register with carry
        case 0x8F:
			uint16_t res = (uint16_t) state->a + (uint16_t) state->a + state->cc.cy;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x88:
			uint16_t res = (uint16_t) state->a + (uint16_t) state->b + state->cc.cy;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x89:
			uint16_t res = (uint16_t) state->a + (uint16_t) state->c + state->cc.cy;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x8A:
			uint16_t res = (uint16_t) state->a + (uint16_t) state->d + state->cc.cy;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x8B:
			uint16_t res = (uint16_t) state->a + (uint16_t) state->e + state->cc.cy;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x8C:
			uint16_t res = (uint16_t) state->a + (uint16_t) state->h + state->cc.cy;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x8D:
			uint16_t res = (uint16_t) state->a + (uint16_t) state->l + state->cc.cy;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;

		// ADC M - Add memory with carry
        case 0x8E:
			uint16_t res = (uint16_t) state->a + (uint16_t) ReadFromHL(state) + state->cc.cy;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;

		// ACI data - Add immediate with carry
        case 0xCE:
			uint16_t x = state->a + opcode[1] + state->cc.cy;
            FlagsZSP(state, x&0xff);
			state->cc.cy = (x > 0xff);
			state->a = x & 0xff;
			state->pc++;
			break;

		// SUB r - Subtract register
        case 0x97:
			uint16_t res = (uint16_t) state->a - (uint16_t) state->a;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x90:
			uint16_t res = (uint16_t) state->a - (uint16_t) state->b;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x91:
			uint16_t res = (uint16_t) state->a - (uint16_t) state->c;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x92:
			uint16_t res = (uint16_t) state->a - (uint16_t) state->d;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x93:
			uint16_t res = (uint16_t) state->a - (uint16_t) state->e;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x94:
			uint16_t res = (uint16_t) state->a - (uint16_t) state->h;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x95:
			uint16_t res = (uint16_t) state->a - (uint16_t) state->l;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;

		// SUB M - Subtract memory
        case 0x96:
			uint16_t res = (uint16_t) state->a - (uint16_t) ReadFromHL(state);
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;

		// SUI data - Subtract immediate
        case 0xD6:
			uint8_t x = state->a - opcode[1];
            FlagsZSP(state, x&0xff);
			state->cc.cy = (state->a < opcode[1]);
			state->a = x;
			state->pc++;
			break;

		// SBB r - Subtract register with borrow
        case 0x9F:
			uint16_t res = (uint16_t) state->a - (uint16_t) state->a - state->cc.cy;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x98:
			uint16_t res = (uint16_t) state->a - (uint16_t) state->b - state->cc.cy;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x99:
			uint16_t res = (uint16_t) state->a - (uint16_t) state->c - state->cc.cy;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x9A:
			uint16_t res = (uint16_t) state->a - (uint16_t) state->d - state->cc.cy;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x9B:
			uint16_t res = (uint16_t) state->a - (uint16_t) state->e - state->cc.cy;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x9C:
			uint16_t res = (uint16_t) state->a - (uint16_t) state->h - state->cc.cy;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;
        case 0x9D:
			uint16_t res = (uint16_t) state->a - (uint16_t) state->l - state->cc.cy;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;

		// SBB M - Subtract memory with borrow
        case 0x9E:
			uint16_t res = (uint16_t) state->a - (uint16_t) ReadFromHL(state) - state->cc.cy;
			ArithFlagsA(state, res);
			state->a=(res&0xff);
			break;

		// SBI data - Subtract immediate with borrow
        case 0xDE:
			uint16_t x = state->a - opcode[1] - state->cc.cy;
            FlagsZSP(state, x&0xff);
			state->cc.cy = (x > 0xff);
			state->a = x & 0xff;
			state->pc++;
			break;

		// INR r - Increment register
        case 0x3C:
            state->a += 1;
            FlagsZSP(state,state->a);
			break;
        case 0x04:
            state->b += 1;
            FlagsZSP(state,state->b);
			break;
        case 0x0C:
            state->c += 1;
            FlagsZSP(state,state->c);
			break;
        case 0x14:
            state->d += 1;
            FlagsZSP(state,state->d);
			break;
        case 0x1C:
            state->e += 1;
            FlagsZSP(state,state->e);
			break;
        case 0x24:
            state->h += 1;
            FlagsZSP(state,state->h);
			break;
        case 0x2C:
            state->l += 1;
            FlagsZSP(state,state->l);
			break;

		// INR M - Increment memory
        case 0x34:
			uint8_t res = ReadFromHL(state) + 1;
            FlagsZSP(state, res);
            WriteToHL(state, res);
			break;

		// DCR r - Decrement register
        case 0x3D:
            state->a -= 1;
            FlagsZSP(state,state->a);
			break;
        case 0x05:
            state->b -= 1;
            FlagsZSP(state,state->b);
			break;
        case 0x0D:
            state->c -= 1;
            FlagsZSP(state,state->c);
			break;
        case 0x15:
            state->d -= 1;
            FlagsZSP(state,state->d);
			break;
        case 0x1D:
            state->e -= 1;
            FlagsZSP(state,state->e);
			break;
        case 0x25:
            state->h -= 1;
            FlagsZSP(state,state->h);
			break;
        case 0x2D:
            state->l -= 1;
            FlagsZSP(state,state->l);
			break;

		// DCR M - Decrement memory
        case 0x35:
			uint8_t res = ReadFromHL(state) - 1;
            FlagsZSP(state, res);
            WriteToHL(state, res);
			break;

		// INX rp - Increment register pair
        case 0x03:
			state->c++;
			if (state->c == 0)
				state->b++;
			break;
        case 0x13:
			state->e++;
			if (state->e == 0)
				state->d++;
			break;
        case 0x23:
			state->l++;
			if (state->l == 0)
				state->h++;
			break;
        case 0x33:
			state->sp++;
			break;

		// DCX rp - Decrement register pair
        case 0x0B:
			state->c -= 1;
			if (state->c==0xff)
				state->b-=1;
			break;
        case 0x1B:
			state->e -= 1;
			if (state->e==0xff)
				state->d-=1;
			break;
        case 0x2B:
			state->l -= 1;
			if (state->l==0xff)
				state->h-=1;
			break;
        case 0x3B:
			state->sp--;
			break;

		// DAD rp - Add register pair to H and L
        case 0x09:
			uint32_t hl = (state->h << 8) | state->l;
			uint32_t bc = (state->b << 8) | state->c;
			uint32_t res = hl + bc;
			state->h = (res & 0xff00) >> 8;
			state->l = res & 0xff;
			state->cc.cy = ((res & 0xffff0000) != 0);
			break;
        case 0x19:
			uint32_t hl = (state->h << 8) | state->l;
			uint32_t de = (state->d << 8) | state->e;
			uint32_t res = hl + de;
			state->h = (res & 0xff00) >> 8;
			state->l = res & 0xff;
			state->cc.cy = ((res & 0xffff0000) != 0);
			break;
        case 0x29:
			uint32_t hl = (state->h << 8) | state->l;
			uint32_t res = hl + hl;
			state->h = (res & 0xff00) >> 8;
			state->l = res & 0xff;
			state->cc.cy = ((res & 0xffff0000) != 0);
			break;
        case 0x39:
			uint32_t hl = (state->h << 8) | state->l;
			uint32_t res = hl + state->sp;
			state->h = (res & 0xff00) >> 8;
			state->l = res & 0xff;
			state->cc.cy = ((res & 0xffff0000) != 0);
			break;

		// DAA - Decimal adjust accumulator
        case 0x27:
            if ((state->a &0xf) > 9)
                state->a += 6;
            if ((state->a&0xf0) > 0x90)
            {
                uint16_t res = (uint16_t) state->a + 0x60;
                state->a = res & 0xff;
                ArithFlagsA(state, res);
            }
            break;

        /* LOGICAL GROUP */

		// ANA r - AND register
        case 0xA7:								// ANA A
			state->a = (state->a & state->a);
            LogicFlagsA(state);
			break;
		case 0xA0:								// ANA B
			state->a = (state->a & state->b);
            LogicFlagsA(state);
			break;
		case 0xA1:								// ANA C
			state->a = (state->a & state->c);
            LogicFlagsA(state);
			break;
		case 0xA2:								// ANA D
			state->a = (state->a & state->d);
            LogicFlagsA(state);
			break;
		case 0xA3:								// ANA E
			state->a = (state->a & state->e);
            LogicFlagsA(state);
			break;
		case 0xA4:								// ANA H
			state->a = (state->a & state->h);
            LogicFlagsA(state);
			break;
		case 0xA5:								// ANA L
			state->a = (state->a & state->l);
            LogicFlagsA(state);
			break;

		// ANA M - AND memory
		case 0xA6:								// ANA M
			state->a = (state->a & ReadFromHL(state));
            LogicFlagsA(state);
			break;

		// ANI data - AND immediate
		case 0xE6:								// ANI data
			state->a = (state->a & opcode[1]);
            LogicFlagsA(state);
			state->pc++;
			break;

		// XRA r - Exclusive OR register
		case 0xAF:								// XRA A
			state->a = (state->a ^ state->a);
            LogicFlagsA(state);
			break;
		case 0xA8:								// XRA B
			state->a = (state->a ^ state->b);
            LogicFlagsA(state);
			break;
		case 0xA9:								// XRA C
			state->a = (state->a ^ state->c);
            LogicFlagsA(state);
			break;
		case 0xAA:								// XRA D
			state->a = (state->a ^ state->d);
            LogicFlagsA(state);
			break;
		case 0xAB:								// XRA E
			state->a = (state->a ^ state->e);
            LogicFlagsA(state);
			break;
		case 0xAC:								// XRA H
			state->a = (state->a ^ state->h);
            LogicFlagsA(state);
			break;
		case 0xAD:								// XRA L
			state->a = (state->a ^ state->l);
            LogicFlagsA(state);
			break;

		// XRA M - Exclusive OR memory
		case 0xAE:								// XRA M
			state->a = (state->a ^ ReadFromHL(state));
            LogicFlagsA(state);
			break;

		// XRI data - Exclusive OR immediate
		case 0xEE:								// XRI data
			state->a = (state->a ^ opcode[1]);
            LogicFlagsA(state);
			state->pc++;
			break;

		// ORA r - OR register
		case 0xB7:								// ORA A
			state->a = (state->a | state->a);
            LogicFlagsA(state);
			break;
		case 0xB0:								// ORA B
			state->a = (state->a | state->b);
            LogicFlagsA(state);
			break;
		case 0xB1:								// ORA C
			state->a = (state->a | state->c);
            LogicFlagsA(state);
			break;
		case 0xB2:								// ORA D
			state->a = (state->a | state->d);
            LogicFlagsA(state);
			break;
		case 0xB3:								// ORA E
			state->a = (state->a | state->e);
            LogicFlagsA(state);
			break;
		case 0xB4:								// ORA H
			state->a = (state->a | state->h);
            LogicFlagsA(state);
			break;
		case 0xB5:								// ORA L
			state->a = (state->a | state->l);
            LogicFlagsA(state);
			break;

		// ORA M - OR memory
        case 0xB6:								// ORA M
			state->a = (state->a | ReadFromHL(state));
            LogicFlagsA(state);
			break;

		// ORI data - OR immediate
        case 0xF6:								// ORI data
			state->a = (state->a | opcode[1]);
            LogicFlagsA(state);
			state->pc++;
			break;

		// CMP r - Compare register
        case 0xBF:								// CMP A
			uint16_t res = (uint16_t) state->a - (uint16_t) state->a;
            ArithFlagsA(state, res);
			break;
        case 0xB8:								// CMP B
			uint16_t res = (uint16_t) state->a - (uint16_t) state->b;
            ArithFlagsA(state, res);
			break;
        case 0xB9:								// CMP C
			uint16_t res = (uint16_t) state->a - (uint16_t) state->c;
            ArithFlagsA(state, res);
			break;
        case 0xBA:								// CMP D
			uint16_t res = (uint16_t) state->a - (uint16_t) state->d;
            ArithFlagsA(state, res);
			break;
        case 0xBB:								// CMP E
			uint16_t res = (uint16_t) state->a - (uint16_t) state->e;
            ArithFlagsA(state, res);
			break;
        case 0xBC:								// CMP H
			uint16_t res = (uint16_t) state->a - (uint16_t) state->h;
            ArithFlagsA(state, res);
			break;
        case 0xBD:								// CMP L
			uint16_t res = (uint16_t) state->a - (uint16_t) state->l;
            ArithFlagsA(state, res);
			break;

		// CMP M - Compare memory
        case 0xBE:								// CMP M
			uint16_t res = (uint16_t) state->a - (uint16_t) ReadFromHL(state);
            ArithFlagsA(state, res);
			break;

		// CPI data - Compare immediate
        case 0xFE:								// CPI data
			uint16_t res = (uint16_t) state->a - (uint16_t) opcode[1];
            ArithFlagsA(state, res);
			state->pc++;
			break;

		// RLC - Rotate left
        case 0x07:								// RLC
			uint8_t x = state->cc.cy = state->a >> 7;
			state->a = (state->a << 1) | x;
			break;

		// RRC - Rotate right
        case 0x0F:								// RRC
			uint8_t x = state->cc.cy = state->a & 0x01;
			state->a = (state->a >> 1) | (x << 7);
			break;

		// RAL - Rotate left through carry
        case 0x17:								// RAL
			uint8_t x = state->a >> 7;
			state->a = (state->a << 1) | state->cc.cy;
			state->cc.cy = x;
			break;

		// RAR - Rotate right through carry
        case 0x1F:								// RAR
			uint8_t x = state->a & 0x01;
			state->a = (state->a << 1) | (state->cc.cy << 7);
			state->cc.cy = x;
			break;

		// CMA - Complement accumulator
        case 0x2F:								// CMA
			state->a = ~state->a;
			break;

		// CMC - Complement carry
        case 0x3F:								// CMC
			state->cc.cy = ~state->cc.cy;
			break;

		// STC - Set carry
        case 0x37:								// STC
			state->cc.cy = 0x01;
			break;

        /* BRANCH GROUP */

        case 0xC3: printf("JMP \t0x%02X%02X", opcode[2], opcode[1]); break;
        case 0xDA: printf("JC  \t0x%02X%02X", opcode[2], opcode[1]); break;
        case 0xD2: printf("JN  \t0x%02X%02X", opcode[2], opcode[1]); break;
        case 0xCA: printf("JZ  \t0x%02X%02X", opcode[2], opcode[1]); break;
        case 0xC2: printf("JNZ \t0x%02X%02X", opcode[2], opcode[1]); break;
        case 0xF2: printf("JP  \t0x%02X%02X", opcode[2], opcode[1]); break;
        case 0xFA: printf("JM  \t0x%02X%02X", opcode[2], opcode[1]); break;
        case 0xEA: printf("JPE \t0x%02X%02X", opcode[2], opcode[1]); break;
        case 0xE2: printf("JPO \t0x%02X%02X", opcode[2], opcode[1]); break;
        case 0xCD: printf("CALL\t0x%02X%02X", opcode[2], opcode[1]); break;
        case 0xDC: printf("CC  \t0x%02X%02X", opcode[2], opcode[1]); break;
        case 0xD4: printf("CNC \t0x%02X%02X", opcode[2], opcode[1]); break;
        case 0xCC: printf("CZ  \t0x%02X%02X", opcode[2], opcode[1]); break;
        case 0xC4: printf("CNZ \t0x%02X%02X", opcode[2], opcode[1]); break;
        case 0xF4: printf("CP  \t0x%02X%02X", opcode[2], opcode[1]); break;
        case 0xFC: printf("CM  \t0x%02X%02X", opcode[2], opcode[1]); break;
        case 0xEC: printf("CPE \t0x%02X%02X", opcode[2], opcode[1]); break;
        case 0xE4: printf("CPO \t0x%02X%02X", opcode[2], opcode[1]); break;
        case 0xC9: printf("RET "); break;
        case 0xD8: printf("RC  "); break;
        case 0xD0: printf("RNC "); break;
        case 0xC8: printf("RZ  "); break;
        case 0xC0: printf("RNZ "); break;
        case 0xF0: printf("RP  "); break;
        case 0xF8: printf("RM  "); break;
        case 0xE8: printf("RPE "); break;
        case 0xE0: printf("RPO "); break;
        case 0xC7: printf("RST \t0"); break;
        case 0xCF: printf("RST \t1"); break;
        case 0xD7: printf("RST \t2"); break;
        case 0xDF: printf("RST \t3"); break;
        case 0xE7: printf("RST \t4"); break;
        case 0xEF: printf("RST \t5"); break;
        case 0xF7: printf("RST \t6"); break;
        case 0xFF: printf("RST \t7"); break;
        case 0xE9: printf("PCHL"); break;

        /* STACK, I/O, AND MACHINE CONTROL GROUP */

		// PUSH rp - Push register pair to stack
        case 0xC5:
            Push(state, state->b, state->c);
			break;
        case 0xD5:
            Push(state, state->d, state->e);
			break;
        case 0xE5:
            Push(state, state->h, state->l);
			break;

		// PUSH PSW - Push processor status word
        case 0xF5:
            Push(state, state->a, *(unsigned char*)&state->cc);
			break;

		// POP rp - Pop top 2 bytes of stack to register pair
        case 0xC1:
            Pop(state, &state->b, &state->c);
			break;
        case 0xD1:
            Pop(state, &state->d, &state->e);
			break;
        case 0xE1:
            Pop(state, &state->h, &state->l);
			break;

		// POP PSW - Pop processor status word
        case 0xF1:
            Pop(state, &state->a,(unsigned char*) &state->cc);
			break;

		// XTHL - Exchange data at the top of the stack with data in the HL register pair
        case 0xE3:
            uint8_t h = state->h;
            uint8_t l = state->l;
            state->l = state->memory[state->sp];
            state->h = state->memory[state->sp+1];
            WriteMem(state, state->sp, l );
            WriteMem(state, state->sp+1, h );
			break;

		// SPHL - Moves the HL register pair to SP
        case 0xF9:
			state->sp = state->l | (state->h << 8);
			break;

		// IN port - Handles input from external hardware
		// not yet implemented
        case 0xDB:
			state->pc++;
			break;

		// OUT port - Handles output to external hardware
		// not yet implemented
        case 0xD3:
			state->pc++;
			break;

		// EI - Enable interrupts
        case 0xFB:
			state->int_enable = 1;
			break;

		// DI - Disable interrupts
        case 0xF3:
			state->int_enable = 0;
			break;

		// HLT - Halt (terminate program)
        case 0x76:
			exit(0);

		// NOP - No operation
        case 0x00:
			break;

		default: UnimplementedInstruction(state);
	}

	return cycles8080[*opcode];
}

int main (int argc, char**argv)
{
	int done = 0;
	int vblankcycles = 0;
	State8080* state = Init8080();

	ReadFileIntoMemoryAt(state, "invaders.h", 0);
	ReadFileIntoMemoryAt(state, "invaders.g", 0x800);
	ReadFileIntoMemoryAt(state, "invaders.f", 0x1000);
	ReadFileIntoMemoryAt(state, "invaders.e", 0x1800);

	while (done == 0)
	{
		done = Emulate8080Op(state);
	}

	return 0;
}
