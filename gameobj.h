#ifndef GAMEOBJ_H
#define GAMEOBJ_H

typedef enum {
    GRASS = 0,
    ROAD = 1,
    WATER = 2,
    FINISH = 9,
} ground_et;

typedef enum {
    PLAYER = 0,
    CAR = 1,
    LOG = 2,
    STORK = 3,
} type_et;

typedef enum {
    NONE = 0,
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
} pos_t;

typedef struct {
    pos_t pos;
    int colors;
    char *text;
    move_et movement;
    type_et type;
} object_t;

typedef struct {
    object_t frog;
    object_t car;
    object_t log;
    object_t stork;
    ground_et* ground;
} game_t;

#endif //GAMEOBJ_H
