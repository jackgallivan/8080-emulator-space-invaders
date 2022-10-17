VPATH = ../disassembler/;../emulator/
CC=gcc
CFLAGS=-fdiagnostics-color=always -Wall -std=c17 -g -O0
disassembler_objects = disassembler.o
emulator_objects = 8080emulator.o 8080emu_utils.o
objects = $(disassembler_objects) $(emulator_objects)

# disassembler
disassembler: $(disassembler_objects)
	$(CC) $(CFLAGS) $^ -o $@

disassembler.o: disassembler.c disassembler.h
	$(CC) -c $(CFLAGS) $< -o $@

# emulator
8080emulator: $(emulator_objects)
	$(CC) $(CFLAGS) $^ -o $@

8080emulator.o: 8080emulator.c 8080emulator.h 8080emu_utils.h
	$(CC) -c $(CFLAGS) $< -o $@
8080emu_utils.o: 8080emu_utils.c 8080emu_utils.h
	$(CC) -c $(CFLAGS) $< -o $@

# clean
clean:
	rm disassembler 8080emulator $(objects)