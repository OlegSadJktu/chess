#include "printer.h"

#define HORZ "\u2550"
#define VERT "\u2551"
#define TOP_RIGHT "\u2557"
#define TOP_LEFT "\u2554"
#define BOTTOM_RIGHT "\u255D"
#define BOTTOM_LEFT "\u255A"



static int FHS = 16; // field horizontal size
static int FVS = 8;  // field vertical size

static int maxx, maxy;

void setMaxxy(int x, int y) {
    maxx = x;
    maxy = y;
}

static void getBounds(int *top, int *left) {
    *left = maxx / 2 - FHS / 2;
    *top = maxy / 2 - FVS / 2;
}


void printFieldBounds(int maxx, int maxy) {
    int leftbound, topbound;
    getBounds(&topbound, &leftbound);
    mvaddstr(topbound - 1, leftbound - 1, TOP_LEFT);
    for (int i = 0; i < FHS; i++) {
        addstr(HORZ);
    }
    addstr(TOP_RIGHT);
    for (int i = 0; i < FVS; i++) {
        int topoffset = topbound + i;
        mvaddstr(topoffset, leftbound -1, VERT);
        mvaddstr(topoffset, leftbound + FHS ,VERT);
    }
    mvaddstr(topbound + FVS , leftbound -1, BOTTOM_LEFT);
    for (int i = 0; i < FHS; i++) {
        addstr(HORZ);
    }
    addstr(BOTTOM_RIGHT);
}

static void printFigure(struct Figure *piece, struct Pos *pos) {
    int top, left;
    getBounds(&top, &left);
    char c = getCharByType(piece->type);
    if (piece->team == WHITE) {
        c += 'A' - 'a';
    }
    mvaddch(top + pos->y , left + (2 * pos->x) , c);
    addch(c);
}

static void printCell(Offsets *off, int index, struct Field *field) {
    struct Figure *pieceOnCell = field->cells[index].piece;
    int top = off->top, left = off->left;
    /* int x, y; */
    /* int pieceX = -1, pieceY = -1; */
    struct Pos indPos, selectedPiecePos = {-1,-1}, curPos;
    indexToPos(index, &indPos);
    curPos.x = field->curx; curPos.y = field->cury;
    struct Figure *piece = NULL;
    if (field->selectedPiece != -1) {
        indexToPos(field->selectedPiece, &selectedPiecePos);
        piece = field->cells[field->selectedPiece].piece;
    }
    int curOnCell = field->curx == indPos.x && field->cury == indPos.y;
    if (curOnCell) {
        attron(COLOR_PAIR(CURSOR_COLOR));
    }
    if (pieceOnCell != NULL) {
        printFigure(pieceOnCell, &indPos);
    } else {
        if (field->selectedPiece > -1) {
            /* attron(COLOR_PAIR(MOVE_COLOR)); */
            /* indexToPos(field->selectedPiece, &x, &y); */
            /* struct Pos pos = {x, y}, move = {pieceX, pieceY}; */
            checker_f f = checker(piece->type);
            if ( f(&selectedPiecePos, &indPos)) {
                if (samePos(&indPos, &curPos)) {
                    attron(COLOR_PAIR(CAN_MOVE));

                } else {
                    attron(COLOR_PAIR(MOVE_COLOR));
                }
            }
        }

        mvaddstr(top + indPos.y , left + (2 * indPos.x) , "  ");
    }
    attroff(COLOR_PAIR(CURSOR_COLOR));
    attroff(COLOR_PAIR(MOVE_COLOR));
    attroff(COLOR_PAIR(CAN_MOVE));
}

void printField(int maxx, int maxy, struct Field *field) {
    printFieldBounds(maxx, maxy);
    int left, top;
    getBounds(&top, &left);
    for (int index = 0; index < FIELD_SIZE; index++) {

        Offsets off = {top, left};
        printCell(&off, index, field);
    }
}

