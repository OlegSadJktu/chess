#ifndef FIELD_H
#define FIELD_H

#include <stdlib.h>
#include "figures.h"

#define FIELD_SIZE 64

struct Cell {
    struct Figure *piece;
};

struct Field {
    /* char name[20]; */
    struct Cell cells[FIELD_SIZE];
    int curx, cury;

};

typedef struct Pos {
    int x, y;
} Pos;

struct Field *createDefaultField();

int posToIndex(int x, int y);

int charsToIndex(char[2]);

int indexToPos(int, int*, int*);


#endif
