#include <ncurses.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define WIN_HEIGHT 15
#define WIN_WIDTH 30
#define SNAKE_MAX_LENGTH 100
#define NO_KEY_PRESS -1
/*
 * TODO
 * - add snake collision with itself
 *   prevent opposite movements
 * - when food updates, cant update on the snake
*/
struct Pos {
    int y_axis;
    int x_axis;
};

//window
WINDOW *win;

//snake
struct Pos head = {1, 15}; //starting position
struct Pos prev_tail;
int snake_len = 1;
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
    // saving prev tail location to turn that character into a blank character
    prev_tail = segments[snake_len - 1];

    for (int i = snake_len - 1; i > 0; i--) {
        segments[i] = segments[i-1];
    }
    
    segments[0].y_axis += dir.y_axis;
    segments[0].x_axis += dir.x_axis;
    head = segments[0];

    mvwaddch(win, prev_tail.y_axis, prev_tail.x_axis, ' ');
    mvwaddch(win, head.y_axis, head.x_axis, 'O');
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

    segments[0] = head;
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
            if (dir.y_axis != 1) {
                dir.y_axis = -1;
                dir.x_axis = 0; 
            }
            break;

        case KEY_DOWN:
            if (dir.y_axis != -1) {
                dir.y_axis = 1;
                dir.x_axis = -0;
            }
            break;


        case KEY_LEFT:
            if (dir.x_axis != 1) {
                dir.y_axis = 0;
                dir.x_axis = -1;
            }
            break;

        case KEY_RIGHT:
            if (dir.x_axis != -1) {
                dir.y_axis = 0;
                dir.x_axis = 1;
            }
            break;

        case 'q':
            quit_game();
    } 
}

void check_collision() {
    // snake collision with food
    if (head.y_axis == food.y_axis && head.x_axis == food.x_axis) {
        update_food();
        snake_len += 1;
        segments[snake_len - 1] = prev_tail;
    }
    
    // snake collision with border
    if (head.y_axis >= WIN_HEIGHT - 1 || head.y_axis <= 0 || head.x_axis >= WIN_WIDTH - 1 || head.x_axis <= 0) {
        quit_game();
    }

    //snake collision with itself
    //we start at i = 1 becuase segments[0] is the head
    for (int i = 1; i <= snake_len - 1; i++) {
        if (head.y_axis == segments[i].y_axis && head.x_axis == segments[i].x_axis) {
            quit_game();
        }
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
