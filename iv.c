#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

int main() {

    printf("Helow, The World!");
    SDL_Window *pwindow = SDL_CreateWindow("Image Viewer", 900, 600, 0);

    return 0;
}