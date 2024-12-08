#include "game.h"

object_t *GenerateObject(const config_t *config, screen_t screen, const ground_et *ground, const type_et type);

void UpdatePosition(screen_t screen, data_t *data, type_et type);

void PrintObject(screen_t screen, object_t obj);

game_t *StartGame(const config_t *config, const game_screen_t game_screen, int type) {
    const screen_t mainscr = game_screen.mainscr;
    // const screen_t status = game_screen.statscr;

    const long seed = *(long *) config[2].data[0] + type;
    srand(seed);

    const int height = mainscr.height - 1 - 2;
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

    object_t empty_object = {};
    data_t *frogdata = malloc(sizeof(data_t));
    frogdata[0] = (data_t){height - 1, mainscr.width / 2, 2, 2, NONE, 1};
    const object_t frog = {frogdata, 20, "IHHL", FROG};

    game_t *g = malloc(sizeof(game_t));
    g->frog = frog;
    g->cars = GenerateObject(config, mainscr, ground, CAR);
    g->log = &empty_object; //TODO log
    g->stork = empty_object; //TODO stork
    g->obstacle = &empty_object; //TODO obstacle
    g->ground = ground;

    return g;
}

void MoveFrog(const screen_t screen, const object_t *frog) {
    WINDOW *win = screen.win;
    // mvwprintw(win, 1, 1, "MOVE %d", frog->movement);
    UpdatePosition(screen, frog->data, FROG);

    //FROG POS DEBUG
    mvwprintw(win, 2, 2, "posy: %d/%d posx: %d/%d", frog->data->posy, screen.height, frog->data->posx, screen.width);

    PrintObject(screen, *frog);
}

void MoveCar(const screen_t screen, const object_t *car) {
    for (int i = 0; i < 4; i++) {
        UpdatePosition(screen, &car->data[i], CAR);
        data_t *data = malloc(sizeof(data_t));
        *data = car->data[i];
        PrintObject(screen, (object_t){data, car->colors, car->text, car->type});
        mvwprintw(screen.win, i + 3, 3, "CARpos Y%d X%d", data->posy, data->posy);
        free(data);
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

object_t *GenerateObject(const config_t *config, screen_t screen, const ground_et *ground, const type_et type) {
    object_t *object = malloc(sizeof(object_t));
    const int height = screen.height, width = screen.width;
    int lines[height], amount = 0;
    object->type = type;
    switch (type) {
        case CAR:
            for (int i = 0; i < height; i++) {
                if (ground[i] == ROAD)
                    lines[amount++] = i + 1;
            }
            object->text = "o/\\oo/\\o";
            object->colors = 21;
            break;
        case LOG:
            for (int i = 0; i < height; i++) {
                if (ground[i] == WATER)
                    lines[amount++] = i + 1;
            }
            object->text = "&~--~&&~--~&";
            object->colors = 22;
            break;
        default: return object;
    }
    int speeds[amount];
    for (int i = 0; i < amount; i++) {
        speeds[i] = (rand() % 100) / 40;
    }
    //TODO          V randomize the amount, but min 5
    const int objamount = 5;
    object->data = malloc(sizeof(data_t) * objamount);
    for (int i = 0; i < objamount; i++) {
        int line = rand() % amount;
        data_t data = {
            //TODO (posx) the cars can collide on spawn
            lines[line],
            rand() % (width - 1),
            2,
            (type == CAR) ? 4 : 6,
            (rand() % 2) ? LEFT : RIGHT,
            speeds[line],
        };
        object->data[i] = data;
    }
    return object;
}

void UpdatePosition(const screen_t screen, data_t *data, const type_et type) {
    const int height = screen.height, width = screen.width;
    // const size_t amount = sizeof(obj->data) / sizeof(data_t*);
    // for (int i = 0; i < amount; i++) {
    int *posy = &data->posy, *posx = &data->posx;
    const int objwidth = data->width, objheight = data->height;
    const float speed = data->speed;
    const move_et movement = data->movement;

    switch (movement) {
        case NONE: break;
        case UP:
            if (0 < *posy && *posy < height - objheight) (*posy)--;
            break;
        case DOWN:
            if (0 < *posy && *posy < height - objheight - 2) (*posy)++;
            break;
        case LEFT:
            if (1 < *posx && *posx < width) *posx -= (int) (1 * speed);
            else if (type != FROG) *posx = width - 1;
            break;
        case RIGHT:
            if (0 < *posx && *posx < width - objwidth - 1) *posx += (int) (1 * speed);
            else if (type != FROG) *posx = 1;
            break;
        default: break;
    }
    // }
}

void PrintObject(const screen_t screen, const object_t obj) {
    WINDOW *win = screen.win;
    // const size_t amount = sizeof(obj.data) / sizeof(data_t *);
    // for (int i = 0; i < amount; i++) {
    const int color = obj.colors;
    const int posy = obj.data->posy;
    const int posx = obj.data->posx;
    const int height = obj.data->height, width = obj.data->width;
    const char *text = obj.text;
    const type_et type = obj.type;

    wattron(win, COLOR_PAIR(color));
    if (type == FROG) {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++)
                mvwaddch(win, posy + i + 1, posx + j, text[(i * width) + j]);
        }
    } else {
        mvwaddstr(win, posy, posx, text);
    }
    wattroff(win, COLOR_PAIR(color));
    // }
}
