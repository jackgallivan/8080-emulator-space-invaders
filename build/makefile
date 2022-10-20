VPATH = ../disassembler/;../emulator/
CC=gcc
CFLAGS=-fdiagnostics-color=always -Wall -std=c17 -g -O0
DEFFLAGS=-DPRINTOPS -DPRINTPSW

# disassembler
disassembler: disassembler.c disassembler.h
	$(CC) $(CFLAGS) -o $@ $^

# emulator
emulator: 8080emulator.c 8080emu_utils.c 8080emulator.h 8080emu_utils.h
	$(CC) $(CFLAGS) -o $@ $^

emu_debug: 8080emulator.c 8080emu_utils.c 8080emulator.h 8080emu_utils.h disassembler.c disassembler.h
	$(CC) $(CFLAGS) $(DEFFLAGS) -o $@ $^

# clean
clean:
	rm disassembler emulator emu_debug
