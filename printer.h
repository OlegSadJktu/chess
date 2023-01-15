#ifndef PRINTER_H
#define PRINTER_H

#include <curses.h>
#include "field.h"
#include "figures.h"
#include "logger.h"

#define CURSOR_COLOR 1
#define MOVE_COLOR 2
#define CAN_MOVE 3

void setMaxxy(int x, int y) ;

typedef struct Offsets {
    int top, left;
} Offsets;


void printFieldBounds(int maxx, int maxy);

void printField(int maxx, int maxy, struct Field*);

#endif
