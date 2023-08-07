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

char *getNameByTeam(enum Team team) {
    switch(team) {
        case WHITE:
            return "WHITE";
        case BLACK:
            return "BLACK";
    }
    return "ERROR";
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

static struct Figure *findFigure(struct Field *field, struct Pos *pos) {
	return field->cells[possToIndex(pos)].piece;
}


int samePos(struct Pos *p1, struct Pos *p2) {
    return p1->x == p2->x && p1->y == p2->y;
}

static int pawnMoveChecker(struct Pos *pos, struct Pos *move, struct Field *field, enum Team team) {
    if (samePos(pos, move)) return 0;
	struct Figure *fig = findFigure(field, pos);
    int dx, dy;
    deltas(pos, move, &dx, &dy);
    dy = dy * (team == WHITE ? 1 : -1);
	if (fig->moves == 0) {
		return (dy == 1 || dy == 2) && dx == 0;
	}
	return dy == 1 && dx == 0;
    /* if (dy == 1 && dx == 0) { */
    /*     return 1; */
    /* } */
    /* return 0; */
}

int kingMoveChecker(struct Pos *pos, struct Pos *move, struct Field *field, enum Team team) {
    if (samePos(pos, move)) return 0;
    int dx = pos->x - move->x, dy = pos->y - move->y;
    dx = abs(dx);
    dy = abs(dy);
    if (dx < 2 && dy < 2) {
        return 1;
    }
    return 0;
}


static int rookMoveChecker(struct Pos *pos, struct Pos *move, struct Field *field, enum Team team) {
    if (samePos(pos, move)) return 0;
    int dx, dy;
    absDeltas(pos, move, &dx, &dy);
    if (dx < 1 || dy < 1) {
        return 1;
    }
    return 0;
}

static int bishopMoveChecker(struct Pos *pos, struct Pos *move, struct Field *field, enum Team team) {
    if (samePos(pos, move)) return 0;
    int dx, dy;
    absDeltas(pos, move, &dx, &dy);
    if (dx == dy) {
        return 1;
    }
    return 0;
}

static int queenMoveChecker(struct Pos *pos, struct Pos *move, struct Field *field, enum Team team) {
    if (samePos(pos, move)) return 0;
    if (rookMoveChecker(pos, move, field, team) || bishopMoveChecker(pos, move, field, team)) {
        return 1;
    }
    return 0;
}

static int horseMoveChecker(struct Pos *pos, struct Pos *move, struct Field *field, enum Team team) {
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

static int allMoveAllowed(struct Pos *pos, struct Pos *move, struct Field *field, enum Team team) {
    if (samePos(pos, move)) return 0;
    return 1;
}


static int pawnAttackChecker(struct Pos *pos, struct Pos *move, struct Field *field, enum Team team) {
    enum Team eTeam = field->cells[possToIndex(move)].piece->team;
    // if same team
    if (eTeam == team) return 0;
    int dx, dy;
    deltas(pos, move, &dx, &dy);
    dy = dy * (team == WHITE ? 1 : -1);
    if ((dx == -1 && dy == 1) || (dx == 1 && dy == 1)) {
        return 1;
    }
    return 0;
}

static int kingAttackChecker(struct Pos *pos, struct Pos *move, struct Field *field, enum Team team) {
    enum Team eTeam = field->cells[possToIndex(move)].piece->team;
    return eTeam != team && kingMoveChecker(pos, move, field, team);
}

static int queenAttackChecker(struct Pos *pos, struct Pos *move, struct Field *field, enum Team team) {
    enum Team eTeam = field->cells[possToIndex(move)].piece->team;
    return eTeam != team && queenMoveChecker(pos, move, field, team);
}

static int bishopAttackChecker(struct Pos *pos, struct Pos *move, struct Field *field, enum Team team) {
    enum Team eTeam = field->cells[possToIndex(move)].piece->team;
    return eTeam != team && bishopMoveChecker(pos, move, field, team);

}

static int rookAttackChecker(struct Pos *pos, struct Pos *move, struct Field *field, enum Team team) {
    enum Team eTeam = field->cells[possToIndex(move)].piece->team;
    return eTeam != team && rookMoveChecker(pos, move, field, team);

}

static int horseAttackChecker(struct Pos *pos, struct Pos *move, struct Field *field, enum Team team) {
    enum Team eTeam = field->cells[possToIndex(move)].piece->team;
    return eTeam != team && horseMoveChecker(pos, move, field, team);

}

checker_f checkerAttack(enum FigureType type) {
    switch (type) {
        case PAWN:
            return pawnAttackChecker;
        case KING:
            return kingAttackChecker;
        case QUEEN:
            return queenAttackChecker;
        case BISHOP:
            return bishopAttackChecker;
        case ROOK:
            return rookAttackChecker;
        case HORSE:
            return horseAttackChecker;
    }
    return allMoveAllowed;
}

checker_f checker(enum FigureType type) {
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


