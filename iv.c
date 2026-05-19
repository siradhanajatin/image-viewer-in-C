#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <SDL3/SDL.h>

static int next_token(FILE *in, char *buf, size_t bufsize) {
    int c;
    while ((c = fgetc(in)) != EOF) {
        if (c == '#') {
            while ((c = fgetc(in)) != EOF && c != '\n');
            continue;
        }
        if (!isspace(c)) {
            size_t i = 0;
            buf[i++] = (char)c;
            while (i + 1 < bufsize) {
                c = fgetc(in);
                if (c == EOF || isspace(c)) break;
                buf[i++] = (char)c;
            }
            buf[i] = '\0';
            return 1;
        }
    }
    return 0;
}

int main() {
    FILE *in = fopen("image.ppm", "rb");
    if (!in) {
        fprintf(stderr, "Failed to open image.ppm\n");
        return 1;
    }

    char token[128];
    next_token(in, token, sizeof(token));

    next_token(in, token, sizeof(token));
    int width = atoi(token);

    next_token(in, token, sizeof(token));
    int height = atoi(token);

    next_token(in, token, sizeof(token));
    int maxval = atoi(token);

    SDL_Window *pwindow = SDL_CreateWindow("Image Viewer", width, height, 0);
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

    SDL_Rect pixel = (SDL_Rect){0,0,1,1};
    Uint32 color = 0;
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            int ri = fgetc(in);
            int gi = fgetc(in);
            int bi = fgetc(in);
            Uint8 r = (Uint8)ri;
            Uint8 g = (Uint8)gi;
            Uint8 b = (Uint8)bi;
            color = SDL_MapSurfaceRGB(psurface, r, g, b);
            pixel.x = x;
            pixel.y = y;
            SDL_FillSurfaceRect(psurface, &pixel, color);
        }
    }

    SDL_UpdateWindowSurface(pwindow);

    SDL_Delay(5000);

    SDL_DestroyWindow(pwindow);
    SDL_Quit();

    return 0;
}