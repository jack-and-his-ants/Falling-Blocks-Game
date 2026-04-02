# Falling Blocks Game - Classic Tetris-Like Game

[![Language](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Library](https://img.shields.io/badge/library-ncurses-green.svg)](https://invisible-island.net/ncurses/)

A terminal-based Tetris inspired game written in C, featuring multithreaded input handling, progressive difficulty, and persistent high scores.

## ✨ Features

- **7 Classic Tetriminos** - I, O, T, L, J, S, Z shapes with unique colors
- **Smooth Controls** - Move, rotate, and hard drop with instant response
- **Progressive Difficulty** - Gravity increases with time
- **Persistent High Scores** - Best score saved with player name
- **Thread-Safe Input** - Separate thread for non-blocking keyboard input
- **Memory Safe** - Full NULL checks, no memory leaks
- **Color Terminal UI** - Beautiful colored blocks using ncurses

## Controls

| Key | Action |
|-----|--------|
| `←` / `→` | Move left / right |
| `↑` | Rotate clockwise |
| `↓` | Soft drop |
| `Space` | Hard drop |
| `q` | Quit game |

## 🚀 Installation

### Prerequisites

```bash
# Ubuntu/Debian
sudo apt-get install libncurses-dev build-essential

# macOS
brew install ncurses
```
### Building
```bash
git clone https://github.com/jack-and-his-ants/Falling-Blocks-Game.git
cd falling-blocks
make
./tetris
```
## 🧠 Technical Details

The project was designed with a modular architecture and includes:

- Multithreaded input system using pthreads
- Mutex-protected shared input buffer
- Dynamic memory management
- Terminal rendering using ncurses windows
- Collision detection system
- Line clearing algorithm
- Increasing difficulty algorithm
## Project Structure
```txt
falling-blocks/
├── include/          # Header files
├── src/              # Source files
├── Makefile          # Build configuration
├── README.md         # This file
└── LICENCE
```
## Licence 
MIT License - feel free to use and modify!

## What I Learned

This project helped me understand:

- Multithreading and synchronization (mutexes)
- Game loop architecture
- Time-based movement vs frame-based movement
- Memory management in C
- Terminal graphics using ncurses
- Designing modular programs in C

## Acknowledgements
- Inspired by Alexey Pajitnov's original Tetris®
- Built with the ncurses library