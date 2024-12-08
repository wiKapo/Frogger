#include "file.h"
#include "screen.h"
#include "gameobj.h"
#include <stdlib.h>

#ifndef GAME_H
#define GAME_H

typedef enum {
    EXIT = 0,
    TUTORIAL = 1,
    NORMAL = 2,
    SETTINGS = 90,
    LEADERBOARD = 91,
} game_state_et;

game_t *StartGame(const config_t *config, game_screen_t game_screen, int type);

void MoveFrog(screen_t screen, object_t frog);

void MoveCar(screen_t screen, object_t car);

int CheckCollision(object_t frog, object_t obj);

move_et IntToMove(int input);

#endif //GAME_H
