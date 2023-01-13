#include "figures.h"

char getCharByType(enum FigureType type) {
    switch(type) {
        case PAWN:
            return 'p';
        case KING:
            return 'k';
        case QUEEN:
            return 'q';
        case ROOK:
            return 'r';
        case BISHOP:
            return 'b';
        case HORSE:
            return 'h';
    }
    return -1;
}
