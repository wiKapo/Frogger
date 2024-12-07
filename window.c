#include "window.h"

#define MIN_WIDTH 50
#define MIN_HEIGHT 20

game_t Start(const config_t *config) {
    WINDOW *initwin = initscr();
    StartColor();

    curs_set(0);
    noecho();
    refresh();

    int first = *(int *) config[0].data[0];
    int second = *(int *) config[0].data[1];
    int maxwidth = getmaxx(initwin), maxheight = getmaxy(initwin);

    int height = first * 2 > MIN_HEIGHT && first * 2 < maxheight ? first * 2 : MIN_HEIGHT;
    int width = second > MIN_WIDTH && second < maxwidth ? second : MIN_WIDTH;

    //create a screen
    WINDOW *win = newwin(height, width, 0, 0);
    int colwin = 2;
    wbkgd(win, COLOR_PAIR(colwin));
    box(win, 0, 0);
    mvwprintw(win, 0, width / 2 - 5, "[ FROGGER ]");
    wrefresh(win);

    WINDOW *status = newwin(3, width, height, 0);
    int colstatus = 1;
    wbkgd(status, COLOR_PAIR(colstatus));
    box(status, 0, 0);
    mvwprintw(status, 1, 1, "%s %s %s", (char *) config[1].data[0], (char *) config[1].data[1],
              (char *) config[1].data[2]);
    mvwprintw(status, 1, 27, "ARENA Y:%d X:%d MH:%d", height, width, maxheight);
    wrefresh(status);

    return (game_t){{win, height, width, colwin}, {status, 3, width, colstatus}};
}

void ClearScreen(const screen_t *screen) {
    ClearScreenT(screen, "");
}

void ClearScreenT(const screen_t *screen, const char *text) {
    WINDOW *win = screen->win;
    box(win, 0, 0);
    for (int i = 1; i < screen->height - 1; i++) {
        for (int j = 1; j < screen->width - 1; j++) {
            mvwprintw(win, i, j, " ");
        }
    }
    if (text != "") {
        mvwprintw(win, 0, screen->width / 2 - (strlen(text) / 2), text);
    }
    wrefresh(win);
}

int ShowMenu(const screen_t *screen) {
    WINDOW *win = screen->win;
    mvwprintw(win, screen->height / 3, screen->width / 2 - 10, "[1] - Start tutorial");
    mvwprintw(win, screen->height / 3 + 1, screen->width / 2 - 10, "[2] - Start normal");
    mvwprintw(win, screen->height / 3 + 2, screen->width / 2 - 10, "[3] - Start hard");
    mvwprintw(win, screen->height / 3 + 2, screen->width / 2 - 10, "[s] - Open settings");
    mvwprintw(win, screen->height / 3 + 4, screen->width / 2 - 10, "[q] - Quit");
    wrefresh(win);
    while (1) {
        char read = getch();
        switch (read) {
            case '1': return 1;
            case '2': return 2;
            case '3': return 3;
            case 's': return 99;
            case 'q': return 0;

            default: break;
        }
    }
}

void ShowStatus(const screen_t *screen) {
    WINDOW *win = newwin(screen->height, screen->width, screen->height + 1, 0);
    wrefresh(win);
}

void DrawGround(const screen_t screen, const ground_et *ground) {
    WINDOW *win = screen.win;
    int width = screen.width - 2, height = screen.height - 2;
    char line[width];
    for (int i = 0; i < width; i++) {
        line[i] = ' ';
    }
    line[width] = '\0';
    for (int i = 0; i < height; i++) {
        wattron(win, COLOR_PAIR(ground[i] + 10));
        mvwprintw(win, height - i, 1, "%s", line);
        wattroff(win, COLOR_PAIR(ground[i] + 10));
        wrefresh(win);
    }
}

void UpdatePosition(int height, int width, int* posy, int* posx, move_et movement);
void MoveFrog(const screen_t screen, object_t* frog) {
    WINDOW *win = screen.win;

    const int color = frog->colors, width = screen.width - 2, height = screen.height - 2;

    UpdatePosition(height, width, &frog->posy, &frog->posx, frog->movement);
    frog->movement = NONE;

    mvwprintw(win, 2, 2, "posy: %d/%d posx: %d/%d", frog->posy, screen.height, frog->posx, screen.width);

    const int posx = frog->posx, posy = frog->posy;
    const int fwidth = frog->width, fheight = frog->height;
    const char *text = frog->text;

    wattron(win, COLOR_PAIR(color));
    for (int i = 0; i < fwidth; i++) {
        for (int j = 0; j < fheight; j++)
            mvwaddch(win, posy + i + 1, posx + j, text[(i * fwidth) + j]);
    }
    wattroff(win, COLOR_PAIR(color));
}

void UpdatePosition(const int height, const int width, int* posy, int* posx, const move_et movement) {
    switch (movement) {
        case NONE: break;
        case UP:
            if (0 < *posy && *posy < height) *posy -= 2;
            break;
        case DOWN:
            if (0 < *posy && *posy < height-2) *posy += 2;
            break;
        case LEFT:
            if (1 < *posx && *posx < width) (*posx)--;
            break;
        case RIGHT:
            if (0 < *posx && *posx < width - 1) (*posx)++;
            break;
        default: break;
    }
}
