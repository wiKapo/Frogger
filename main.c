#include <sys/time.h>
#include "window.h"

int main() {
    struct timeval gametime;
    gettimeofday(&gametime, NULL);

    int play = 1;
    game_t game = Start();
    screen_t screen = game.mainwin;
    WINDOW* win = screen.win;

    ShowMenu(&screen);
    ClearScreen(&screen);

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