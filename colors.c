#include "colors.h"
#include <ncurses.h>
#include <stdlib.h>

void StartColor() {
    if(has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_GREEN, 0, 750, 0);

    init_color(COLOR_LIGHT_GRAY, 609, 609, 609);
    init_color(COLOR_GRAY, 330, 330, 330);
    init_color(COLOR_DARK_GRAY, 100, 100, 100);

    init_pair(1, COLOR_GREEN, COLOR_DARK_GRAY);
    init_pair(2, COLOR_WHITE, COLOR_DARK_GRAY);
}
