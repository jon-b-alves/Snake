#include <ncurses.h>
#include <stdio.h>
#include <stdbool.h>

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
    int height = 30;
    int width = 60;
    int start_y = (LINES - height) / 2;
    int start_x = (COLS - width) / 2;
    WINDOW *win = newwin(height, width, start_y, start_x);
    box(win, 0, 0);
    wrefresh(win);
    wgetch(win);
    delwin(win);
    endwin();
    return 0;
}
