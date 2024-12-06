#include "screen.h"
#include "time.h"
#include "file.h"
#include "colors.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#ifndef WINDOW_H
#define WINDOW_H

game_t Start();
int ShowMenu(const screen_t* screen);
void ClearScreen(const screen_t* screen);
void ClearScreenT(const screen_t* screen, const char* text);

#endif //WINDOW_H
