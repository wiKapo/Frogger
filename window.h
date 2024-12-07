#include "screen.h"
#include "time.h"
#include "file.h"
#include "colors.h"
#include "gameobj.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#ifndef WINDOW_H
#define WINDOW_H

game_screen_t Start(const config_t* config);
int ShowMenu(const screen_t* screen);
void ClearScreen(const screen_t* screen);
void ClearScreenT(const screen_t* screen, const char* text);
void DrawGround(const screen_t screen, const ground_et* ground);
void MoveFrog(const screen_t screen, object_t* frog);

#endif //WINDOW_H
