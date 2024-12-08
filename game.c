#include "game.h"

int CheckSide(data_t test, int width, object_t *search);

void AddStaticObject(screen_t screen, const ground_et *ground, static_object_t *object);

void FrogUpdatePosition(screen_t screen, frog_t *frog);

void UpdatePosition(screen_t screen, data_t *data, int objheight, int objwidth, type_et type);

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
    const frog_t frog = (frog_t){
        {
            height - 1, (float) mainscr.width / 2,
            STILL, 1
        },
        2, 2, 20, "FROG", 0, FROG
    };
    // data_t empty = (data_t){0, 0, STILL, 0};
    object_t car = (object_t){malloc(sizeof(data_t)), 2, 4, 0, 0, 21, "_/T\\O--O", CAR};
    object_t log = (object_t){malloc(sizeof(data_t)), 2, 6, 0, 0, 22, "&~--~&&~--~&", LOG};
    AddObjects(mainscr, ground, &car);
    AddObjects(mainscr, ground, &log);

    static_object_t tree = (static_object_t){malloc(sizeof(data_t)), 0, 23, "####"};
    AddStaticObject(mainscr, ground, &tree);

    game_t *g = malloc(sizeof(game_t));
    g->frog = frog;
    g->car = car;
    g->log = log;
    g->stork = empty_object; //TODO stork
    g->obstacle = tree;
    g->ground = ground;

    return g;
}

void MoveFrog(const screen_t screen, frog_t *frog) {
    FrogUpdatePosition(screen, frog);

    //FROG POS DEBUG
    // WINDOW *win = screen.win;
    // mvwprintw(win, 1, 1, "MOVE %d", frog->data->movement);
    // mvwprintw(win, 2, 2, "posy: %d/%d posx: %d/%d", frog.data->posy, screen.height, frog.data->posx, screen.width);

    PrintObject(screen, (object_t){
                    &frog->data,
                    frog->width, frog->height,
                    1, 1, frog->colors, frog->text, frog->type
                });
}

void MoveCar(const screen_t screen, object_t *car) {
    const int amount = car->amount;
    for (int i = 0; i < amount; i++) {
        if (CheckSide(car->data[i], car->width, car))
            UpdatePosition(screen, &car->data[i], car->height, car->width, car->type);
        if ((car->data[i].movement == LEFT && (int) car->data[i].posx == 0 ||
             car->data[i].movement == RIGHT && (int) car->data[i].posx == car->width - 1)) {
            if (rand() % 25 == 0 && car->amount > 6) {
                car->amount--;
                car->data[i].posx = -10;
                car->data[i].movement = STILL;
            } else if (rand() % 5 == 0) {
                float val = (float) (rand() % 20) / 10;
                car->data[i].speed = val > 0.5 ? val : 1;
            }
        }
        PrintObject(screen, (object_t){
                        &car->data[i],
                        car->height, car->width,
                        amount, car->maxamount, car->colors, car->text, car->type
                    });

        //CAR POS DEBUG
        // mvwprintw(screen.win, i + 3, 3, "CARpos Y%d X%.1f", car->data[i].posy, car->data[i].posx);
    }
    for (int i = 1; i < amount; i++) {
        if (car->data[i - 1].movement == STILL) {
            car->data[i - 1] = car->data[i];
            car->data[i].movement = STILL;
        }
    }
}

//00:21:00 9.12.2024
int CheckObstacle(const data_t frog, const static_object_t tree) {
    for (int i = 0; i < tree.amount; i++) {
        if (frog.posx == tree.data[i].posx || frog.posx + 1 == tree.data[i].posx ||
            frog.posy == tree.data[i].posy || frog.posy + 1 == tree.data[i].posy) {
        }
    }
}

int CheckSide(const data_t test, int width, object_t *search) {
    const int movement = test.movement;
    const int posx = (int) test.posx, posy = test.posy;
    const int amount = search->amount;
    for (int i = 0; i < amount; i++) {
        if (posx == (int) search->data[i].posx || posy != search->data[i].posy)
            continue;
        if (movement == LEFT &&
            (int) posx == (int) search->data[i].posx + width)
            return 0;
        if (movement == RIGHT && posx + width == (int) search->data[i].posx)
            return 0;
    }
    return 1;
}

int CheckCollision(const frog_t frog, const object_t obj) {
    const int posy = frog.data.posy;
    const float posx = frog.data.posx;
    const int height = frog.height - 1;
    const float width = (float) frog.width - 1;

    for (int i = 0; i < obj.amount; i++) {
        int obj_posy = obj.data[i].posy;
        float obj_posx = obj.data[i].posx;
        int obj_height = obj.height - 1;
        float obj_width = (float) obj.width - 1;
        if (
            (posx >= obj_posx && posx <= obj_posx + obj_width && //TOP LEFT
             posy >= obj_posy && posy <= obj_posy + obj_height) ||
            (posx + width >= obj_posx && posx + width <= obj_posx + obj_width && //TOP RIGHT
             posy >= obj_posy && posy <= obj_posy + obj_height) ||
            (posx >= obj_posx && posx <= obj_posx + obj_width && //BOTTOM LEFT
             posy + height >= obj_posy && posy + height <= obj_posy + obj_height) ||
            (posx + width >= obj_posx && posx + width <= obj_posx + obj_width && //BOTTOM RIGHT
             posy + height >= obj_posy && posy + height <= obj_posy + obj_height)
        )
            return 1;
    }
    return 0;
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
        default: move = STILL;
    }
    return move;
}

void FrogUpdatePosition(const screen_t screen, frog_t *frog) {
    long *time = &frog->timeout;
    if (*time > GetTime() || frog->data.movement == STILL)
        return;
    UpdatePosition(screen, &frog->data, frog->width, frog->height, frog->type);
    *time = GetTime() + INPUT_DELAY;
}

void UpdatePosition(const screen_t screen, data_t *data, int objheight, int objwidth, type_et type) {
    const int height = screen.height, width = screen.width;
    int *posy = &data->posy;
    float *posx = &data->posx;
    const float speed = data->speed;
    const move_et movement = data->movement;

    switch (movement) {
        case STILL: break;
        case UP:
            if (0 < *posy && *posy < height - 1) (*posy)--;
            break;
        case DOWN:
            if (0 < *posy && *posy < height - objheight) (*posy)++;
            break;
        case LEFT:
            if (0 < *posx && (int) *posx < width) *posx -= 1 * speed;
            else if (type != FROG) *posx = (float) width - 1;
            break;
        case RIGHT:
            if (0 <= *posx && (int) *posx < width - objwidth) *posx += 1 * speed;
            else if (type != FROG) *posx = 0;
            break;
        default: break;
    }
}

void DrawObstacle(screen_t screen, static_object_t obj) {
    for (int i = 0; i < obj.amount; i++)
        PrintObject(screen, (object_t){&obj.data[i], 2, 2, 0, 0, obj.colors, obj.text, TREE});
}


void PrintObject(const screen_t screen, const object_t obj) {
    WINDOW *win = screen.win;
    const int color = obj.colors;
    const int posy = obj.data->posy;
    const int posx = (int) obj.data->posx;
    const int height = obj.height, width = obj.width;
    const char *text = obj.text;

    wattron(win, COLOR_PAIR(color));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            mvwaddch(win, posy + i, posx + j, text[(i * width) + j]);
    }
    wattroff(win, COLOR_PAIR(color));
}

void AddStaticObject(const screen_t screen, const ground_et *ground, static_object_t *object) {
    const int height = screen.height, width = screen.width;
    int lines[height], lineamount = 0;

    for (int i = 0; i < height / 2; i++) {
        if (ground[i * 2] == GRASS) {
            lines[lineamount++] = height - (i * 2);
        }
    }
    int objamount = 6 * (lineamount > 1 ? lineamount / 3 * 2 : 1);
    object->data = realloc(object->data, sizeof(data_t) * objamount);
    for (int i = 0; i < objamount; i++) {
        int line = rand() % lineamount;
        object->data[i] = (data_t){
            lines[line] - 4, (float) (rand() % (width - 6)), STILL, 0
        };
    }
    object->amount = objamount;
}

void AddObjects(const screen_t screen, const ground_et *ground, object_t *object) {
    const int height = screen.height, width = screen.width;
    int lines[height], lineamount = 0;
    const type_et type = object->type;
    int amount = object->amount;
    switch (type) {
        case CAR:
            for (int i = 0; i < (height - 1) / 2; i++) {
                if (ground[i * 2] == ROAD) {
                    lines[lineamount++] = (height - (i * 2));
                }
            }
            break;
        case LOG:
            for (int i = 0; i < height / 2; i++) {
                if (ground[i * 2] == WATER) {
                    lines[lineamount++] = (height - i - 1);
                }
            }
            break;
        default: break;
    }

    if (amount == 0) {
        float speed[lineamount];
        move_et direction[lineamount];
        for (int i = 0; i < lineamount; i++) {
            float val = (float) (rand() % 100) / 40;
            speed[i] = val > 0.5 ? val : 1;
            direction[i] = (rand() % 2) ? LEFT : RIGHT;
        }

        // randomizing the amount of objects when creating new
        int objamount = 6 * (lineamount > 1 ? lineamount / 3 * 2 : 1);
        object->data = realloc(object->data, sizeof(data_t) * objamount);
        for (int i = 0; i < objamount; i++) {
            int line = rand() % lineamount;
            object->data[i] = (data_t){
                lines[line] - 4, (float) (rand() % (width - 6)),
                direction[line], speed[line],
            };
        }
        object->amount = objamount;
        object->maxamount = objamount;
        return;
    }
    const float val = (float) (rand() % 20) / 10;
    int check = object->data[amount].movement == LEFT;
    object->data[amount] = (data_t){
        lines[rand() % lineamount] - 2, check ? (float) screen.width - 1 : 0,
        check ? LEFT : RIGHT, val > 0.5 ? val : 1
    };
    object->amount++;
}
