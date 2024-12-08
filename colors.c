#include "colors.h"
#include <ncurses.h>
#include <stdlib.h>

void StartColor() {
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_YELLOW, 750, 750, 0);
    init_color(COLOR_RED, 750, 0, 0);
    init_color(COLOR_GREEN, 0, 750, 0);
    init_color(COLOR_WHITE, 900, 900, 900);

    init_color(COLOR_LIGHT_GRAY, 609, 609, 609);
    init_color(COLOR_GRAY, 330, 330, 330);
    init_color(COLOR_DARK_GRAY, 100, 100, 100);
    init_color(COLOR_DARKER_GRAY, 50, 50, 50);
    init_color(COLOR_DARK_GREEN, 0, 500, 0);
    init_color(COLOR_DARKER_GREEN, 105, 211, 78);
    init_color(COLOR_BROWN, 457, 199, 78);
    init_color(COLOR_DARK_BROWN, 238, 117, 54);

    //SCREEN DEFAULT COLORS
    init_pair(1, COLOR_WHITE, COLOR_DARK_GRAY); //MAIN SCREEN
    init_pair(2, COLOR_GREEN, COLOR_DARK_GRAY); //STATUS SCREEN

    //COLORS FOR GROUND
    init_pair(10, COLOR_WHITE, COLOR_DARK_GREEN); //GRASS
    init_pair(11, COLOR_WHITE, COLOR_DARKER_GRAY); //ROAD
    init_pair(12, COLOR_WHITE, COLOR_CYAN); //WATER
    init_pair(19, COLOR_WHITE, COLOR_RED); //FINISH

    //COLORS FOR OBJECTS
    init_pair(20, COLOR_GREEN, COLOR_DARKER_GREEN); //FROG
    init_pair(21, COLOR_BLACK, COLOR_RED); //CAR
    init_pair(22, COLOR_BROWN, COLOR_DARK_BROWN); //LOG

    //COLORS FOR COUNTDOWN
    init_pair(30, COLOR_WHITE, COLOR_DARK_GRAY); //GO!
    init_pair(31, COLOR_GREEN, COLOR_DARK_GRAY); //1
    init_pair(32, COLOR_YELLOW, COLOR_DARK_GRAY); //2
    init_pair(33, COLOR_RED, COLOR_DARK_GRAY); //3
}
