#include "ui.h"

void draw_filled_circle(SDL_Renderer* renderer, int cx, int cy, int radius, int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    for (int y = -radius; y <= radius; y++) {
        int dx = (int)sqrt(radius * radius - y * y);
        SDL_RenderDrawLine(renderer, cx - dx, cy + y, cx + dx, cy + y);
    }
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

int isCellOk(SDL_Renderer* renderer, int x, int y) {
    Uint32 pixel = get_renderer_pixel(renderer, x, y);
    Uint8 r, g, b, a;
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, 1, 1, 32, SDL_PIXELFORMAT_RGBA32);
    get_rgba(pixel, surface->format, &r, &g, &b, &a);
    SDL_FreeSurface(surface);

    if (r == WALLC && g == WALLC && b == WALLC) {
        return 1;
    } else {
        return 0;
    }
}
