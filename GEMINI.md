# Project Overview
This project is a simple C-based image viewer using SDL2 and SDL2_image. It initializes a window and renderer, loads an image (defaulting to `sample.png`), and displays it centered on a dark grey background.

## Main Technologies
- **Language:** C
- **Libraries:** 
  - SDL2 (Core functionality and window management)
  - SDL2_image (Image loading for PNG, JPG, etc.)

# Building and Running

## Prerequisites
Ensure the development libraries for SDL2 and SDL2_image are installed.
- On Debian/Ubuntu: `sudo apt install libsdl2-dev libsdl2-image-dev`
- On Fedora: `sudo dnf install SDL2-devel SDL2_image-devel`
- On Arch: `sudo pacman -S sdl2 sdl2_image`

## Compilation
Compile the source using `gcc`, linking both SDL2 libraries:

```bash
gcc imageViewer.c -o imageViewer -lSDL2 -lSDL2_image
```

## Running
After compilation, execute the binary. It will attempt to load `sample.png` from the current directory.

```bash
./imageViewer
```

# Development Conventions

## Code Style
- Standard C syntax.
- SDL initialization checks with descriptive error messages.
- Uses `SDL_Renderer` for efficient hardware-accelerated rendering.
- Handles the window close event (`SDL_QUIT`) to exit cleanly.

## Key Files
- `imageViewer.c`: Main source code.
- `sample.png`: Default image file used for demonstration.