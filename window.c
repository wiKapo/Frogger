#include "window.h"

#define MIN_WIDTH 25
#define MIN_HEIGHT 25

screen_t Start() {
    FILE *config = fopen("config.txt", "r");

    //read config from file
    if (config == NULL) {
        perror("Error opening config file\n");
        exit(0);
    }

    int width = MIN_WIDTH, height = MIN_HEIGHT;
    char arg[100] = "ARG";

    int first, second;
    while (fscanf(config, "%s %d %d", arg, &first, &second) != EOF) {
        if (!strcmp(arg, "ARENA")) {
            height = first < MIN_HEIGHT ? first : MIN_HEIGHT;
            width = second < MIN_WIDTH ? second : MIN_WIDTH;
            break;
        }
    }
    fclose(config);

    //create a screen
    // WINDOW *win = newwin(3, 5, 3, 0);
    WINDOW *win = newwin(height, width, 1, 0);
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "ARENA Y:%d X:%d\n", height, width);
    wrefresh(win);

    screen_t scr = {win, height, width, 1};

    return scr;
}

void ShowMenu(screen_t *screen) {
    WINDOW *win = screen->win;
    box(win, 0, 0);
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
