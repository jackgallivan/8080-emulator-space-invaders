# CS 467 Capstone Project - <br> Build an Emulator and Run Space Invaders

Goal: Create an Intel 8080 emulator in C/C++ that can disassemble a Space Invaders ROM file and play the game [1].

# Project Archive - Final

## Tested Platforms
1. Windows
2. Linux

## Installation / Run Instructions

### Using the latest GitHub release
1. Download the zip file for the [current release]() for your respective operating system. Each release version contains all the necessary dependencies, audio files, and ROM files.
2. Extract the contents of the the zip file to a location on your PC.
3. Open a terminal window in the project root directory and run the executable/binary inside the program folder to start the emulator.

   ```
   $ ./main
   ```

   If on Windows, you may opt to double click the executable.

### Compiling from the source code
#### Prerequisites
1. GCC 
2. G++
3. GNU Make
4. [SDL2](https://wiki.libsdl.org/SDL2/Installation)
5. [SDL_mixer](https://github.com/libsdl-org/SDL_mixer)
6. [MSYS2](https://www.msys2.org/) (For Windows Development only)
7. [Source Code]() (contains the necessary audio files and ROM files)

#### Steps
1. Open a terminal in the project's root directory

2. Compile the program.

   ```
   $ make
   ```

3. Run the created binary/executable.

   ```
   $ ./main
   ```

   If on Windows, you may opt to double click the executable file.

## Expected Output

When you run the program either from the release version or by compiling from the source code, the result is a window opening with Space Invaders loaded on the screen. At this point the player can control the game using the mapped [keyboard controls](#controls). To close out of the game, the player must close out of the game window.

#### Space Invaders - Title Screen <br>
![Space Invaders title screen](/img/game-screenshot-0.png?raw=true "Screenshot - Title Screen") <br>

#### Space Invaders - Insert Coin Screen <br>
![Space Invaders insert coin screen with typo](/img/game-screenshot-3.png?raw=true "Screenshot - Insert Coin Screen") <br>

#### Space Invaders - Gameplay Screenshots <br>
![Space Invaders in-game screenshot](/img/game-screenshot-1.png?raw=true "Screenshot - Gameplay #1")
![Space Invaders in-game screenshot](/img/game-screenshot-2.png?raw=true "Screenshot - Gameplay #2") <br>


## How to Play
The goal of the game is to get a high score by shooting down all the invaders before they either shoot your ship down or before they reach the bottom of the screen. The more invaders you shoot down, the more difficult the game becomes. The game ends when you run out of ships and get a "Game Over".

<a name="controls"></a>

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


---

## References

[1] W. Pfeil, "Build an Emulator and Run Space Invaders ROM," *EECS Project Portal*. [Online]. Available: https://eecs.oregonstate.edu/capstone/submission/pages/viewSingleProject.php?id=UTiao6aM3hcgDDJu. [Accessed: 31-Oct-2022].

[2] K.P. Miller, "Finishing the CPU emulator," *Emulator 101*. [Online]. Available: http://www.emulator101.com/finishing-the-cpu-emulator.html. [Accessed: 31-Oct-2022].
