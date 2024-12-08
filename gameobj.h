#ifndef GAMEOBJ_H
#define GAMEOBJ_H

typedef enum {
    GRASS = 0,
    ROAD = 1,
    WATER = 2,
    FINISH = 9,
} ground_et;

typedef enum {
    FROG = 0,
    CAR = 1,
    FRIEND = 2,
    LOG = 3,
    STORK = 4,
    TREE = 5,
} type_et;

typedef enum {
    STILL = 0,
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
    float posx;
    move_et movement;
    float speed;
} data_t;

typedef struct {
    data_t *data;
    int height;
    int width;
    int amount;
    int maxamount;
    int colors;
    char *text;
    type_et type;
} object_t;

typedef struct {
    data_t data;
    int height;
    int width;
    int colors;
    char *text;
    long timeout;
    type_et type;
} frog_t;

typedef struct {
    data_t *data;
    int amount;
    int colors;
    char *text;
} static_object_t;

typedef struct {
    frog_t frog;
    object_t car;
    object_t log;
    object_t stork;
    static_object_t obstacle;
    ground_et *ground;
} game_t;

#endif //GAMEOBJ_H
