# Phony targets
.PHONY: all clean cleanobjs
# Directories make should search
VPATH = ../disassembler/:../emulator/:../machine
# Vars for compiling
CC = gcc
CFLAGS = -fdiagnostics-color=always -Wall -std=c17 -g -O0
# Vars for compilining with debug defs
DEFFLAGS = -DPRINTOPS -DPRINTPSW
COMPILE_DEBUG = $(COMPILE.c) $(DEFFLAGS) $(OUTPUT_OPTION) $<
# All program targets
PROGRAMS = disassembler emulator emulator_debug machine
# Object file names
disassembler_OBJS = disassembler.o
emulator_OBJS = emulator.o emu_utils.o
emulator_debug_OBJS = emulator_debug.o emu_utils_debug.o disassembler_debug.o
machine_OBJS = machine.o graphics.o
ALL_OBJS = $(disassembler_OBJS) $(emulator_OBJS) $(emulator_debug_OBJS) $(machine_OBJS)

# compile all programs
all: $(PROGRAMS)

# compile disassembler
disassembler: $(disassembler_OBJS)
disassembler.o: disassembler.c disassembler.h

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

# compile machine
machine: $(machine_OBJS)

# delete all created files
clean: cleanobjs
	rm -f $(PROGRAMS)
# delete only object files
cleanobjs:
	rm -f $(ALL_OBJS)
