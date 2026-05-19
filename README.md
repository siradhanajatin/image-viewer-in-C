# image-viewer-in-C
A custom image viewer in C that parses and displays binary PPM (Portable Pixelmap) images using the SDL2 (Simple DirectMedia Layer) library. I am using Windows and VS Code for creating this image viewer. 

## Tutorial on SDL3 Setup
The download and setup of SDL3 from "https://github.com/libsdl-org/SDL/blob/main/docs/INTRO-mingw.md".

## How the Code Works

- `iv.c` opens `image.ppm` in binary mode and reads the PPM header.
- It parses the `P6` format, width, height, and max color value.
- The program then reads RGB bytes one pixel at a time and draws them into an SDL surface.
- After drawing, it updates the window and stays open until the SDL quit event is received.

## SDL Library Notes

- `SDL_CreateWindow()` makes the display window.
- `SDL_GetWindowSurface()` lets the program write pixels directly to the window surface.
- `SDL_PollEvent()` listens for events like the window close button.

Useful references:
- SDL setup: https://github.com/libsdl-org/SDL/blob/main/docs/INTRO-mingw.md
- SDL window creation: https://wiki.libsdl.org/SDL_CreateWindow
- SDL event polling: https://wiki.libsdl.org/SDL_PollEvent
- SDL pixel mapping: https://wiki.libsdl.org/SDL_MapRGB

## Development History

- Started with a simple C prototype that opened `image.ppm` and read the header values.
- Found that the first version closed the file before reading pixel data, so the next change kept the file open for the full image read.
- Replaced stdin-based `getchar()` reads with file-based `fgetc(in)` for correct binary pixel reading.
- Implemented SDL window creation and surface drawing so each RGB triplet is mapped to a pixel on screen.
- Improved header parsing to skip comments and whitespace, making the reader more robust for P6 PPM files.
- Added an SDL event loop so the window stays open until the user clicks the quit button instead of exiting after a fixed delay.

## Run Commands

- Build: `cmake --build build`
- Run from the project root: `./build/iv`

