#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "shared.h"

void push(Coordinate** table, size_t* size, Coordinate c) {
    (*size)++;
    *table = realloc(*table, (*size) * sizeof(Coordinate));
    if (*table == NULL) {
        perror("Allocating error");
        exit(EXIT_FAILURE);
    }
    (*table)[*size - 1] = c;
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
