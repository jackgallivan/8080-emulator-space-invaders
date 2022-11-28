# CS 467 Capstone Project - <br> Build an Emulator and Run Space Invaders

Goal: Create an Intel 8080 emulator in C/C++ that can disassemble a Space Invaders ROM file and play the game [1].

# Project Archive - Final

## Tested Platforms
1. Windows
2. Linux

*Note that all necessary dependencies, audio files and ROM files are included in the release folders for both versions.

## Installation Instructions

1. Download the zip file for the [current release]() for your respective operating system.
2. Extract the contents of the the zip file to a location on your PC.
3. Run "./main" inside the program folder to start the emulator.

## Compile Instructions

### Prerequisites
1. GCC 
2. G++
3. GNU Make
4. SDL2
5. SDL_mixer
6. [MSYS2](https://www.msys2.org/) (For Windows Development only)

## Steps
1. Open a terminal in the project's root directory

2. Compile the program.

   ```
   $ make
   ```

3. Run the created binary/executable.

   ```
   $ ./main
   ```

4. To close the emulator, close the program window.

## How to Play
The goal of the game is to shoot down all the invaders before they either shoot your ship down or before they reach the bottom of the screen. The more invaders you shoot down, the faster the game becomes.

### Controls - Start Game

| Keyboard key | Action                                    |
| ------------ | ----------------------------------------- |
| C            | Insert Coin                               |
| 1            | 1-Player Game Start (must insert 1 coin)  |
| 2            | 2-Player Game Start (must insert 2 coins) |

### Controls - Player 1 Controls

| Keyboard key | Action     |
| ------------ | ---------- |
| W            | Shoot      |
| A            | Move Left  |
| D            | Move Right |

### Controls - Player 2 Controls

| Keyboard key | Action     |
| ------------ | ---------- |
| Up Arrow     | Shoot      |
| Left Arrow   | Move Left  |
| Right Arrow  | Move Right |

### Screenshots

![Space Invaders title screen](/img/game-screenshot-0.png?raw=true "Screenshot - Title Screen") <br>
##### Space Invaders - Title Screen <br>
![Space Invaders insert coin screen with typo](/img/game-screenshot-3.png?raw=true "Screenshot - Insert Coin Screen")
##### Space Invaders - Insert Coin Screen <br>
![Space Invaders in-game screenshot](/img/game-screenshot-1.png?raw=true "Screenshot - Gameplay #1")
![Space Invaders in-game screenshot](/img/game-screenshot-2.png?raw=true "Screenshot - Gameplay #2") <br>
##### Space Invaders - Gameplay Screenshots

---

## References

[1] W. Pfeil, "Build an Emulator and Run Space Invaders ROM," *EECS Project Portal*. [Online]. Available: https://eecs.oregonstate.edu/capstone/submission/pages/viewSingleProject.php?id=UTiao6aM3hcgDDJu. [Accessed: 31-Oct-2022].

[2] K.P. Miller, "Finishing the CPU emulator," *Emulator 101*. [Online]. Available: http://www.emulator101.com/finishing-the-cpu-emulator.html. [Accessed: 31-Oct-2022].
