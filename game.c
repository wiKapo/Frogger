#include "game.h"

game_t *StartGame(const config_t *config, const game_screen_t game_screen, int type) {
    const screen_t main = game_screen.mainscr;
    const screen_t status = game_screen.statscr;

    const long seed = *(long *) config[2].data[0] + type;
    srand(seed);

    const int height = main.height - 1 - 2;
    ground_et *ground = malloc(sizeof(ground_et) * height);

    //Decide what ground to draw
    for (int i = 4; i < height - 1; i += 2) {
        ground[i] = rand() % 3;
        ground[i + 1] = ground[i];
    }
    ground[0] = ground[1] = GRASS;
    if (type == 1) ground[2] = ground[3] = GRASS;
    ground[height - 3] = ground[height - 2] = GRASS;
    ground[height - 1] = ground[height] = FINISH;

    object_t object = {};
    const object_t frog = {height - 1, main.width / 2, 2, 2, 20, "IHHL", NONE, PLAYER};

    game_t *g = malloc(sizeof(game_t));
    g->frog  = frog;
    g->car = object; //TODO car
    g->log = object; //TODO log
    g->stork = object; //TODO stork
    g->ground = ground;

    return g;
}
