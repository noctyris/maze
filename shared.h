#ifndef DEP_H
#define DEP_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include "priorityqueue.c"

#define HEIGHT  600
#define WIDTH   800
#define WALLC   200
#define SIZE    8

typedef struct {
    int x;
    int y;
} Coordinate;

typedef struct {
    Coordinate key;
    Coordinate value;
} ParentEntry;

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
