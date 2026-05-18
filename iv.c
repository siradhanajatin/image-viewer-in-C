#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

int main() {

    const int width = 900;
    const int height = 600;
    
    SDL_Window *pwindow = SDL_CreateWindow("Image Viewer", width, height, 0);
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);


    Uint8 r,g,b;
    r=0x1A;
    g=b=0x00;
    Uint32 color = SDL_MapSurfaceRGB(psurface, r, g, b);  
    
    SDL_Rect pixel = (SDL_Rect){0,0,1,1};
    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            pixel.x=x;
            pixel.y=y;
            SDL_FillSurfaceRect(psurface, &pixel, color);
        }
    }
    SDL_UpdateWindowSurface(pwindow);

    SDL_Delay(3000);


    return 0;
}