#ifndef DEP_H
#define DEP_H

#define SIZE    7
#define WIDTH   800
#define HEIGHT  600
#define WALLC   200

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
