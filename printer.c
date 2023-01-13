#include "printer.h"

#define HORZ "\u2550"
#define VERT "\u2551"
#define TOP_RIGHT "\u2557"
#define TOP_LEFT "\u2554"
#define BOTTOM_RIGHT "\u255D"
#define BOTTOM_LEFT "\u255A"

#define CURSOR "a"

static int FHS = 16; // field horizontal size
static int FVS = 8;  // field vertical size

static void castToBounds(int maxx, int maxy, int *left, int *top) { 
    *left = maxx / 2 - FHS / 2;
    *top = maxy / 2 - FVS / 2;
}

void printFieldBounds(int maxx, int maxy) {
    int leftbound = maxx / 2 - FHS / 2;
    int topbound = maxy / 2 - FVS / 2;
    mvaddstr(topbound, leftbound, TOP_LEFT);
    for (int i = 0; i < FHS; i++) {
        addstr(HORZ);
    }
    addstr(TOP_RIGHT);
    for (int i = 0; i < FVS; i++) {
        int topoffset = topbound + 1 + i;
        mvaddstr(topoffset, leftbound, VERT);
        mvaddstr(topoffset, leftbound + FHS + 1,VERT);
    }
    mvaddstr(topbound + FVS + 1, leftbound , BOTTOM_LEFT);
    for (int i = 0; i < FHS; i++) {
        addstr(HORZ);
    }
    addstr(BOTTOM_RIGHT);
}

static void printCell(Offsets *off, int index, struct Field *field) {
    struct Figure *piece = field->cells[index].piece;
    int top = off->top, left = off->left;
    int x, y;
    indexToPos(index, &x, &y);
    if (field->curx == x && field->cury == y) {
        attron(COLOR_PAIR(1));
    }
    if (piece != NULL) {
        char c = getCharByType(piece->type);
        if (piece->team == WHITE) {
            c += 'A' - 'a';
        }
        mvaddch(top + y + 1, left + (2 * x) + 1, c);
        addch(c);
    } else {
        mvaddstr(top + y + 1, left + (2 * x) + 1, "  ");
    }
    attroff(COLOR_PAIR(1));
}

void printField(int maxx, int maxy, struct Field *field) {
    printFieldBounds(maxx, maxy);
    int left, top;
    castToBounds(maxx, maxy, &left, &top);
    for (int index = 0; index < FIELD_SIZE; index++) {

        Offsets off = {top, left};
        printCell(&off, index, field);
    }
    /* attron(COLOR_PAIR(1)); */
    /* mvaddstr(field->cury + top + 1, (2 * field->curx) + left + 1, CURSOR); */
    /* addstr(CURSOR); */
    /* attroff(COLOR_PAIR(1)); */
}

