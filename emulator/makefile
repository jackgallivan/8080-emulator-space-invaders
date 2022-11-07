# Phony targets
.PHONY: all clean
# Directories make should search
VPATH = ../disassembler/

# Vars for compiling C
CC = gcc
CFLAGS = -fdiagnostics-color=always -Wall -std=c17 -g -O0 -DMAIN_EMULATOR
# Vars for compiling with debug defs
DEFFLAGS = -DPRINTOPS -DPRINTPSW
COMPILE_DEBUG = $(COMPILE.c) $(DEFFLAGS) $(OUTPUT_OPTION) $<

# All program targets
PROGRAMS = emulator emulator_debug
# Object file names
emulator_OBJS = emulator.o emu_utils.o
emulator_debug_OBJS = emulator_debug.o emu_utils_debug.o disassembler_debug.o
ALL_OBJS = $(disassembler_OBJS) $(emulator_OBJS) $(emulator_debug_OBJS)

# compile all programs
all: $(PROGRAMS)

# compile emulator
emulator: $(emulator_OBJS)
emulator.o: emulator.c emulator.h emu_utils.h
emu_utils.o: emu_utils.c emu_utils.h

# compile emulator_debug
emulator_debug: $(emulator_debug_OBJS)
emulator_debug.o: emulator.c emulator.h emu_utils.h disassembler.h
	$(COMPILE_DEBUG)
emu_utils_debug.o: emu_utils.c emu_utils.h
	$(COMPILE_DEBUG)
disassembler_debug.o: disassembler.c disassembler.h
	$(COMPILE_DEBUG)

# delete all created files
clean:
	rm -f $(PROGRAMS) $(ALL_OBJS)
