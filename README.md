# Minesweeper

**Minesweeper** is a fully-interactive C++ implementation of the classic puzzle game, brought to life with **SFML** for real-time graphics and event handling.

---

## **Overview**

This project replicates the core gameplay of **Minesweeper**—a tile-based game where players uncover all non-mine squares without triggering hidden mines. It's built using **C++** and **SFML (Simple and Fast Multimedia Library)** and includes features like dynamic board generation, configurable grid size, and GUI-based user input.

---

## **Key Features**

- **Custom Board Configuration**: Load different grid sizes through a `.cfg` file.  
- **Interactive Welcome Screen**: Prompt for and render the player’s name before gameplay.  
- **Real-Time Tile Interaction**: Click to reveal, flag, or reset the game board.  
- **Win/Loss Logic**: Tracks mine hits and tile uncovering, with victory or game-over states.  
- **Polished SFML GUI**: Uses clean text, fonts, and positioning to guide the player.

---

## **Architecture**

The project is composed of the following major components:

### 1. **`main.cpp`**
- Entry point of the application.  
- Reads board config from `files/board_config.cfg`.  
- Handles user name input, initializes the SFML window, and manages the main game loop.

### 2. **`Game.h`**
- Core game logic class.  
- Manages the grid, mine placement, tile reveals, flagging, and game state (ongoing, win, lose).

### 3. **`ScreenGenerator.h`**
- Responsible for visual rendering of the game board.  
- Draws tiles, numbers, mines, and flags based on current state.

### 4. **`board_config.cfg`**
- Defines the board size (columns and rows).  
- Allows easy switching between game difficulty levels or testing layouts.

---

## **User Interaction**

- **Left Click**: Reveal a tile.  
- **Right Click**: Flag or unflag a tile.  
- **Text Input**: Enter name before starting the game.  
- **Restart/Win/Lose Screens**: Displayed dynamically through SFML text rendering.

---

## **Data Files**

- `files/board_config.cfg` – Custom board dimensions (2 lines: columns, then rows)  
- `files/font.ttf` – Used for all in-game and GUI text rendering

---

## **Build Instructions**

To compile and run the game:

```bash
mkdir build && cd build
cmake ..
make
./Minesweeper
