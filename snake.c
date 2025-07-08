#include <ncurses.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/*
 * TODO
 * - Create border in which snake confines
 * - Create object which randomly generates as points
 * - Create snake and its movements
 * - snake grows when capturing object
 * - if snake touches border, game over
 * - if snake touches itself, game over
*/

int generate_rand_y() {
    const int min_y = 1;
    const int max_y = 28;
    int random_y = (rand() % (max_y - min_y + 1)) + min_y;
    return random_y;
}

int generate_rand_x() {
    const int min_x = 1;
    const int max_x = 58;
    int random_x = (rand() % (max_x - min_x + 1)) + min_x;
    return random_x;
}

int main(void) {
    srand(time(NULL));
    initscr();
    const int height = 30;
    const int width = 60;
    const int start_y = (LINES - height) / 2;
    const int start_x = (COLS - width) / 2;
    WINDOW *win = newwin(height, width, start_y, start_x);
    box(win, ACS_VLINE, ACS_HLINE);
    //mvwaddch(win, 29, 59, 'O');
    int y = generate_rand_y();
    int x = generate_rand_x();
    printf("%d\n%d\n", y, x);
    mvwaddch(win, y, x, 'O');
    wrefresh(win);
    wgetch(win);
    delwin(win);
    endwin();
    return 0;
}
