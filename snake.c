#include <ncurses.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define WIN_HEIGHT 30
#define WIN_WIDTH 60
#define SNAKE_MAX_LENGTH 100
#define NO_KEY_PRESS -1
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
struct Pos old_head = {1, 30};
struct Pos segments[SNAKE_MAX_LENGTH];
struct Pos dir = {1, 0}; //starting direction (down)

//food
struct Pos food;

void update_food() {
    food.y_axis = (rand() % (WIN_HEIGHT - 2)) + 1;
    food.x_axis = (rand() % (WIN_WIDTH - 2)) + 1;
    mvwaddch(win, food.y_axis, food.x_axis, '@');
}

void update_snake() {
    //deletes the old position of the head in the next frame by replacing it with a blank character
    mvwaddch(win,old_head.y_axis, old_head.x_axis, ' ');

    head.y_axis += dir.y_axis;
    head.x_axis += dir.x_axis;
    mvwaddch(win, head.y_axis, head.x_axis, 'O');

    old_head = head;
}

void init() {
    srand(time(NULL));
    initscr();

    const int start_y = (LINES - WIN_HEIGHT) / 2;
    const int start_x = (COLS - WIN_WIDTH) / 2;
    win = newwin(WIN_HEIGHT, WIN_WIDTH, start_y, start_x);

    box(win, ACS_VLINE, ACS_HLINE);
    
    keypad(win, TRUE);
    nodelay(win, TRUE);
    curs_set(0);
    noecho();

    update_food();

}

int quit_game() {
    delwin(win);
    endwin();
    exit(0);
}

void process_input() {
    int input;
    int key = NO_KEY_PRESS;

    // if no key is pressed, wgetch returns ERR 
    while ((input = wgetch(win)) != ERR) {
        key = input;
    }
    
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
            dir.x_axis = -1;
            break;

        case KEY_RIGHT:
            dir.y_axis = 0;
            dir.x_axis = 1;
            break;

        case 'q':
            quit_game();
    } 
}

void check_collision() {
    if (head.y_axis == food.y_axis && head.x_axis == food.x_axis) {
        update_food();
    }
    
    if (head.y_axis >= WIN_HEIGHT - 1 || head.y_axis <= 0 || head.x_axis >= WIN_WIDTH - 1 || head.x_axis <= 0) {
        quit_game();
    }
}

int main(void) {
    init();

    while (true) {
        process_input();
        update_snake();
        check_collision();

        wrefresh(win);
        napms(100);
    }

    quit_game();
    return 0;
}
