#include <ncurses.h>
#include <time.h>
#include "window.h"

int main() {
    initscr();
    printw("Hello World!");
    refresh();
    noecho();
    getch();

    time_t gametime;
    time(&gametime);

    int play = 1;
    while (play) {
        //frog_move();
        //enemy_move();
        printw("TIME: %ld", gametime);
        refresh();
        timeout(1000);
        if (getch() == 'q')
            play = 0;
    }

    endwin();
}

//
// Created by wikapo on 12/3/24.
//
