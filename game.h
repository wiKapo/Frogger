#include "file.h"
#include "screen.h"
#include "window.h"
#include "gameobj.h"
#include <stdlib.h>

#ifndef GAME_H
#define GAME_H

typedef enum {
    PLAYER = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4,
    DOWNLEFT = 5,
    DOWNRIGHT = 6,
    UPLEFT = 7,
    UPRIGHT = 8,
} move_et;

typedef struct {
    int posy;
    int posx;
    int height;
    int width;
    int colors;
    move_et movement;
    type_et type;
} object_t;

object_t* StartGame(const config_t *config, const game_t game);

#endif //GAME_H
