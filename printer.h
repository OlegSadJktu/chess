#ifndef PRINTER_H
#define PRINTER_H

#include <curses.h>
#include "field.h"

typedef struct Offsets {
    int top, left;
} Offsets;

/* static void printCell(Offsets*, Pos*, struct Cell*); */

void printFieldBounds(int maxx, int maxy);

void printField(int maxx, int maxy, struct Field*);

#endif
