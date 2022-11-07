#include "disassembler.h"

/*
	disassemble_8080_op:
	Disassemble and print the assembly instruction at the location in
	*code_buffer with an offset of pc bytes.

	*code_buffer: pointer to assembled 8080 binary code
	pc: offset (in bytes) within the code

	return: the size (in bytes) of the instruction pc refers to

	NOTE:
		Data interleaved within valid instructions will not be disassembled
		properly (The data will be processed as invalid or erroneous
		assembly instructions).

		For a correct interpretation of Space Invaders code, see
		http://computerarcheology.com/Arcade/SpaceInvaders/Code.html
*/
int disassemble_8080_op(unsigned char *code_buffer, int pc)
{
	unsigned char *code = &code_buffer[pc];
	int op_bytes = 1;
	printf("%04X ", pc);
	switch (*code)
	{
		/* DATA TRANSFER GROUP */

		case 0x7F: printf("MOV \tA,A      "); break;
		case 0x78: printf("MOV \tA,B      "); break;
		case 0x79: printf("MOV \tA,C      "); break;
		case 0x7A: printf("MOV \tA,D      "); break;
		case 0x7B: printf("MOV \tA,E      "); break;
		case 0x7C: printf("MOV \tA,H      "); break;
		case 0x7D: printf("MOV \tA,L      "); break;
		case 0x47: printf("MOV \tB,A      "); break;
		case 0x40: printf("MOV \tB,B      "); break;
		case 0x41: printf("MOV \tB,C      "); break;
		case 0x42: printf("MOV \tB,D      "); break;
		case 0x43: printf("MOV \tB,E      "); break;
		case 0x44: printf("MOV \tB,H      "); break;
		case 0x45: printf("MOV \tB,L      "); break;
		case 0x4F: printf("MOV \tC,A      "); break;
		case 0x48: printf("MOV \tC,B      "); break;
		case 0x49: printf("MOV \tC,C      "); break;
		case 0x4A: printf("MOV \tC,D      "); break;
		case 0x4B: printf("MOV \tC,E      "); break;
		case 0x4C: printf("MOV \tC,H      "); break;
		case 0x4D: printf("MOV \tC,L      "); break;
		case 0x57: printf("MOV \tD,A      "); break;
		case 0x50: printf("MOV \tD,B      "); break;
		case 0x51: printf("MOV \tD,C      "); break;
		case 0x52: printf("MOV \tD,D      "); break;
		case 0x53: printf("MOV \tD,E      "); break;
		case 0x54: printf("MOV \tD,H      "); break;
		case 0x55: printf("MOV \tD,L      "); break;
		case 0x5F: printf("MOV \tE,A      "); break;
		case 0x58: printf("MOV \tE,B      "); break;
		case 0x59: printf("MOV \tE,C      "); break;
		case 0x5A: printf("MOV \tE,D      "); break;
		case 0x5B: printf("MOV \tE,E      "); break;
		case 0x5C: printf("MOV \tE,H      "); break;
		case 0x5D: printf("MOV \tE,L      "); break;
		case 0x67: printf("MOV \tH,A      "); break;
		case 0x60: printf("MOV \tH,B      "); break;
		case 0x61: printf("MOV \tH,C      "); break;
		case 0x62: printf("MOV \tH,D      "); break;
		case 0x63: printf("MOV \tH,E      "); break;
		case 0x64: printf("MOV \tH,H      "); break;
		case 0x65: printf("MOV \tH,L      "); break;
		case 0x6F: printf("MOV \tL,A      "); break;
		case 0x68: printf("MOV \tL,B      "); break;
		case 0x69: printf("MOV \tL,C      "); break;
		case 0x6A: printf("MOV \tL,D      "); break;
		case 0x6B: printf("MOV \tL,E      "); break;
		case 0x6C: printf("MOV \tL,H      "); break;
		case 0x6D: printf("MOV \tL,L      "); break;
		case 0x7E: printf("MOV \tA,M      "); break;
		case 0x46: printf("MOV \tB,M      "); break;
		case 0x4E: printf("MOV \tC,M      "); break;
		case 0x56: printf("MOV \tD,M      "); break;
		case 0x5E: printf("MOV \tE,M      "); break;
		case 0x66: printf("MOV \tH,M      "); break;
		case 0x6E: printf("MOV \tL,M      "); break;
		case 0x77: printf("MOV \tM,A      "); break;
		case 0x70: printf("MOV \tM,B      "); break;
		case 0x71: printf("MOV \tM,C      "); break;
		case 0x72: printf("MOV \tM,D      "); break;
		case 0x73: printf("MOV \tM,E      "); break;
		case 0x74: printf("MOV \tM,H      "); break;
		case 0x75: printf("MOV \tM,L      "); break;
		case 0x3E: printf("MVI \tA,0x%02X   ", code[1]); op_bytes = 2; break;
		case 0x06: printf("MVI \tB,0x%02X   ", code[1]); op_bytes = 2; break;
		case 0x0E: printf("MVI \tC,0x%02X   ", code[1]); op_bytes = 2; break;
		case 0x16: printf("MVI \tD,0x%02X   ", code[1]); op_bytes = 2; break;
		case 0x1E: printf("MVI \tE,0x%02X   ", code[1]); op_bytes = 2; break;
		case 0x26: printf("MVI \tH,0x%02X   ", code[1]); op_bytes = 2; break;
		case 0x2E: printf("MVI \tL,0x%02X   ", code[1]); op_bytes = 2; break;
		case 0x36: printf("MVI \tM,0x%02X   ", code[1]); op_bytes = 2; break;
		case 0x01: printf("LXI \tB,0x%02X%02X ", code[2], code[1]); op_bytes = 3; break;
		case 0x11: printf("LXI \tD,0x%02X%02X ", code[2], code[1]); op_bytes = 3; break;
		case 0x21: printf("LXI \tH,0x%02X%02X ", code[2], code[1]); op_bytes = 3; break;
		case 0x31: printf("LXI \tSP,0x%02X%02X", code[2], code[1]); op_bytes = 3; break;
		case 0x3A: printf("LDA \t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0x32: printf("STA \t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0x2A: printf("LHLD\t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0x22: printf("SHLD\t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0x0A: printf("LDAX\tB        "); break;
		case 0x1A: printf("LDAX\tD        "); break;
		case 0x02: printf("STAX\tB        "); break;
		case 0x12: printf("STAX\tD        "); break;
		case 0xEB: printf("XCHG\t         "); break;

		/* ARITHMETIC GROUP */

		case 0x87: printf("ADD \tA        "); break;
		case 0x80: printf("ADD \tB        "); break;
		case 0x81: printf("ADD \tC        "); break;
		case 0x82: printf("ADD \tD        "); break;
		case 0x83: printf("ADD \tE        "); break;
		case 0x84: printf("ADD \tH        "); break;
		case 0x85: printf("ADD \tL        "); break;
		case 0x86: printf("ADD \tM        "); break;
		case 0xC6: printf("ADI \t0x%02X     ", code[1]); op_bytes = 2; break;
		case 0x8F: printf("ADC \tA        "); break;
		case 0x88: printf("ADC \tB        "); break;
		case 0x89: printf("ADC \tC        "); break;
		case 0x8A: printf("ADC \tD        "); break;
		case 0x8B: printf("ADC \tE        "); break;
		case 0x8C: printf("ADC \tH        "); break;
		case 0x8D: printf("ADC \tL        "); break;
		case 0x8E: printf("ADC \tM        "); break;
		case 0xCE: printf("ACI \t0x%02X     ", code[1]); op_bytes = 2; break;
		case 0x97: printf("SUB \tA        "); break;
		case 0x90: printf("SUB \tB        "); break;
		case 0x91: printf("SUB \tC        "); break;
		case 0x92: printf("SUB \tD        "); break;
		case 0x93: printf("SUB \tE        "); break;
		case 0x94: printf("SUB \tH        "); break;
		case 0x95: printf("SUB \tL        "); break;
		case 0x96: printf("SUB \tM        "); break;
		case 0xD6: printf("SUI \t0x%02X     ", code[1]); op_bytes = 2; break;
		case 0x9F: printf("SBB \tA        "); break;
		case 0x98: printf("SBB \tB        "); break;
		case 0x99: printf("SBB \tC        "); break;
		case 0x9A: printf("SBB \tD        "); break;
		case 0x9B: printf("SBB \tE        "); break;
		case 0x9C: printf("SBB \tH        "); break;
		case 0x9D: printf("SBB \tL        "); break;
		case 0x9E: printf("SBB \tM        "); break;
		case 0xDE: printf("SBI \t0x%02X     ", code[1]); op_bytes = 2; break;
		case 0x3C: printf("INR \tA        "); break;
		case 0x04: printf("INR \tB        "); break;
		case 0x0C: printf("INR \tC        "); break;
		case 0x14: printf("INR \tD        "); break;
		case 0x1C: printf("INR \tE        "); break;
		case 0x24: printf("INR \tH        "); break;
		case 0x2C: printf("INR \tL        "); break;
		case 0x34: printf("INR \tM        "); break;
		case 0x3D: printf("DCR \tA        "); break;
		case 0x05: printf("DCR \tB        "); break;
		case 0x0D: printf("DCR \tC        "); break;
		case 0x15: printf("DCR \tD        "); break;
		case 0x1D: printf("DCR \tE        "); break;
		case 0x25: printf("DCR \tH        "); break;
		case 0x2D: printf("DCR \tL        "); break;
		case 0x35: printf("DCR \tM        "); break;
		case 0x03: printf("INX \tB        "); break;
		case 0x13: printf("INX \tD        "); break;
		case 0x23: printf("INX \tH        "); break;
		case 0x33: printf("INX \tSP       "); break;
		case 0x0B: printf("DCX \tB        "); break;
		case 0x1B: printf("DCX \tD        "); break;
		case 0x2B: printf("DCX \tH        "); break;
		case 0x3B: printf("DCX \tSP       "); break;
		case 0x09: printf("DAD \tB        "); break;
		case 0x19: printf("DAD \tD        "); break;
		case 0x29: printf("DAD \tH        "); break;
		case 0x39: printf("DAD \tSP       "); break;
		case 0x27: printf("DAA \t         "); break;

		/* LOGICAL GROUP */

		case 0xA7: printf("ANA \tA        "); break;
		case 0xA0: printf("ANA \tB        "); break;
		case 0xA1: printf("ANA \tC        "); break;
		case 0xA2: printf("ANA \tD        "); break;
		case 0xA3: printf("ANA \tE        "); break;
		case 0xA4: printf("ANA \tH        "); break;
		case 0xA5: printf("ANA \tL        "); break;
		case 0xA6: printf("ANA \tM        "); break;
		case 0xE6: printf("ANI \t0x%02X     ", code[1]); op_bytes = 2; break;
		case 0xAF: printf("XRA \tA        "); break;
		case 0xA8: printf("XRA \tB        "); break;
		case 0xA9: printf("XRA \tC        "); break;
		case 0xAA: printf("XRA \tD        "); break;
		case 0xAB: printf("XRA \tE        "); break;
		case 0xAC: printf("XRA \tH        "); break;
		case 0xAD: printf("XRA \tL        "); break;
		case 0xAE: printf("XRA \tM        "); break;
		case 0xEE: printf("XRI \t0x%02X     ", code[1]); op_bytes = 2; break;
		case 0xB7: printf("ORA \tA        "); break;
		case 0xB0: printf("ORA \tB        "); break;
		case 0xB1: printf("ORA \tC        "); break;
		case 0xB2: printf("ORA \tD        "); break;
		case 0xB3: printf("ORA \tE        "); break;
		case 0xB4: printf("ORA \tH        "); break;
		case 0xB5: printf("ORA \tL        "); break;
		case 0xB6: printf("ORA \tM        "); break;
		case 0xF6: printf("ORI \t0x%02X     ", code[1]); op_bytes = 2; break;
		case 0xBF: printf("CMP \tA        "); break;
		case 0xB8: printf("CMP \tB        "); break;
		case 0xB9: printf("CMP \tC        "); break;
		case 0xBA: printf("CMP \tD        "); break;
		case 0xBB: printf("CMP \tE        "); break;
		case 0xBC: printf("CMP \tH        "); break;
		case 0xBD: printf("CMP \tL        "); break;
		case 0xBE: printf("CMP \tM        "); break;
		case 0xFE: printf("CPI \t0x%02X     ", code[1]); op_bytes = 2; break;
		case 0x07: printf("RLC \t         "); break;
		case 0x0F: printf("RRC \t         "); break;
		case 0x17: printf("RAL \t         "); break;
		case 0x1F: printf("RAR \t         "); break;
		case 0x2F: printf("CMA \t         "); break;
		case 0x3F: printf("CMC \t         "); break;
		case 0x37: printf("STC \t         "); break;

		/* BRANCH GROUP */

		case 0xC3: printf("JMP \t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0xDA: printf("JC  \t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0xD2: printf("JNC \t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0xCA: printf("JZ  \t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0xC2: printf("JNZ \t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0xF2: printf("JP  \t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0xFA: printf("JM  \t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0xEA: printf("JPE \t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0xE2: printf("JPO \t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0xCD: printf("CALL\t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0xDC: printf("CC  \t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0xD4: printf("CNC \t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0xCC: printf("CZ  \t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0xC4: printf("CNZ \t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0xF4: printf("CP  \t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0xFC: printf("CM  \t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0xEC: printf("CPE \t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0xE4: printf("CPO \t0x%02X%02X   ", code[2], code[1]); op_bytes = 3; break;
		case 0xC9: printf("RET \t         "); break;
		case 0xD8: printf("RC  \t         "); break;
		case 0xD0: printf("RNC \t         "); break;
		case 0xC8: printf("RZ  \t         "); break;
		case 0xC0: printf("RNZ \t         "); break;
		case 0xF0: printf("RP  \t         "); break;
		case 0xF8: printf("RM  \t         "); break;
		case 0xE8: printf("RPE \t         "); break;
		case 0xE0: printf("RPO \t         "); break;
		case 0xC7: printf("RST \t0        "); break;
		case 0xCF: printf("RST \t1        "); break;
		case 0xD7: printf("RST \t2        "); break;
		case 0xDF: printf("RST \t3        "); break;
		case 0xE7: printf("RST \t4        "); break;
		case 0xEF: printf("RST \t5        "); break;
		case 0xF7: printf("RST \t6        "); break;
		case 0xFF: printf("RST \t7        "); break;
		case 0xE9: printf("PCHL\t         "); break;

		/* STACK, I/O, AND MACHINE CONTROL GROUP */

		case 0xC5: printf("PUSH\tB        "); break;
		case 0xD5: printf("PUSH\tD        "); break;
		case 0xE5: printf("PUSH\tH        "); break;
		case 0xF5: printf("PUSH\tPSW      "); break;
		case 0xC1: printf("POP \tB        "); break;
		case 0xD1: printf("POP \tD        "); break;
		case 0xE1: printf("POP \tH        "); break;
		case 0xF1: printf("POP \tPSW      "); break;
		case 0xE3: printf("XTHL\t         "); break;
		case 0xF9: printf("SPHL\t         "); break;
		case 0xDB: printf("IN  \t0x%02X     ", code[1]); op_bytes = 2; break;
		case 0xD3: printf("OUT \t0x%02X     ", code[1]); op_bytes = 2; break;
		case 0xFB: printf("EI  \t         "); break;
		case 0xF3: printf("DI  \t         "); break;
		case 0x76: printf("HLT \t         "); break;
		case 0x00: printf("NOP \t         "); break;
		default: printf("ERROR: INVALID INSTRUCTION: 0x%02X", code[0]); break;
	}
#ifndef PRINTOPS
	printf("\n");
#endif

	return op_bytes;
}

#ifdef MAIN_DISASSEMBLER
int main(int argc, char **argv)
{
	FILE *f = fopen(argv[1], "rb");
	if (f == NULL)
	{
		printf("ERROR: Couldn't open %s\n", argv[1]);
		exit(1);
	}

	// Get file size and read file into buffer
	fseek(f, 0L, SEEK_END);
	int fsize = ftell(f);
	fseek(f, 0L, SEEK_SET);

	unsigned char *buffer = malloc(fsize);

	fread(buffer, fsize, 1, f);
	fclose(f);

	int pc = 0;

	while (pc < fsize)
	{
		pc += disassemble_8080_op(buffer, pc);
	}
	return 0;
}
#endif
