#include <ncurses.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define WIN_HEIGHT 30
#define WIN_WIDTH 60
/*
 * TODO
 * - Create snake and its movements
 * - snake grows when capturing object
 * - if snake touches border, game over
 * - if snake touches itself, game over
*/
struct Pos {
    int y_axis;
    int x_axis;
};

struct Pos generate_random_food_position() {
    struct Pos food_position;
    food_position.y_axis = (rand() % (WIN_HEIGHT - 2)) + 1;
    food_position.x_axis = (rand() % (WIN_WIDTH - 2)) + 1;
    return food_position;
}

//snake
struct Pos head = {1, 30};
struct Pos segments[100];
struct Pos dir = {-1, 0};

//food
struct Pos food;

int main(void) {
    srand(time(NULL));
    initscr();

    const int start_y = (LINES - WIN_HEIGHT) / 2;
    const int start_x = (COLS - WIN_WIDTH) / 2;
    WINDOW *win = newwin(WIN_HEIGHT, WIN_WIDTH, start_y, start_x);
    box(win, ACS_VLINE, ACS_HLINE);

    food = generate_random_food_position();
    mvwaddch(win, food.y_axis, food.x_axis, '@');

    mvwaddch(win, head.y_axis, head.x_axis, 'O');

    wrefresh(win);
    wgetch(win);
    delwin(win);
    endwin();
    return 0;
}
