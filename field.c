#include "field.h"

static struct Figure *createFigure(enum Team team, enum FigureType type) {
    struct Figure *figure = malloc(sizeof(struct Figure));
    figure->team = team;
    figure->type = type;
    return figure;
};

struct Field *createDefaultField() {
    struct Field *field = malloc(sizeof(struct Field));
    field->cury = 0;
    field->curx = 0;
    field->cells[charsToIndex("a1")].piece = createFigure(WHITE,HORSE);
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

int indexToPos(int index, int *x, int *y) {
    if (index > FIELD_SIZE - 1 || index < 0) {
        return -1;
    }
    *x = index % 8;
    *y = index / 8;
    return index;
}
