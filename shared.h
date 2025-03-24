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

#define WALLC   200
#define HEIGHT  60
#define WIDTH   80
#define SIZE    10

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
