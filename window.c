#include "window.h"

#define MIN_WIDTH 50
#define MIN_HEIGHT 30

#define COUNTDOWN_TIME  500

game_screen_t Start(const config_t *config) {
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

    //create main screen
    WINDOW *mainwin = newwin(height, width, 0, 0);
    int colwin = 1;
    wbkgd(mainwin, COLOR_PAIR(colwin));
    box(mainwin, 0, 0);
    mvwprintw(mainwin, 0, width / 2 - 5, GAME_TITLE);
    wrefresh(mainwin);

    //create ground screen
    WINDOW *groundwin = subwin(mainwin, height - 2, width - 2, 1, 1);

    //create game screen
    WINDOW *gamewin = subwin(mainwin, height - 2, width - 2, 1, 1);
    keypad(gamewin, TRUE);

    //create status screen
    WINDOW *status = newwin(3, width, height, 0);
    int colstatus = 2;
    wbkgd(status, COLOR_PAIR(colstatus));
    box(status, 0, 0);
    mvwprintw(status, 1, 1, "%s %s %s", (char *) config[1].data[0], (char *) config[1].data[1],
              (char *) config[1].data[2]);
    //mvwprintw(status, 1, 27, "ARENA Y:%d X:%d MH:%d", height, width, maxheight);
    wrefresh(status);

    return (game_screen_t){
        {mainwin, height, width, colwin},
        {groundwin, height - 2, width - 2, colwin},
        {gamewin, height - 2, width - 2, colwin},
        {status, 3, width, colstatus}
    };
}

void ClearScreen(const screen_t screen) {
    ClearScreenT(screen, "");
}

void ClearScreenT(const screen_t screen, const char *text) {
    WINDOW *win = screen.win;
    box(win, 0, 0);
    for (int i = 1; i < screen.height - 1; i++) {
        for (int j = 1; j < screen.width - 1; j++) {
            mvwprintw(win, i, j, " ");
        }
    }
    if (text != "") {
        mvwprintw(win, 0, screen.width / 2 - (strlen(text) / 2), text);
    }
    wrefresh(win);
}

int ShowMenu(const screen_t screen) {
    WINDOW *win = screen.win;
    mvwprintw(win, screen.height / 3, screen.width / 2 - 10, "[1] - Start tutorial");
    mvwprintw(win, screen.height / 3 + 1, screen.width / 2 - 10, "[2] - Start normal");
    mvwprintw(win, screen.height / 3 + 2, screen.width / 2 - 10, "[3] - Start hard");
    mvwprintw(win, screen.height / 3 + 3, screen.width / 2 - 10, "[s] - Open settings");
    mvwprintw(win, screen.height / 3 + 4, screen.width / 2 - 10, "[l] - Open leaderboard");
    mvwprintw(win, screen.height / 3 + 6, screen.width / 2 - 10, "[q] - Quit");
    wrefresh(win);
    while (1) {
        const char read = getch();
        switch (read) {
            case '1': return 1;
            case '2': return 2;
            case '3': return 3;
            case 's': return 99;
            case 'l': return 80;
            case 'q': return 0;

            default: break;
        }
    }
}

void ShowCountdown(const screen_t screen) {
    WINDOW *win = screen.win;
    WINDOW *countdown = subwin(win, 3, 5, screen.height / 2 - 1, screen.width / 2 - 3);
    // WINDOW *countdown = subwin(win, 3, 5, 17, 23);

    wbkgd(countdown, COLOR_PAIR(33));
    box(countdown, 0, 0);
    mvwaddstr(countdown, 1, 1, " 3 ");
    wrefresh(countdown);
    wtimeout(countdown, COUNTDOWN_TIME);
    wgetch(countdown);

    wbkgd(countdown, COLOR_PAIR(32));
    box(countdown, 0, 0);
    mvwaddch(countdown, 1, 2, '2');
    wrefresh(countdown);
    wtimeout(countdown, COUNTDOWN_TIME);
    wgetch(countdown);

    wbkgd(countdown, COLOR_PAIR(31));
    box(countdown, 0, 0);
    mvwaddch(countdown, 1, 2, '1');
    wrefresh(countdown);
    wtimeout(countdown, COUNTDOWN_TIME);
    wgetch(countdown);

    wbkgd(countdown, COLOR_PAIR(30));
    box(countdown, 0, 0);
    mvwaddstr(countdown, 1, 1, "GO!");
    wrefresh(countdown);
    wtimeout(countdown, COUNTDOWN_TIME);
    wgetch(countdown);
}

void ShowStatus(const screen_t screen) {
    WINDOW *win = newwin(screen.height, screen.width, screen.height + 1, 0);
    wrefresh(win);
}

void DrawGround(const screen_t screen, const ground_et *ground) {
    WINDOW *win = screen.win;
    const int width = screen.width, height = screen.height;

    for (int i = 0; i < height; i++) {
        wattron(win, COLOR_PAIR(ground[i] + 10));
        mvwhline(win, height - i - 1, 0, ' ', width);
        wattroff(win, COLOR_PAIR(ground[i] + 10));
    }
    //GROUND TYPE DEBUG
    // for (int i = 0; i < screen.height; i++) {
    //     if (i % 2 == 1)
    //         wattron(win, COLOR_PAIR(1));
    //     mvwprintw(win, screen.height - i - 1, 0, "%d", ground[i]);
    //     if (i % 2 == 1)
    //         wattroff(win, COLOR_PAIR(1));
    // }
    wrefresh(win);
}

void ShowFinish(const screen_t screen, const config_t *config, const long time) {
    WINDOW *win = screen.win;

    mvwprintw(win, screen.height / 3, screen.width / 2 - 6, "You win");
    mvwprintw(win, screen.height / 3 + 1, screen.width / 2 - 10, "Your score: %02ld:%02ld.%02ld",
              time / 1000 / 60, (time / 1000) % 60, time % 1000);
    mvwprintw(win, screen.height / 3 + 2, screen.width / 2 - 10, "Save to file? [y/n]");
    wrefresh(win);
    while (1) {
        char c = getch();
        if (c == 'y') {
            SaveScore(config, time);
            break;
        }
        if (c == 'n' || c == 'q') {
            break;
        }
    }
}
