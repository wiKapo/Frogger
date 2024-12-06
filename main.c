#include <sys/time.h>
#include "window.h"

int main() {
    initscr();
    printw("Hello World!");
    curs_set(0);
    refresh();
    noecho();
    getch();

    struct timeval gametime;
    gettimeofday(&gametime, NULL);

    int play = 1;
    screen_t screen = Start();
    WINDOW* win = screen.win;

    ShowMenu(&screen);

    while (play) {
        //frog_move();
        //enemy_move();

        mvwprintw(win, 2, 1, "TIME: %ld", gametime.tv_usec);
        wrefresh(win);
        timeout(1000);
        gettimeofday(&gametime, NULL);
        if (getch() == 'q')
            play = 0;
    }

    endwin();
}

//
// Created by wikapo on 12/3/24.
//