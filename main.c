#include "time.h"
#include "window.h"
#include "game.h"

int main() {
    //read config from file
    config_t *config = read_config_file("config.txt");

    game_t game = Start(config);
    screen_t screen = game.mainscr;
    WINDOW *win = screen.win;

    int play = 1;

    while (play) {
        ClearScreenT(&screen, "[ FROGGER ]");
        int state = ShowMenu(&screen);
        ClearScreenT(&screen, "[ FROGGER ]");

        if (!state)
            play = 0;

        long starttime = GetTime();

        while (state) {
            switch (state) {
                case 1: break;
                //
                default: break;
            }
            StartGame(config, game);
            //frog_move();
            //enemy_move();


            long gametime = GetTime() - starttime;

            mvwprintw(win, 0, screen.width - 12, "[%02ld:%02ld.%02ld]",
                      gametime / 1000 / 60,
                      (gametime / 1000) % 60,
                      gametime % 1000);
            wrefresh(win);
            timeout(1000/30);
            if (getch() == 'q')
                state = 0;
        }
    }

    endwin();
}
