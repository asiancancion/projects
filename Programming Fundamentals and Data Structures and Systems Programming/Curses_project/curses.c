
// Include the Curses library
#include <stdio.h>
#include <ncurses.h>
#include "cursesfuncts.h"
#define BLUE_WHITE 1
#define RED_WHITE 2

int main(){
    colorsetup();
    drawC(5,10);
    drawS(5,45);
    attroff(COLOR_PAIR(RED_WHITE));
    move(23,10);
    printw("Created with Curses by Caleb Song");
    getch();
    endwin();
    return 0;
}

