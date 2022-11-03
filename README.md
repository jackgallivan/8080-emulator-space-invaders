# CS 467 Capstone Project - <br> Build an Emulator and Run Space Invaders

Goal: Create an Intel 8080 emulator in C/C++ that can disassemble a Space Invaders ROM file and play the game.[^1]

# Project Archive - Midpoint

### Prerequisites

1. GCC
2. GNU make
3. [Source code](https://github.com/jackgallivan/8080-emulator-space-invaders/releases/tag/v0.1)

## Running the emulator, with debug output

The emulator, without debug output enabled, will run continuously without any output, so this will compile the emulator with debug output. 

### Compile Instructions

1. Open a terminal in the project's `build/` directory

   ```
   $ cd build/
   ```

2. Compile the emulator with debug output

   ```
   $ make emulator_debug
   ```

### Run the program

3. Run the created binary

   ```
   $ ./emulator_debug
   ```

### Expected Output

The program will start printing the debug output as it reads the opcodes from Space Invaders. The first ten lines of output will look like this:

```
$ ./emulator_debug
0000 NOP                                REGISTERS:  A=00 B=00 C=00 D=00 E=00 H=00 L=00 SP=0000 PC=0001      FLAGS:  - - - -- --
0001 NOP                                REGISTERS:  A=00 B=00 C=00 D=00 E=00 H=00 L=00 SP=0000 PC=0002      FLAGS:  - - - -- --
0002 NOP                                REGISTERS:  A=00 B=00 C=00 D=00 E=00 H=00 L=00 SP=0000 PC=0003      FLAGS:  - - - -- --
0003 JMP        0x18D4                  REGISTERS:  A=00 B=00 C=00 D=00 E=00 H=00 L=00 SP=0000 PC=18d4      FLAGS:  - - - -- --
18D4 LXI        SP,0x2400               REGISTERS:  A=00 B=00 C=00 D=00 E=00 H=00 L=00 SP=2400 PC=18d7      FLAGS:  - - - -- --
18D7 MVI        B,0x00                  REGISTERS:  A=00 B=00 C=00 D=00 E=00 H=00 L=00 SP=2400 PC=18d9      FLAGS:  - - - -- --
18D9 CALL       0x01E6                  REGISTERS:  A=00 B=00 C=00 D=00 E=00 H=00 L=00 SP=23fe PC=01e6      FLAGS:  - - - -- --
01E6 LXI        D,0x1B00                REGISTERS:  A=00 B=00 C=00 D=1b E=00 H=00 L=00 SP=23fe PC=01e9      FLAGS:  - - - -- --
01E9 LXI        H,0x2000                REGISTERS:  A=00 B=00 C=00 D=1b E=00 H=20 L=00 SP=23fe PC=01ec      FLAGS:  - - - -- --
01EC JMP        0x1A32                  REGISTERS:  A=00 B=00 C=00 D=1b E=00 H=20 L=00 SP=23fe PC=1a32      FLAGS:  - - - -- --
...
```

Most of the first 30000 instructions are spent in a loop around 1A5F, where the program is copying data to the screen. About 50000 instructions in, the program will get stuck in this infinite loop[^2]:

```
...
0ADA LDA        0x20C0                  REGISTERS:  A=40 B=00 C=00 D=1f E=b0 H=3e L=01 SP=23fe PC=0add      FLAGS:  - - - -- --
0ADD ANA        A                       REGISTERS:  A=40 B=00 C=00 D=1f E=b0 H=3e L=01 SP=23fe PC=0ade      FLAGS:  - - - -- --
0ADE JNZ        0x0ADA                  REGISTERS:  A=40 B=00 C=00 D=1f E=b0 H=3e L=01 SP=23fe PC=0ada      FLAGS:  - - - -- --
...
```

I *don't* recommend waiting to see the output get there, as printing the debug output makes it take **at least a few minutes**. Once we get to the point in this project where the Space Invaders arcade cabinet hardware is fully emulated, it will become clear that the program is waiting for user input at this point.

## Running the disassembler, standalone

### Compile Instructions

1. Open a terminal in the project's `build/` directory

   ```
   $ cd build/
   ```

2. Compile the disassembler

   ```
   $ make disassembler
   ```

### Run the program

3. Run the created binary, with the concatenated invaders ROM file as an argument.

   ```
   $ ./disassembler ../invaders/invaders
   ```

### Expected Output

The disassembler will disassemble the invaders ROM, printing each instruction, proceeded by its address in the ROM. You can compare your output with ours [here](invaders/invaders-disassembled.txt).

**Note:** *chunks of data, where no opcodes are meant to exist, will still be interpreted as opcodes anyway, and will print as invalid instructions, which is expected.*

[^1]: [EECS Project Portal - Build an Emulator and Run Space Invaders ROM](https://eecs.oregonstate.edu/capstone/submission/pages/viewSingleProject.php?id=UTiao6aM3hcgDDJu)

[^2]: [Emulator 101 - Finishing the CPU emulator](http://www.emulator101.com/finishing-the-cpu-emulator.html)
