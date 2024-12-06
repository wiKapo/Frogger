#include "window.h"
#include "file.h"

#define MIN_WIDTH 25
#define MIN_HEIGHT 25

game_t Start() {
    WINDOW *initwin = initscr();
    curs_set(0);
    noecho();
    printw("GAME LOADING...");
    refresh();
    getch();
    //read config from file

    config_t *config = read_config_file("config.txt");
    // FILE *config = fopen("config.txt", "r");
    //
    // if (config == NULL) {
    //     perror("Error opening config file\n");
    //     exit(0);
    // }
    //
    // int width = MIN_WIDTH, height = MIN_HEIGHT;
    // int maxwidth = getmaxx(initwin), maxheight = getmaxy(initwin);
    // char arg[100] = "ARG";
    //
    // int first, second;
    // while (fscanf(config, "%s %d %d", arg, &first, &second) != EOF) {
    //     if (!strcmp(arg, "ARENA")) {
    //         height = first > MIN_HEIGHT && first < maxheight ? first : MIN_HEIGHT;
    //         width = second > MIN_WIDTH && second < maxwidth? second : MIN_WIDTH;
    //         break;
    //     }
    // }
    // fclose(config);

    int first = *(int*)config[0].data[0];
    int second = *(int*)config[0].data[1];
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
    mvwprintw(status, 1, 1, "ARENA Y:%d X:%d\n", height, width);
    wrefresh(status);

    game_t game = {{win, height, width, 1}, {status, 3, width, 1}};

    return game;
}

void ClearScreen(screen_t *screen) {
    WINDOW *win = screen->win;
    box(win, 0, 0);
    wrefresh(win);
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

void ShowStatus(screen_t *screen) {
    WINDOW *win = newwin(screen->height, screen->width, screen->height + 1, 0);
    wrefresh(win);
}
