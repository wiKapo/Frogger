#include "time.h"
#include "window.h"
#include "game.h"

#define CONFIG_FILENAME     "config.txt"

int main() {
    //read config from file
    config_t *config = read_config_file(CONFIG_FILENAME);

    const game_screen_t game_screen = Start(config);
    screen_t mainscr = game_screen.mainscr;
    WINDOW *win = mainscr.win;

    int play = 1;

    while (play) {
        ClearScreenT(&mainscr, "[ FROGGER ]");
        int state = ShowMenu(&mainscr);
        ClearScreenT(&mainscr, "[ FROGGER ]");

        if (!state)
            play = 0;

        if (state == 99) {
            //ShowSettings()
            config = read_config_file(CONFIG_FILENAME);
            continue;
        }

        long starttime = GetTime();
        const game_t *game = StartGame(config, game_screen, state);

        DrawGround(mainscr, game->ground);

        object_t frog = game->frog;

        while (state) {
            //frog_move();
            MoveFrog(mainscr, &frog);
            //enemy_move();


            long gametime = GetTime() - starttime;

            mvwprintw(win, 0, mainscr.width - 12, "[%02ld:%02ld.%02ld]",
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
