#include <ncurses.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define WIN_HEIGHT 30
#define WIN_WIDTH 60
#define SNAKE_MAX_LENGTH 100
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

//window
WINDOW *win;

//snake
struct Pos head = {1, 30}; //starting position
struct Pos segments[SNAKE_MAX_LENGTH];
struct Pos dir = {-1, 0}; //starting direction (down)

//food
struct Pos food;

struct Pos generate_random_food_position() {
    struct Pos food_position;
    food_position.y_axis = (rand() % (WIN_HEIGHT - 2)) + 1;
    food_position.x_axis = (rand() % (WIN_WIDTH - 2)) + 1;
    return food_position;
}

void process_input() {
    int key = wgetch(win);
    
    switch (key) {
        case KEY_UP:
            dir.y_axis = -1;
            dir.x_axis = 0;
            break;

        case KEY_DOWN:
            dir.y_axis = 1;
            dir.x_axis = -0;
            break;


        case KEY_LEFT:
            dir.y_axis = 0;
            dir.x_axis - -1;
            break;

        case KEY_RIGHT:
            dir.y_axis = 0;
            dir.x_axis = 1;
            break;
    } 
}

void update_snake() {
    head.y_axis += dir.y_axis;
    head.x_axis += dir.x_axis;
}

int main(void) {
    srand(time(NULL));
    initscr();

    const int start_y = (LINES - WIN_HEIGHT) / 2;
    const int start_x = (COLS - WIN_WIDTH) / 2;
    win = newwin(WIN_HEIGHT, WIN_WIDTH, start_y, start_x);
    keypad(win, TRUE);
    box(win, ACS_VLINE, ACS_HLINE);
    
    process_input(win);
    update_snake();

    food = generate_random_food_position();
    mvwaddch(win, food.y_axis, food.x_axis, '@');

    mvwaddch(win, head.y_axis, head.x_axis, 'O');

    wrefresh(win);
    wgetch(win);
    delwin(win);
    endwin();
    return 0;
}
