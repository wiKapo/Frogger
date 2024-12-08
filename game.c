#include "game.h"

object_t GenerateObject(screen_t screen, const ground_et *ground, type_et type);

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
    const frog_t frog = (frog_t){
        {
            height - 1, (float) mainscr.width / 2,
            2, 2,
            STILL, 1
        },
        20, "IHHL", 0, FROG
    };

    game_t *g = malloc(sizeof(game_t));
    g->frog = frog;
    g->car = GenerateObject(mainscr, ground, CAR);
    g->log = empty_object; //TODO log
    g->stork = empty_object; //TODO stork
    g->obstacle = (static_obj_t){}; //TODO obstacle
    g->ground = ground;

    return g;
}

void MoveFrog(const screen_t screen, frog_t *frog) {
    UpdatePosition(screen, &frog->data, FROG);

    //FROG POS DEBUG
    // WINDOW *win = screen.win;
    // mvwprintw(win, 1, 1, "MOVE %d", frog->data->movement);
    // mvwprintw(win, 2, 2, "posy: %d/%d posx: %d/%d", frog.data->posy, screen.height, frog.data->posx, screen.width);

    PrintObject(screen, (object_t){&frog->data, 1, frog->colors, frog->text, frog->type});
}

void MoveCar(const screen_t screen, const object_t car) {
    const int amount = car.amount;
    for (int i = 0; i < amount; i++) {
        UpdatePosition(screen, &car.data[i], CAR);
        // data_t *data = malloc(sizeof(data_t));
        // *data = car->data[i];
        PrintObject(screen, (object_t){&car.data[i], amount, car.colors, car.text, car.type});

        //CAR POS DEBUG
        // mvwprintw(screen.win, i + 3, 3, "CARpos Y%d X%.1f", car.data[i].posy, car.data[i].posx);
        // free(data);
    }
}

int CheckCollision(frog_t frog, object_t obj) {
    const int posy = frog.data.posy;
    const float posx = frog.data.posx;
    const int height = frog.data.height - 1;
    const float width = (float) frog.data.width;

    for (int i = 0; i < obj.amount; i++) {
        int obj_posy = obj.data[i].posy;
        float obj_posx = obj.data[i].posx;
        int obj_height = obj.data[i].height - 1;
        float obj_width = (float) obj.data[i].width - 1;
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

object_t GenerateObject(const screen_t screen, const ground_et *ground, const type_et type) {
    // object_t *object = malloc(sizeof(object_t));
    const int height = screen.height, width = screen.width;
    int lines[height], amount = 0;
    char *text;
    int colors;
    switch (type) {
        case CAR:
            for (int i = 0; i < (height - 1) / 2; i++) {
                if (ground[i * 2] == ROAD) {
                    lines[amount++] = (height - (i * 2));
                }
            }
            text = "_/T\\O--O";
            colors = 21;
            break;
        case LOG:
            for (int i = 0; i < height / 2; i++) {
                if (ground[i * 2] == WATER) {
                    lines[amount++] = (height - i - 1);
                }
            }
            text = "&~--~&&~--~&";
            colors = 22;
            break;
        default: return (object_t){};
    }
    float speed[amount];
    move_et direction[amount];
    for (int i = 0; i < amount; i++) {
        speed[i] = (float) (rand() % 100) / 40;
        direction[i] = (rand() % 2) ? LEFT : RIGHT;
    }
    // randomizing the amount of objects
    const int objamount = 5 * (amount > 1 ? amount / 2 : 1);

    data_t *data = malloc(sizeof(data_t) * objamount);
    for (int i = 0; i < objamount; i++) {
        int line = rand() % amount;
        data[i] = (data_t){
            //TODO (posx) the cars can collide on spawn
            lines[line] - 4, (float) (rand() % (width - 6)),
            2, (type == CAR) ? 4 : 6,
            direction[line], speed[line],
        };
    }
    return (object_t){data, objamount, colors, text, type};
}

void UpdatePosition(const screen_t screen, data_t *data, const type_et type) {
    const int height = screen.height, width = screen.width;
    // const size_t amount = sizeof(obj->data) / sizeof(data_t*);
    // for (int i = 0; i < amount; i++) {
    int *posy = &data->posy;
    float *posx = &data->posx;
    const int objwidth = data->width, objheight = data->height;
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
            else if (type != FROG) *posx = width - 1;
            break;
        case RIGHT:
            if (0 <= *posx && (int) *posx < width - objwidth) *posx += 1 * speed;
            else if (type != FROG) *posx = 0;
            break;
        default: break;
    }
    // }
}

void PrintObject(const screen_t screen, const object_t obj) {
    WINDOW *win = screen.win;
    const int color = obj.colors;
    const int posy = obj.data->posy;
    const int posx = (int) obj.data->posx;
    const int height = obj.data->height, width = obj.data->width;
    const char *text = obj.text;

    wattron(win, COLOR_PAIR(color));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            mvwaddch(win, posy + i, posx + j, text[(i * width) + j]);
    }
    wattroff(win, COLOR_PAIR(color));
}
