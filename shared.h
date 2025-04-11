#ifndef SHARED_H
#define SHARED_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include "priorityqueue.c"

#define WALLC   200
#define FONT "UbuntuMono.ttf"

typedef struct {
    int x;
    int y;
} Coordinate;

typedef struct {
    Coordinate key;
    Coordinate value;
} ParentEntry;

int SIZE, WIDTH = 80, HEIGHT = 60;

int isClick;
Coordinate clickStart = {0, 0};
Coordinate clickEnd = {0, 0};
Coordinate mousePos;

Coordinate chooseRandomCoordinate(Coordinate* directions) {
    int randomIndex = rand() % 4;
    return directions[randomIndex];
}

Coordinate DIRECTIONS[] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
};

#endif
