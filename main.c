#include "field.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <curses.h>
#include "printer.h"
#include "logger.h"



void eventHandler(struct Field *field, char ch) {
    switch (ch) {
        case ' ':
            selectF(field);
            return;
        case 'j':
            if (field->cury < 7)
                field->cury++;
            return;
        case 'k':
            if (field->cury > 0)
            field->cury--;
            return;
        case 'h':
            if (field->curx > 0)
            field->curx--;
            return;
        case 'l':
            if (field->curx < 7)
            field->curx++;
            return;
    }

}

int main() {
    int maxx, maxy;
    setlocale(LC_ALL, "");
    /* struct Field *field = malloc(sizeof(struct Field)); */
    /* printf("%p\n", field); */
    initscr();
    start_color();
    init_pair(CURSOR_COLOR, COLOR_YELLOW, COLOR_WHITE);
    init_pair(MOVE_COLOR, COLOR_RED, COLOR_GREEN);
    init_pair(CAN_MOVE, COLOR_BLACK, COLOR_YELLOW);
    getmaxyx(stdscr, maxy, maxx);
    setMaxxy(maxx, maxy);
    char ch = 0;

    struct Field *field = createDefaultField();

    curs_set(0);
    /* printField(maxx, maxy, field); */

    do {
        clear();
        eventHandler(field, ch);
        printField(maxx, maxy, field);
        refresh();

    } while ((ch = getch()) != 'q');
    
    endwin();

}
