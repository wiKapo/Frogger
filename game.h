#include "file.h"
#include "screen.h"
#include "gameobj.h"
#include <stdlib.h>

#ifndef GAME_H
#define GAME_H

game_t *StartGame(const config_t *config, game_screen_t game_screen, int type);

void MoveFrog(screen_t screen, const object_t *frog);

void MoveCar(screen_t screen, const object_t *car);

move_et IntToMove(int input);

#endif //GAME_H
