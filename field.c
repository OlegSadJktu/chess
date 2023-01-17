#include "field.h"

static struct Figure *createFigure(enum Team team, enum FigureType type) {
    struct Figure *figure = malloc(sizeof(struct Figure));
    figure->team = team;
    figure->type = type;
    return figure;
};

void createFigures(struct Cell *cells, enum Team team) {
    char pos[2] = "a0";
    if (team == WHITE) {
        pos[1] = '1';
    } else {
        pos[1] = '8';
    }
    enum FigureType types[SIDE_SIZE] = {BISHOP, HORSE, ROOK, KING, QUEEN, ROOK, HORSE, BISHOP};
    for (int i = 0; i < SIDE_SIZE; i++) {
        cells[charsToIndex(pos)].piece = createFigure(team, types[i]);
        pos[0] += 1;
    }
}

struct Field *createDefaultField() {
    struct Field *field = malloc(sizeof(struct Field));
    field->selectedPiece = -1;
    struct Cell *cells = field->cells;
    char pos[2] = "a2";

    for (int i = 0; i < SIDE_SIZE; i++) {
        cells[charsToIndex(pos)].piece = createFigure(WHITE, PAWN);
        /* logInt("char", pos[0]); */
        logInfo(pos);
        pos[0] = pos[0] + 1;
    }
    pos[0] = 'a'; pos[1] = '7';
    for (int i = 0; i < SIDE_SIZE; i++) {
        cells[charsToIndex(pos)].piece = createFigure(BLACK, PAWN);
        pos[0] += 1;
    }
    createFigures(cells, WHITE);
    createFigures(cells, BLACK);

/*     field->cells[charsToIndex("a1")].piece = createFigure(WHITE,KING); */
/*     field->cells[charsToIndex("b1")].piece = createFigure(WHITE,QUEEN); */
/*     field->cells[charsToIndex("c1")].piece = createFigure(WHITE,HORSE); */
/*     field->cells[charsToIndex("d1")].piece = createFigure(WHITE,BISHOP); */
/*     field->cells[charsToIndex("e1")].piece = createFigure(WHITE,ROOK); */
/*     field->cells[charsToIndex("f1")].piece = createFigure(WHITE,PAWN); */

/*     field->cells[charsToIndex("a8")].piece = createFigure(BLACK,KING); */
/*     field->cells[charsToIndex("b8")].piece = createFigure(BLACK,QUEEN); */
/*     field->cells[charsToIndex("c8")].piece = createFigure(BLACK,HORSE); */
/*     field->cells[charsToIndex("d8")].piece = createFigure(BLACK,BISHOP); */
/*     field->cells[charsToIndex("e8")].piece = createFigure(BLACK,ROOK); */
/*     field->cells[charsToIndex("f8")].piece = createFigure(BLACK,PAWN); */
    return field;
}

// IN LOWERCASE
int charsToIndex(char pos[2]) {
    char sym = pos[0];
    char num = pos[1];
    if (sym > 'h' || sym < 'a' || num > '8' || num < '1') {
        return -1;
    }
    int x = sym - 'a';
    int y = 7 - (num - '1');
    return posToIndex(x, y);
}

int posToIndex(int x, int y) {
    if (x > 7 || x < 0 || y > 7 || y < 0) {
        return -1;
    }
    return y * 8 + x;
}

int possToIndex(struct Pos* pos) {
    return posToIndex(pos->x, pos->y);
}

int indexToPos(int index, struct Pos *pos) {
    if (index > FIELD_SIZE - 1 || index < 0) {
        return -1;
    }
    pos->x = index % 8;
    pos->y = index / 8;
    return index;
}

static int curToIndex(struct Field *field) {
    return posToIndex(field->curx, field->cury);
}

void selectF(struct Field *field) {
    int index = curToIndex(field);
    struct Figure *fig = field->cells[index].piece;
    if (field->selectedPiece == -1) {
        if (fig != NULL) {
            field->selectedPiece = index;
        }
        return;
    } 
    int selInd = field->selectedPiece;
    struct Figure *selected = field->cells[selInd].piece;
    struct Pos selPos;
    struct Pos curPos = {field->curx, field->cury};
    indexToPos(selInd, &selPos);
    if (selInd == index) {
        field->selectedPiece = -1;
        return;
    }
    if (fig == NULL && checker(selected->type)(&selPos, &curPos, field, selected->team)) {
        field->cells[index].piece 
            = field->cells[field->selectedPiece].piece;
        field->cells[field->selectedPiece].piece = NULL;
        field->selectedPiece = -1;
    } else {
        int curInd = possToIndex(&curPos);
        if (field->cells[curInd].piece == NULL) {
            return;
        }
        checker_f f = checkerAttack(selected->type);
        if (f(&selPos, &curPos, field, selected->team)) {
            attack(field, &selPos, &curPos);
            field->selectedPiece = -1;
        }

    }



}

void attack(struct Field *field, struct Pos *attack, struct Pos *defense) {
    int atckInd = possToIndex(attack);
    int defInd = possToIndex(defense);
    struct Figure *atckStr = field->cells[atckInd].piece;
    struct Figure *defStr = field->cells[defInd].piece;
    if (defStr == NULL) {
        logInfo("Defender is NULL");
        return;
    }
    if (atckStr == NULL) {
        logInfo("Attacker is NULL");
        return;
    }
    field->cells[defInd].piece = atckStr;
    field->cells[atckInd].piece = NULL;
    free(defStr);
}
