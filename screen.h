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
    screen_t mainwin;
    screen_t statwin;
} game_t;

#endif //SCREEN_H
