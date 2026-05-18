#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

int main() {
    FILE *in = fopen("image.ppm", "rb");
    if (!in) {
        fprintf(stderr, "Failed to open image.ppm\n");
        return 1;
    }

    char header[1000];
    char comment[1000];
    char dimensions[1000];

    if (!fgets(header, sizeof(header), in)) {
        fprintf(stderr, "Failed to read PPM header\n");
        fclose(in);
        return 1;
    }

    if (!fgets(comment, sizeof(comment), in)) {
        fprintf(stderr, "Failed to read PPM comment line\n");
        fclose(in);
        return 1;
    }

    if (!fgets(dimensions, sizeof(dimensions), in)) {
        fprintf(stderr, "Failed to read image dimensions\n");
        fclose(in);
        return 1;
    }

    int width = -1;
    int height = -1;
    if (sscanf(dimensions, "%d %d", &width, &height) != 2) {
        fprintf(stderr, "Invalid dimensions line: %s", dimensions);
        fclose(in);
        return 1;
    }

    printf("width=%d, height=%d\n", width, height);
    fclose(in);

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

    SDL_DestroyWindow(pwindow);
    SDL_Quit();

    return 0;
}