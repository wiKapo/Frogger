#include "game.h"

game_t *StartGame(const config_t *config, const game_screen_t game_screen, int type) {
    const screen_t main = game_screen.mainscr;
    // const screen_t status = game_screen.statscr;

    const long seed = *(long *) config[2].data[0] + type;
    srand(seed);

    const int height = main.height - 1 - 2;
    ground_et *ground = malloc(sizeof(ground_et) * height);

    //Decide what ground to draw
    for (int i = 4; i < height - 1; i += 2) {
        const int val = rand() % 100;
        if (val < 44)
            ground[i + 1] = ground[i] = GRASS;
        else if (val < 72)
            ground[i + 1] = ground[i] = ROAD;
        else if (val < 99)
            ground[i + 1] = ground[i] = WATER;
        else
            ground[i + 1] = ground[i] = GRASS;
    }
    ground[0] = ground[1] = GRASS;
    if (type == 1) ground[2] = ground[3] = GRASS;
    ground[height - 3] = ground[height - 2] = GRASS;
    ground[height - 1] = ground[height] = FINISH;

    object_t object = {};
    const object_t frog = {height - 1, main.width / 2, 2, 2, 20, "IHHL", NONE, 1, PLAYER};

    game_t *g = malloc(sizeof(game_t));
    g->frog = frog;
    g->car = object; //TODO car
    g->log = object; //TODO log
    g->stork = object; //TODO stork
    g->ground = ground;

    return g;
}

void UpdatePosition(screen_t screen, object_t *obj);

void PrintObject(screen_t screen, object_t obj);

void MoveFrog(const screen_t screen, object_t *frog) {
    // WINDOW *win = screen.win;
    // mvwprintw(win, 1, 1, "MOVE %d", frog->movement);
    UpdatePosition(screen, frog);

    //FROG POS DEBUG
    //mvwprintw(win, 2, 2, "posy: %d/%d posx: %d/%d", posy, screen.height, posx, screen.width);

    PrintObject(screen, *frog);
}

void MoveCar(const screen_t screen, object_t *car) {
    UpdatePosition(screen, car);
    PrintObject(screen, *car);
}

void PrintObject(const screen_t screen, const object_t obj) {
    WINDOW *win = screen.win;
    const int color = obj.colors;
    const int posy = obj.pos.posy;
    const int posx = obj.pos.posx;
    const int height = obj.pos.height, width = obj.pos.width;
    const char *text = obj.text;

    wattron(win, COLOR_PAIR(color));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++)
            mvwaddch(win, posy + i + 1, posx + j, text[(i * width) + j]);
    }
    wattroff(win, COLOR_PAIR(color));
}

void UpdatePosition(const screen_t screen, object_t *obj) {
    const int height = screen.height, width = screen.width;
    int *posy = &obj->pos.posy, *posx = &obj->pos.posx;
    int objwidth = obj->pos.width, objheight = obj->pos.height;
    const move_et movement = obj->movement;
    switch (movement) {
        case NONE: break;
        case UP:
            if (0 < *posy && *posy < height - objheight) (*posy)--;
            break;
        case DOWN:
            if (0 < *posy && *posy < height - objheight - 2) (*posy)++;
            break;
        case LEFT:
            if (1 < *posx && *posx < width) (*posx)--;
            break;
        case RIGHT:
            if (0 < *posx && *posx < width - objwidth - 1) (*posx)++;
            break;
        default: break;
    }
}

move_et IntToMove(int input) {
    move_et move;
    switch (input) {
        case KEY_UP:
        case 'w':
        case 'i':
            move = UP;
            break;
        case KEY_DOWN:
        case 's':
        case 'k':
            move = DOWN;
            break;
        case KEY_LEFT:
        case 'a':
        case 'j':
            move = LEFT;
            break;
        case KEY_RIGHT:
        case 'd':
        case 'l':
            move = RIGHT;
            break;
        default: move = NONE;
    }
    return move;
}
