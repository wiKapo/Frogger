#include "file.h"
#include "screen.h"
#include "window.h"
#include "gameobj.h"
#include <stdlib.h>

#ifndef GAME_H
#define GAME_H

object_t* StartGame(const config_t *config, const game_t game, int type);

#endif //GAME_H
