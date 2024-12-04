#ifndef WINDOW_H
#define WINDOW_H
#include <ncurses.h>

WINDOW *create_window(int width, int height);
void destroy_window(WINDOW *window);

#endif //WINDOW_H
