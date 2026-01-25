# Simple PPM Image Viewer

A lightweight, C-based image viewer designed specifically for PPM (Portable Pixel Map) files. Unlike standard viewers, this project implements its own PPM parsing logic for both P3 (ASCII) and P6 (Binary) formats, rendering them using the SDL2 library.

## Features

- **Custom Parsing:** Manually parses PPM file headers and pixel data without relying on external image loading libraries like `SDL_image`.
- **Format Support:** 
  - **P3:** ASCII-based PPM files.
  - **P6:** Binary-based PPM files.
- **Visualization:** Renders images pixel-by-pixel onto an SDL window.

## Prerequisites

You need to have the SDL2 development library installed on your system.

### Linux (Debian/Ubuntu)
```bash
sudo apt install libsdl2-dev
```

### Linux (Fedora)
```bash
sudo dnf install SDL2-devel
```

### Linux (Arch)
```bash
sudo pacman -S sdl2
```

## Compilation

Compile the source code using `gcc`. Note that only the core `SDL2` library is required.

```bash
gcc iV.c -o iV -lSDL2
```

## Usage

Run the executable and provide the path to a `.ppm` file as an argument:

```bash
./iV filename.ppm
```

### Example

```bash
./iV sample.ppm
```

## How It Works

1. **Header Parsing:** The program reads the PPM header to identify the format (P3 vs P6), dimensions, and color depth.
2. **Comment Handling:** It is capable of skipping comments (lines starting with `#`) within the file header.
3. **Rendering:** 
   - Creates an SDL window matching the image dimensions.
   - Iterates through the pixel data, mapping RGB values to the window surface.
   - For P3, it reads integer values; for P6, it reads raw bytes.

## Controls

- Close the window to exit the application.
