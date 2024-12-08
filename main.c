#include "time.h"
#include "window.h"
#include "game.h"

#define CONFIG_FILENAME     "config.txt"
#define FPS                 30

void GameLoop(screen_t mainscr, const game_t *game, const config_t *config);

int main() {
    //read config from file
    const config_t *config = ReadConfigFile(CONFIG_FILENAME);

    const game_screen_t game_screen = Start(config);
    const screen_t mainscr = game_screen.mainscr;

    //MAIN LOOP
    while (1) {
        ClearScreenT(mainscr, GAME_TITLE);
        int play = ShowMenu(mainscr);
        ClearScreenT(mainscr, GAME_TITLE);

        if (!play) break;
        if (play == 80) {
            //ShowLeaderboard();
            continue;
        }
        if (play == 99) {
            //ShowSettings();
            config = ReadConfigFile(CONFIG_FILENAME);
            continue;
        }
        const game_t *game = StartGame(config, game_screen, play);

        ClearScreenT(mainscr, GAME_TITLE);

        DrawGround(mainscr, game->ground);
        ShowCountdown(mainscr);

        //GAME LOOP
        GameLoop(mainscr, game, config);
    }
    endwin();
    return 0;
}

void GameLoop(const screen_t mainscr, const game_t *game, const config_t *config) {
    WINDOW *mainwin = mainscr.win;
    object_t frog = game->frog;
    object_t *cars = game->cars;

    const long starttime = GetTime();
    while (1) {
        wtimeout(mainwin, 1000 / FPS);
        int input = wgetch(mainwin);
        if (input == 'q') break;

        DrawGround(mainscr, game->ground);

        frog.data->movement = IntToMove(input);
        MoveFrog(mainscr, &frog);
        MoveCar(mainscr, cars);
        //MoveLog();
        //MoveStork();
        //CheckCollision();

        long gametime = GetTime() - starttime;

        if (frog.data->posy == 0) {
            ShowFinish(mainscr, config, gametime);
            break;
        }

        mvwprintw(mainwin, 0, mainscr.width - 12, "[%02ld:%02ld.%02ld]",
                  gametime / 1000 / 60,
                  (gametime / 1000) % 60,
                  gametime % 1000);
    }
}
