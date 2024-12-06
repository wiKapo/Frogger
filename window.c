#include "window.h"
#include "file.h"

#define MIN_WIDTH 25
#define MIN_HEIGHT 25

game_t Start() {
    WINDOW *initwin = initscr();
    curs_set(0);
    noecho();
    refresh();

    //read config from file
    config_t *config = read_config_file("config.txt");

    int first = *(int *) config[0].data[0];
    int second = *(int *) config[0].data[1];
    int maxwidth = getmaxx(initwin), maxheight = getmaxy(initwin);

    int height = first > MIN_HEIGHT && first < maxheight ? first : MIN_HEIGHT;
    int width = second > MIN_WIDTH && second < maxwidth ? second : MIN_WIDTH;

    //create a screen
    WINDOW *win = newwin(height, width, 0, 0);
    box(win, 0, 0);
    mvwprintw(win, 0, width / 2 - 5, "[ FROGGER ]");
    wrefresh(win);

    WINDOW *status = newwin(3, width, height + 1, 0);
    box(status, 0, 0);
    mvwprintw(status, 1, 1, "%s %s %s", (char*)config[1].data[0], (char*)config[1].data[1], (char*)config[1].data[2]);
    mvwprintw(status, 1, 30, "ARENA Y:%d X:%d", height, width);
    wrefresh(status);

    game_t game = {{win, height, width, 1}, {status, 3, width, 1}};

    return game;
}

void ClearScreen(screen_t *screen) {
    ClearScreenT(screen, "");
}

void ClearScreenT(screen_t *screen, char *text) {
    WINDOW *win = screen->win;
    box(win, 0, 0);
    for(int i = 1; i < screen->height - 1; i++) {
        for(int j = 1; j < screen->width - 1; j++) {
            mvwprintw(win, i, j, " ");
        }
    }
    if (text != "") {
        mvwprintw(win, 0, screen->width / 2 - (strlen(text) / 2), text);
    }
    wrefresh(win);
}

void ShowMenu(screen_t *screen) {
    WINDOW *win = screen->win;
    mvwprintw(win, screen->height / 3, screen->width / 2 - 3, "FROGGER");
    mvwprintw(win, screen->height / 3 + 1, screen->width / 2 - 10, "[1] - Start tutorial");
    mvwprintw(win, screen->height / 3 + 2, screen->width / 2 - 10, "[2] - Start normal");
    mvwprintw(win, screen->height / 3 + 3, screen->width / 2 - 10, "[3] - Start infinite");
    wrefresh(win);
    char read;
    while (1) {
        read = getch();
        switch (read) {
            case '1': return;
            case '2': return;
            case '3': return;
            case 'q':
                box(win, 0, 0);
                mvwprintw(win, 3, 3, "SHUTTING DOWN");
                timeout(5000);
                endwin();
                exit(0);
            default: break;
        }
    }
}

void ShowStatus(screen_t *screen) {
    WINDOW *win = newwin(screen->height, screen->width, screen->height + 1, 0);
    wrefresh(win);
}
