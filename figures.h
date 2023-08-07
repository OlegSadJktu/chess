#ifndef FIGURES_H
#define FIGURES_H

#include <math.h>
#include "field.h"
/* #include "figures.h" */

enum FigureType {
    PAWN,
    KING, 
    QUEEN,
    ROOK, 
    BISHOP,
    HORSE,
};

typedef struct Pos Pos;
typedef struct Field Field;


enum Team {
    BLACK = 0, WHITE = 1,
};

typedef int (*checker_f)(Pos*, Pos*, Field*, enum Team);

struct Figure {
    enum FigureType type;
    enum Team team;
	int moves;
};

char getCharByType(enum FigureType type);

checker_f checker(enum FigureType type);

checker_f checkerAttack(enum FigureType);

#endif 
