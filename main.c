#include "time.h"
#include "window.h"
#include "game.h"

#define CONFIG_FILENAME     "config.txt"
#define FPS                 30

int GameLoop(game_screen_t game_screen, game_t *game, const config_t *config);

int main() {
    //read config from file
    const config_t *config = ReadConfigFile(CONFIG_FILENAME);

    const game_screen_t game_screen = Start(config);
    const screen_t mainscr = game_screen.mainscr;
    const screen_t gamescr = game_screen.gamescr;
    const screen_t statscr = game_screen.statscr;
    game_state_et play = EXIT;
    int retry = 0;
    //MAIN LOOP
    while (1) {
        if (!retry) {
            ClearScreenT(mainscr, GAME_TITLE);
            play = ShowMenu(mainscr);
            ClearScreenT(mainscr, GAME_TITLE);

            if (play == EXIT) break;
            if (play == LEADERBOARD) {
                //ShowLeaderboard();
                continue;
            }
            if (play == SETTINGS) {
                //ShowSettings();
                config = ReadConfigFile(CONFIG_FILENAME);
                continue;
            }
        }
        game_t *game = StartGame(config, game_screen, play);

        ClearScreenT(mainscr, GAME_TITLE);

        DrawGround(gamescr, game->ground);
        wrefresh(gamescr.win);
        ShowCountdown(mainscr);

        //GAME LOOP
        retry = GameLoop(game_screen, game, config);
    }
    endwin();
    return 0;
}

int GameLoop(const game_screen_t game_screen, game_t *game, const config_t *config) {
    const screen_t mainscr = game_screen.mainscr;
    WINDOW *mainwin = mainscr.win;
    const screen_t gamescr = game_screen.gamescr;
    WINDOW *gamewin = gamescr.win;

    frog_t *frog = &game->frog;
    object_t cars = game->car;
    int input = 0;

    const long starttime = GetTime();
    while (1) {
        DrawGround(gamescr, game->ground);
        DrawObstacle(gamescr, game->obstacle);
        MoveFrog(gamescr, frog);
        MoveCar(gamescr, &cars);
        //CAR AMOUNT / MAXAMOUNT DEBUG
        //mvwprintw(gamescr.win, 0, 1, "%d %d", cars.amount, cars.maxamount);
        if (rand() % 50 == 0 && cars.amount < cars.maxamount) {
            AddObjects(gamescr, game->ground, &cars);
        }
        //MoveLog();
        //MoveStork();
        wrefresh(gamewin);

        if (CheckCollision(*frog, cars)) {
            ClearScreenT(mainscr, GAME_TITLE);
            if (ShowFail(gamescr, config))
                return 1;
            break;
        }

        long gametime = GetTime() - starttime;

        if (frog->data.posy == 0) {
            ClearScreenT(mainscr, GAME_TITLE);
            ShowFinish(gamescr, config, gametime);
            break;
        }

        mvwprintw(mainwin, 0, mainscr.width - 12, "[%02ld:%02ld.%02ld]",
                  gametime / 1000 / 60,
                  (gametime / 1000) % 60,
                  gametime % 1000);
        wrefresh(mainwin);

        timeout(1000 / FPS);
        input = getch();
        if (input == 'q') break;
        frog->data.movement = IntToMove(input);
    }
    return 0;
}
