#ifndef SCREEN_H
#define SCREEN_H
#include <ncurses.h>

typedef struct {
    WINDOW *win;
    int height;
    int width;
    int colors;
} screen_t;

typedef struct {
    screen_t mainscr;
    screen_t statscr;
} game_screen_t;

#endif //SCREEN_H
