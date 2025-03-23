#include "functions.h"

void push(Coordinate** table, size_t* size, Coordinate c) {
    Coordinate* new_table = realloc(*table, (*size + 1) * sizeof(Coordinate));
    if (new_table == NULL) {
        perror("Memory allocation error");
        free(*table);
        exit(EXIT_FAILURE);
    }
    *table = new_table;

    (*table)[*size] = c;
    (*size)++;
}

Coordinate pop(Coordinate** table, size_t* size) {
    if (*size == 0) {
        fprintf(stderr,"Empty table");
        exit(EXIT_FAILURE);
    }
    Coordinate top = (*table)[*size - 1];
    (*size)--;
    Coordinate* new_table = realloc(*table, (*size) * sizeof(Coordinate));
    if (*size > 0 && new_table == NULL) {
        perror("Memory reallocation error");
        exit(EXIT_FAILURE);
    }
    *table = new_table;

    return top;
}

int find(Coordinate coord, Coordinate* table, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (table[i].x == coord.x && table[i].y == coord.y) {
            return 1;
        }
    }
    return 0;
}

void add_parent(ParentEntry** table, size_t* size, Coordinate key, Coordinate value) {
    ParentEntry* new_table = realloc(*table, (*size + 1) * sizeof(ParentEntry));
    if (!new_table) {
        perror("Memory allocation error");
        free(*table);
        exit(EXIT_FAILURE);
    }
    *table = new_table;

    (*table)[*size].key = key;
    (*table)[*size].value = value;
    (*size)++;
}

Coordinate find_parent(ParentEntry* table, size_t size, Coordinate key) {
    for (size_t i = 0; i < size; i++) {
        if (table[i].key.x == key.x && table[i].key.y == key.y) {
            return table[i].value;
        }
    }
    return key;
}

float heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1-x2) + abs(y1-y2);
}
