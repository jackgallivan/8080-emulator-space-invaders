# Phony targets
.PHONY: all clean cleanobjs
# Directories make should search
VPATH = ../disassembler/:../emulator/
# Vars for compiling
CC = gcc
CFLAGS = -fdiagnostics-color=always -Wall -std=c17 -g -O0
# Vars for compilining with debug defs
DEFFLAGS = -DPRINTOPS -DPRINTPSW
COMPILE_DEBUG = $(COMPILE.c) $(DEFFLAGS) $(OUTPUT_OPTION) $<
# All program targets
PROGRAMS = disassembler 8080emulator 8080emulator_debug 8080emulator_cpudiag
# Object file names
disassembler_OBJS = disassembler.o
emulator_OBJS = 8080emulator.o 8080emu_utils.o
emulator_debug_OBJS = 8080emulator_debug.o 8080emu_utils_debug.o disassembler_debug.o
emulator_cpudiag_OBJS = 8080emulator_cpudiag.o 8080emu_utils_cpudiag.o disassembler_debug.o
ALL_OBJS = $(disassembler_OBJS) $(emulator_OBJS) $(emulator_debug_OBJS) $(emulator_cpudiag_OBJS)

# compile all programs
all: $(PROGRAMS)

# compile disassembler
disassembler: $(disassembler_OBJS)
disassembler.o: disassembler.c disassembler.h

# compile 8080emulator
8080emulator: $(emulator_OBJS)
8080emulator.o: 8080emulator.c 8080emulator.h 8080emu_utils.h
8080emu_utils.o: 8080emu_utils.c 8080emu_utils.h

# compile 8080emulator_debug
8080emulator_debug: $(emulator_debug_OBJS)
8080emulator_debug.o: 8080emulator.c 8080emulator.h 8080emu_utils.h disassembler.h
	$(COMPILE_DEBUG)
8080emu_utils_debug.o: 8080emu_utils.c 8080emu_utils.h
	$(COMPILE_DEBUG)
disassembler_debug.o: disassembler.c disassembler.h
	$(COMPILE_DEBUG)

# compile 8080emulator_cpudiag
8080emulator_cpudiag: $(emulator_cpudiag_OBJS)
8080emulator_cpudiag.o: 8080emulator.c 8080emulator.h 8080emu_utils.h disassembler.h
	$(COMPILE_DEBUG) -DCPUDIAG
8080emu_utils_cpudiag.o: 8080emu_utils.c 8080emu_utils.h
	$(COMPILE_DEBUG) -DCPUDIAG

# delete all created files
clean: cleanobjs
	rm -f $(PROGRAMS)
# delete only object files
cleanobjs:
	rm -f $(ALL_OBJS)
