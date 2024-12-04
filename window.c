#include "window.h"
#include <ncurses.h>

WINDOW* Start(){
    //read config from file
    //create a screen
    WINDOW *win = newwin(3, 5, 3, 0);
    return win;
}

void ShowMenu(WINDOW* win){
    box(win, 0, 0);
    wrefresh(win);
}
