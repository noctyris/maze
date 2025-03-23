#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "shared.h"

void push(Coordinate** table, size_t* size, Coordinate c);

Coordinate pop(Coordinate** table, size_t* size);

int find(Coordinate coord, Coordinate* table, size_t size);

void add_parent(ParentEntry** table, size_t* size, Coordinate key, Coordinate value);

Coordinate find_parent(ParentEntry* table, size_t size, Coordinate key);

#endif
