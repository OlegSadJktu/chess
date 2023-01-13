#ifndef FIGURES_H
#define FIGURES_H

enum FigureType {
    PAWN,
    KING, 
    QUEEN,
    ROOK, 
    BISHOP,
    HORSE,
};

enum Team {
    BLACK, WHITE,
};

struct Figure {
    enum FigureType type;
    enum Team team;
};

char getCharByType(enum FigureType type);

#endif 
