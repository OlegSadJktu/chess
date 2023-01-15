#ifndef FIGURES_H
#define FIGURES_H

#include <math.h>
#include "field.h"

enum FigureType {
    PAWN,
    KING, 
    QUEEN,
    ROOK, 
    BISHOP,
    HORSE,
};

typedef struct Pos Pos;

typedef int (*checker_f)(Pos*, Pos*);

enum Team {
    BLACK, WHITE,
};

struct Figure {
    enum FigureType type;
    enum Team team;
};

char getCharByType(enum FigureType type);

checker_f checker(enum FigureType type);

#endif 
