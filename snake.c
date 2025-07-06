#include <ncurses.h>
#include <stdio.h>

/*
 * TODO
 * - Create border in which snake confines
 * - Create object which randomly generates as points
 * - Create snake and its movements
 * - snake grows when capturing object
 * - if snake touches border, game over
 * - if snake touches itself, game over
*/

int main(void) {
    initscr();
    int i = 0;

    while (1) {
        clear();
        mvaddstr(i, 0, "rain");
        refresh();
        int ch = getch();
        if (ch == 'q') break;
        else i++;
    }

    endwin();
    return 0;
}
