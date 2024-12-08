#include "time.h"
#include "window.h"
#include "game.h"

#define CONFIG_FILENAME     "config.txt"
#define FPS                 30

void GameLoop(game_screen_t game_screen, const game_t *game, const config_t *config);

int main() {
    //read config from file
    const config_t *config = ReadConfigFile(CONFIG_FILENAME);

    const game_screen_t game_screen = Start(config);
    const screen_t mainscr = game_screen.mainscr;
    const screen_t groundscr = game_screen.groundscr;

    //MAIN LOOP
    while (1) {
        ClearScreenT(mainscr, GAME_TITLE);
        const game_state_et play = ShowMenu(mainscr);
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
        const game_t *game = StartGame(config, game_screen, play);

        ClearScreenT(mainscr, GAME_TITLE);

        DrawGround(groundscr, game->ground);
        ShowCountdown(mainscr);

        //GAME LOOP
        GameLoop(game_screen, game, config);
    }
    endwin();
    return 0;
}

void GameLoop(const game_screen_t game_screen, const game_t *game, const config_t *config) {
    const screen_t mainscr = game_screen.mainscr;
    WINDOW *mainwin = mainscr.win;
    const screen_t gamescr = game_screen.gamescr;
    WINDOW *gamewin = gamescr.win;
    const screen_t groundscr = game_screen.groundscr;

    const object_t frog = game->frog;
    const object_t cars = game->car;

    const long starttime = GetTime();
    while (1) {
        wtimeout(gamewin, 1000 / FPS);
        int input = wgetch(gamewin);
        if (input == 'q') break;

        DrawGround(groundscr, game->ground);
        frog.data->movement = IntToMove(input);
        MoveFrog(gamescr, frog);
        MoveCar(gamescr, cars);
        //MoveLog();
        //MoveStork();
        //CheckCollision();

        long gametime = GetTime() - starttime;

        if (frog.data->posy == 0) {
            ClearScreenT(mainscr, GAME_TITLE);
            ShowFinish(gamescr, config, gametime);
            break;
        }

        mvwprintw(mainwin, 0, mainscr.width - 12, "[%02ld:%02ld.%02ld]",
                  gametime / 1000 / 60,
                  (gametime / 1000) % 60,
                  gametime % 1000);
        wrefresh(mainwin);
    }
}
