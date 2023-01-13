#include "field.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <curses.h>
#include "printer.h"



void moveCursor(struct Field *field, char ch) {
    switch (ch) {
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
    init_pair(1, COLOR_YELLOW, COLOR_WHITE);
    getmaxyx(stdscr, maxy, maxx);
    char ch;

    struct Field *field = createDefaultField();

    curs_set(0);
    printField(maxx, maxy, field);
    while ((ch = getch()) != 'q') {
        clear();
        moveCursor(field, ch);
        printField(maxx, maxy, field);

        refresh();
    }
    endwin();

}
