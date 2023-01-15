#ifndef FIELD_H
#define FIELD_H

#include <stdlib.h>
#include "figures.h"

#define FIELD_SIZE 64

enum CursorMode {
    NORMAL, SELECT,
};

struct Cell {
    struct Figure *piece;
};

struct Field {
    struct Cell cells[FIELD_SIZE];
    int curx, cury;
    // default -1
    int selectedPiece;

};

struct Pos {
    int x, y;
};

struct Field *createDefaultField();

int posToIndex(int x, int y);

int charsToIndex(char[2]);

int indexToPos(int, struct Pos*);

void selectF(struct Field*);

int samePos(struct Pos *p1, struct Pos *p2);

#endif
