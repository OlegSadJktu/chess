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


static void deltas(struct Pos *p1, struct Pos *p2, int *dx, int *dy) {
    *dy = p1->y - p2->y;
    *dx = p1->x - p2->x;
}

static void absDeltas(struct Pos *p1, struct Pos *p2, int *dx, int *dy) {
    deltas(p1, p2, dx, dy);
    *dy = abs(*dy);
    *dx = abs(*dx);
}


int samePos(struct Pos *p1, struct Pos *p2) {
    return p1->x == p2->x && p1->y == p2->y;
}

static int pawnMoveChecker(struct Pos *pos, struct Pos *move) {
    if (samePos(pos, move)) return 0;
    int dx, dy;
    deltas(pos, move, &dx, &dy);
    if (dy == 1 && dx == 0) {
        return 1;
    }
    return 0;
}

int kingMoveChecker(struct Pos *pos, struct Pos *move) {
    if (samePos(pos, move)) return 0;
    int dx = pos->x - move->x, dy = pos->y - move->y;
    dx = abs(dx);
    dy = abs(dy);
    if (dx < 2 && dy < 2) {
        return 1;
    }
    return 0;
}


static int rookMoveChecker(struct Pos *pos, struct Pos *move) {
    if (samePos(pos, move)) return 0;
    int dx, dy;
    absDeltas(pos, move, &dx, &dy);
    if (dx < 1 || dy < 1) {
        return 1;
    }
    return 0;
}

static int bishopMoveChecker(struct Pos *pos, struct Pos *move) {
    if (samePos(pos, move)) return 0;
    int dx, dy;
    absDeltas(pos, move, &dx, &dy);
    if (dx == dy) {
        return 1;
    }
    return 0;
}

static int queenMoveChecker(struct Pos *pos, struct Pos *move) {
    if (samePos(pos, move)) return 0;
    if (rookMoveChecker(pos, move) || bishopMoveChecker(pos, move)) {
        return 1;
    }
    return 0;
}

static int horseMoveChecker(struct Pos *pos, struct Pos *move) {
    if (samePos(pos, move)) return 0;
    int dx = pos->x - move->x;
    int dy = pos->y - move->y;
    dx = abs(dx); 
    dy = abs(dy);
    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
        return 1;
    }
    return 0;
}

static int allMoveAllowed(struct Pos *pos, struct Pos *move) {
    if (samePos(pos, move)) return 0;
    return 1;
}


checker_f checker(enum FigureType type) {
/* int (*checker(enum FigureType type))(Pos*, Pos *) { */
    switch (type) {
        case PAWN:
            return pawnMoveChecker;
        case KING:
            return kingMoveChecker;
        case QUEEN:
            return queenMoveChecker;
        case BISHOP:
            return bishopMoveChecker;
        case ROOK:
            return rookMoveChecker;
        case HORSE:
            return horseMoveChecker;
    }
    return allMoveAllowed;
}

/* int (*checker(enum FigureType type))(Pos, Pos) { */
/*     return pawnMoveChecker; */

/* } */

