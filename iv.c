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
    if (!next_token(in, token, sizeof(token))) {
        fprintf(stderr, "Failed to read PPM magic\n");
        fclose(in);
        return 1;
    }

    if (token[0] != 'P' || token[1] != '6') {
        fprintf(stderr, "Unsupported PPM format: %s\n", token);
        fclose(in);
        return 1;
    }

    if (!next_token(in, token, sizeof(token))) {
        fprintf(stderr, "Failed to read image width\n");
        fclose(in);
        return 1;
    }
    int width = atoi(token);

    if (!next_token(in, token, sizeof(token))) {
        fprintf(stderr, "Failed to read image height\n");
        fclose(in);
        return 1;
    }
    int height = atoi(token);

    if (!next_token(in, token, sizeof(token))) {
        fprintf(stderr, "Failed to read maxval\n");
        fclose(in);
        return 1;
    }
    int maxval = atoi(token);

    SDL_Window *pwindow = SDL_CreateWindow("Image Viewer", width, height, 0);
    if (!pwindow) {
        fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
        fclose(in);
        SDL_Quit();
        return 1;
    }

    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

    SDL_Rect pixel = (SDL_Rect){0,0,1,1};
    Uint32 color = 0;
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            int ri = fgetc(in);
            int gi = fgetc(in);
            int bi = fgetc(in);

            if (ri == EOF || gi == EOF || bi == EOF) {
                fprintf(stderr, "Unexpected EOF while reading pixel data\n");
                fclose(in);
                SDL_DestroyWindow(pwindow);
                SDL_Quit();
                return 1;
            }

            Uint8 r = (Uint8)ri;
            Uint8 g = (Uint8)gi;
            Uint8 b = (Uint8)bi;

            color = SDL_MapSurfaceRGB(psurface, r, g, b);
            pixel.x = x;
            pixel.y = y;
            SDL_FillSurfaceRect(psurface, &pixel, color);
        }
    }

    fclose(in);
    SDL_UpdateWindowSurface(pwindow);

    int app_running = 1;
    while (app_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                app_running = 0;
            }
        }
        SDL_Delay(100);
    }

    SDL_DestroyWindow(pwindow);
    SDL_Quit();

    return 0;
}