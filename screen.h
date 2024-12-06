#ifndef SCREEN_H
#define SCREEN_H
#include <ncurses.h>

typedef struct {
    WINDOW *win;
    int width;
    int height;
    int temp_color;
} screen_t;

#endif //SCREEN_H
