#include "game.h"

object_t *StartGame(const config_t *config, const game_t game, int type) {
    screen_t main = game.mainscr;
    screen_t status = game.statscr;

    long seed = *(long *) config[2].data[0] + type;

    srand(seed);

    int height = main.height - 1 - 2;
    ground_et ground[height];

    //Decide what ground to draw
    for (int i = 4; i < height - 1; i += 2) {
        ground[i] = rand() % 3;
        ground[i + 1] = ground[i];
    }
    ground[0] = ground[1] = GRASS;
    if (type == 1) ground[2] = ground[3] = GRASS;
    ground[height - 3] = ground[height - 2] = GRASS;
    ground[height - 1] = ground[height] = FINISH;

    DrawGround(main, ground);

    object_t *objects = (object_t *) malloc(sizeof(object_t) * 2);
    object_t frog = {height - 1, main.width / 2, 2, 2, 20, "IHHL", NONE, PLAYER};
    objects[0] = frog;

    return objects;
}
