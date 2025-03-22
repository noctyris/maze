#ifndef UI_H
#define UI_H

#include "shared.h"

void draw_filled_circle(SDL_Renderer* renderer, int cx, int cy, int radius, int r, int g, int b);

void maze(SDL_Renderer* renderer, Coordinate* directions);

Uint32 get_renderer_pixel(SDL_Renderer* renderer, int x, int y);

void get_rgba(Uint32 pixel, SDL_PixelFormat *format, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a);

void draw_sprite(SDL_Renderer* renderer, int x, int y);

void remove_sprite(SDL_Renderer* renderer, int x, int y);

int isCellOk(SDL_Renderer* renderer, int x, int y);

#endif
