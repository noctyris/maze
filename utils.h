#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define SIZE    10
#define WIDTH   800
#define HEIGHT  600

typedef struct {
    int x;
    int y;
} Coordinate;

void draw_filled_circle(SDL_Renderer* renderer, int cx, int cy, int radius, int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    for (int y = -radius; y <= radius; y++) {
        int dx = (int)sqrt(radius * radius - y * y);
        SDL_RenderDrawLine(renderer, cx - dx, cy + y, cx + dx, cy + y);
    }
    SDL_RenderPresent(renderer);
}

Coordinate chooseRandomCoordinate(Coordinate* directions) {
    int randomIndex = rand() % 4;
    return directions[randomIndex];
}

void maze(SDL_Renderer* renderer, Coordinate* directions) {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    for (int x = SIZE; x < WIDTH; x += SIZE * 2) {
        for (int y = SIZE; y < HEIGHT; y += SIZE * 2) {
            SDL_Rect rect = {x, y, SIZE, SIZE};
            SDL_RenderFillRect(renderer, &rect);

            Coordinate randomCoord = chooseRandomCoordinate(directions);
            SDL_Rect adjacentRect = {x + randomCoord.x * SIZE, y + randomCoord.y * SIZE, SIZE, SIZE};
            SDL_RenderFillRect(renderer, &adjacentRect);
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 200, 50, 255);
    SDL_RenderFillRect(renderer, &(SDL_Rect){0, 0, SIZE, SIZE});

    SDL_SetRenderDrawColor(renderer, 200, 50, 0, 255);
    SDL_RenderFillRect(renderer, &(SDL_Rect){WIDTH - SIZE, HEIGHT - SIZE, SIZE, SIZE});
}

Uint32 get_renderer_pixel(SDL_Renderer* renderer, int x, int y) {
    Uint32 pixel;
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, 1, 1, 32, SDL_PIXELFORMAT_RGBA32);
    if (SDL_RenderReadPixels(renderer, &(SDL_Rect){x, y, 1, 1}, SDL_PIXELFORMAT_RGBA32, surface->pixels, surface->pitch) != 0) {
        printf("Erreur SDL_RenderReadPixels: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return 0;
    }

    pixel = *(Uint32 *)surface->pixels;
    SDL_FreeSurface(surface);
    return pixel;
}

void get_rgba(Uint32 pixel, SDL_PixelFormat *format, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a) {
    SDL_GetRGBA(pixel, format, r, g, b, a);
}

void draw_sprite(SDL_Renderer* renderer, int x, int y) {
    draw_filled_circle(renderer, x + SIZE / 2 - 1, y + SIZE / 2 - 1, 3, 255, 255, 0);
}

void remove_sprite(SDL_Renderer* renderer, int x, int y) {
    Uint32 pixel = get_renderer_pixel(renderer, x, y);
    Uint8 r, g, b, a;
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, 1, 1, 32, SDL_PIXELFORMAT_RGBA32);
    get_rgba(pixel, surface->format, &r, &g, &b, &a);
    SDL_FreeSurface(surface);

    draw_filled_circle(renderer, x + SIZE / 2 - 1, y + SIZE / 2 - 1, 3, r, g, b);
}

#endif
