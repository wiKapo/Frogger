#include "time.h"
#include "window.h"
#include "game.h"

#define CONFIG_FILENAME     "config.txt"
#define FPS                 30

int main() {
    //read config from file
    const config_t *config = read_config_file(CONFIG_FILENAME);

    const game_screen_t game_screen = Start(config);
    const screen_t mainscr = game_screen.mainscr;
    WINDOW *mainwin = mainscr.win;
    const screen_t statscr = game_screen.statscr;
    WINDOW *statwin = statscr.win;

    //MAIN LOOP
    while (1) {
        ClearScreenT(mainscr, GAME_TITLE);
        int play = ShowMenu(mainscr);
        ClearScreenT(mainscr, GAME_TITLE);

        if (!play) break;
        if (play == 99) {
            //ShowSettings()
            config = read_config_file(CONFIG_FILENAME);
            continue;
        }

        const long starttime = GetTime();
        const game_t *game = StartGame(config, game_screen, play);

        object_t frog = game->frog;

        ClearScreenT(mainscr, GAME_TITLE);
        ShowCountdown(mainscr);

        //GAME LOOP
        while (1) {
            // timeout(0);
            wtimeout(mainwin, 1000 / FPS);
            int input = wgetch(mainwin);
            if (input == 'q') break;

            DrawGround(mainscr, game->ground);

            frog.movement = IntToMove(input);
            MoveFrog(mainscr, &frog);
            //MoveCar();
            //MoveLog();
            //MoveStork();
            //CheckCollision();

            long gametime = GetTime() - starttime;

            mvwprintw(mainwin, 0, mainscr.width - 12, "[%02ld:%02ld.%02ld]",
                      gametime / 1000 / 60,
                      (gametime / 1000) % 60,
                      gametime % 1000);
        }
    }
    endwin();
    return 0;
}
