#include "file.h"
#include "screen.h"
#include "gameobj.h"
#include <stdlib.h>

#ifndef GAME_H
#define GAME_H

game_t *StartGame(const config_t *config, const game_screen_t game_screen, int type);

#endif //GAME_H
