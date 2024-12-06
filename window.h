#include "screen.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#ifndef WINDOW_H
#define WINDOW_H

game_t Start();
void ShowMenu(screen_t* screen);
void ClearScreen(screen_t* screen);

#endif //WINDOW_H
