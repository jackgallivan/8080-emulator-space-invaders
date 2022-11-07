# Phony targets
.PHONY: all clean
# Vars for compiling C
CC = gcc
CFLAGS = -fdiagnostics-color=always -Wall -std=c17 -g -O0 -DMAIN_DISASSEMBLER
# All program targets
PROGRAMS = disassembler
# Object file names
OBJS = disassembler.o

# compile disassembler
disassembler: $(disassembler_OBJS)
disassembler.o: disassembler.c disassembler.h

# delete all created files
clean:
	rm -f $(PROGRAMS) $(OBJS)
