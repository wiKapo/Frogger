#include "time.h"
#include "window.h"

int main() {
    game_t game = Start();
    screen_t screen = game.mainwin;
    WINDOW* win = screen.win;

    int play = 1;

    while (play) {
        ClearScreenT(&screen, "[ FROGGER ]");
        int state = ShowMenu(&screen);
        ClearScreenT(&screen, "[ FROGGER ]");

        if (!state)
            play = 0;

        long starttime = GetTime() - 50000;

        while (state) {
            switch (state) {
                case 9: break;
                    //
                default: break;
            }
                //frog_move();
                //enemy_move();


            long gametime = GetTime() - starttime;

            mvwprintw(win, 0, screen.width - 12, "[%02ld:%02ld.%02ld]", gametime / 1000 / 60, (gametime/ 1000)%60, gametime % 1000);
            wrefresh(win);
            timeout(125);
            if (getch() == 'q')
                state = 0;
        }
    }

    endwin();
}