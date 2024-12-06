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
    init_color(COLOR_GREEN, 0, 750, 0);
    init_color(COLOR_DARK_GREEN, 0, 500, 0);
    init_color(COLOR_DARKER_GREEN, 105, 211, 78);
    init_color(COLOR_WHITE, 900, 900, 900);

    init_color(COLOR_LIGHT_GRAY, 609, 609, 609);
    init_color(COLOR_GRAY, 330, 330, 330);
    init_color(COLOR_DARK_GRAY, 100, 100, 100);
    init_color(COLOR_DARKER_GRAY, 50, 50, 50);

    init_pair(1, COLOR_GREEN, COLOR_DARK_GRAY);
    init_pair(2, COLOR_WHITE, COLOR_DARK_GRAY);

    //COLORS FOR GROUND
    init_pair(10, COLOR_WHITE, COLOR_DARK_GREEN); //GRASS
    init_pair(11, COLOR_WHITE, COLOR_DARKER_GRAY); //ROAD
    init_pair(12, COLOR_WHITE, COLOR_CYAN); //WATER
    init_pair(19, COLOR_WHITE, COLOR_RED); //FINISH

    //colors for objects
    init_pair(20, COLOR_GREEN, COLOR_DARKER_GREEN); //FROG
}
