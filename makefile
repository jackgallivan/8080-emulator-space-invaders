# Phony targets
.PHONY: all clean
# Directories make should search
VPATH = emulator/:machine/

# Vars for compiling C
CC = gcc
CFLAGS = -fdiagnostics-color=always -Wall -std=c17 -g -O0
# Vars for compiling C++
CXX = g++
CXXFLAGS = -fdiagnostics-color=always -Wall -std=c++17 -g -O0
ifeq ($(OS),Windows_NT)
	LDLIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer
else
	LDLIBS = -lSDL2main -lSDL2 -lSDL2_mixer
endif

# All program targets
PROGRAMS = invaders
# Object file names
OBJS = main.o machine.o graphics.o audio.o io.o emulator.o emu_utils.o

# make binaries then discard object files
all: $(PROGRAMS) cleanobjs

# compile main
invaders: $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@
main.o: main.cpp machine.hpp
machine.o: machine.cpp machine.hpp audio.hpp emulator.h emu_utils.h
graphics.o: graphics.cpp machine.hpp
audio.o: audio.cpp machine.hpp audio.hpp
io.o: io.cpp machine.hpp
emulator.o: emulator.c emulator.h emu_utils.h
emu_utils.o: emu_utils.c emu_utils.h

# delete all created files
clean:
	rm -f $(PROGRAMS) $(OBJS)

cleanobjs:
	rm -f $(OBJS)
