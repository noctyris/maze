#ifndef UTILS_H
#define UTILS_H

#include "main.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE    10
#define WIDTH   800
#define HEIGHT  600

typedef struct {
    int x;
    int y;
} Coordinate;

void push(Coordinate** table, size_t* size, Coordinate c) {
    (*size)++;
    *table = realloc(*table, (*size) * sizeof(Coordinate));
    if (*table == NULL) {
        perror("Allocating error");
        exit(EXIT_FAILURE);
    }
    (*table)[*size - 1] = c;
}

void draw_filled_circle(SDL_Renderer* renderer, int cx, int cy, int radius, int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    for (int y = -radius; y <= radius; y++) {
        int dx = (int)sqrt(radius * radius - y * y);
        SDL_RenderDrawLine(renderer, cx - dx, cy + y, cx + dx, cy + y);
    }
}

Coordinate chooseRandomCoordinate(Coordinate* directions) {
    int randomIndex = rand() % 4;
    return directions[randomIndex];
}

Coordinate pop(Coordinate** table, size_t* size) {
    if (*size == 0) {
        fprintf(stderr,"Empty table");
        exit(EXIT_FAILURE);
    }
    Coordinate top = (*table)[*size - 1];
    (*size)--;
    *table = realloc(*table, (*size) * sizeof(Coordinate));
    if (*size > 0 && *table == NULL) {
        perror("Realocating error");
        exit(EXIT_FAILURE);
    }
    return top;
}

#endif
