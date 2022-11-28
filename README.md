# CS 467 Capstone Project - <br> Build an Emulator and Run Space Invaders

Goal: Create an Intel 8080 emulator in C/C++ that can disassemble a Space Invaders ROM file and play the game [1].

# Project Archive - Final

## Tested Platforms
1. Windows
2. Linux

## Installation / Run Instructions

### Using the latest GitHub release (Windows only)
1. Download the zip file for the [current release](). The release contains all the necessary dependencies (.dll), audio files, and ROM files.
2. Extract the contents of the the zip file to a location on your PC.
3. Open a terminal window in the project root directory and run the executable inside the program folder to start the emulator.

   ```
   $ ./main
   ```

### Compiling from the source code
#### Prerequisites
1. GCC 
2. G++
3. GNU Make
4. [Mingw-w64 through MSYS2](https://www.msys2.org/) (for Windows development only)
5. [SDL2](https://wiki.libsdl.org/SDL2/Installation)
6. [SDL_mixer](https://github.com/libsdl-org/SDL_mixer)
7. [Source Code]() (contains the necessary audio files and ROM files)

#### Steps
1. Install the prerequisite packages to your operating system. 
   
   - On Linux:
      - Install the libsdl2-dev and libsdl2-mixer-dev packages:

         ```
         $ sudo apt-get update
         $ sudo apt-get libsdl2-dev
         $ sudo apt-get libsdl2-mixer-dev
         ```
      - Install all other packages, if they are not already included by default. 

   - On Windows:
      - Install MSYS2 on your PC.
      - Make sure your system environment variables have the following Paths:
         - {msys64 program folder location}\mingw64\bin
         - {msys64 program folder location}\usr\bin

      - Install SDL2, SDL_mixer, and other development packages using the following commands on MSYS2:
         ```
         pacman -S mingw-w64-x86_64-toolchain
         pacman -S mingw-w64-x86_64-SDL2
         pacman -S mingw-w64-x86_64-SDL2_mixer
         ```

2. Once all the dependencies have been installed, go to the source code and open a terminal/command line window in the project's root directory.

3. Compile the program using make.

   ```
   $ make
   ```

4. Run the created binary/executable.

   ```
   $ ./main
   ```

## Expected Output

When you run the program, whether it be from the release version or by compiling from the source code, the result is a window opening with Space Invaders loaded on the screen. At this point the player can control the game using the mapped [keyboard controls](#controls). To close out of the game, the player must close out of the game window.

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
