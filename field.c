#include "field.h"

static struct Figure *createFigure(enum Team team, enum FigureType type) {
    struct Figure *figure = malloc(sizeof(struct Figure));
    figure->team = team;
    figure->type = type;
    return figure;
};

struct Field *createDefaultField() {
    struct Field *field = malloc(sizeof(struct Field));
    field->selectedPiece = -1;
    field->cury = 0;
    field->curx = 0;
    field->cells[charsToIndex("a1")].piece = createFigure(WHITE,KING);
    field->cells[charsToIndex("b1")].piece = createFigure(WHITE,QUEEN);
    field->cells[charsToIndex("c1")].piece = createFigure(WHITE,HORSE);
    field->cells[charsToIndex("d1")].piece = createFigure(WHITE,BISHOP);
    field->cells[charsToIndex("e1")].piece = createFigure(WHITE,ROOK);
    field->cells[charsToIndex("f1")].piece = createFigure(WHITE,PAWN);

    field->cells[charsToIndex("a8")].piece = createFigure(BLACK,KING);
    field->cells[charsToIndex("b8")].piece = createFigure(BLACK,QUEEN);
    field->cells[charsToIndex("c8")].piece = createFigure(BLACK,HORSE);
    field->cells[charsToIndex("d8")].piece = createFigure(BLACK,BISHOP);
    field->cells[charsToIndex("e8")].piece = createFigure(BLACK,ROOK);
    field->cells[charsToIndex("f8")].piece = createFigure(BLACK,PAWN);
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
    } else {
        if (field->selectedPiece == index) {
            field->selectedPiece = -1;
            return;
        }
        if (fig == NULL) {
            field->cells[curToIndex(field)].piece 
                = field->cells[field->selectedPiece].piece;
            field->cells[field->selectedPiece].piece = NULL;
            field->selectedPiece = -1;
        } 

    }

}
