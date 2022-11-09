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
LDLIBS = -lmingw32 -lSDL2main -lSDL2

# All program targets
PROGRAMS = main
# Object file names
OBJS = main.o machine.o graphics.o audio.o io.o emulator.o emu_utils.o

# compile main
main: $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@
main.o: main.cpp machine.hpp emulator.h emu_utils.h
machine.o: machine.cpp machine.hpp
graphics.o: graphics.cpp machine.hpp
audio.o: audio.cpp audio.hpp machine.hpp
io.o: io.cpp machine.hpp audio.hpp
emulator.o: emulator.c emulator.h emu_utils.h
emu_utils.o: emu_utils.c emu_utils.h

# delete all created files
clean:
	rm -f $(PROGRAMS) $(OBJS)
