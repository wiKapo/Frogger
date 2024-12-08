#include "screen.h"
#include "time.h"
#include "file.h"
#include "colors.h"
#include "gameobj.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define GAME_TITLE          "[ FROGGER ]"

#ifndef WINDOW_H
#define WINDOW_H

game_screen_t Start(const config_t* config);
int ShowMenu(screen_t screen);
void ShowCountdown(screen_t screen);
void ShowFinish(screen_t screen, const config_t *config, long time);
int ShowFail(screen_t screen, const config_t *config);
void ClearScreen(screen_t screen);
void ClearScreenT(screen_t screen, const char* text);
void DrawGround(screen_t screen, const ground_et* ground);

#endif //WINDOW_H
