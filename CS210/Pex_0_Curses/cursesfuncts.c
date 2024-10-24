#include <ncurses.h>
#define BLUE_WHITE 1
#define RED_WHITE 2
void colorsetup(){
    initscr();
    start_color();
    init_pair(BLUE_WHITE, COLOR_BLUE, COLOR_WHITE);
    init_pair(RED_WHITE, COLOR_RED, COLOR_WHITE);
    wbkgd(stdscr, COLOR_PAIR(BLUE_WHITE));
    attron(COLOR_PAIR(RED_WHITE));
}

void drawC(int x, int y){

    move(x,y);
    printw("~~~~~~~~~~~~~~~~~~~");
    x+=1;
    move(x,y);
    printw("~");
    x+=1;
    move(x,y);
    printw("~");
    x+=1;
    move(x,y);
    printw("~");
    x+=1;
    move(x,y);
    printw("~");
    x+=1;
    move(x,y);
    printw("~");
    x+=1;
    move(x,y);
    printw("~");
    x+=1;
    move(x,y);
    printw("~");
    x+=1;
    move(x,y);
    printw("~");
    x+=1;
    move(x,y);
    printw("~");
    x+=1;
    move(x,y);
    printw("~");
    x+=1;
    move(x,y);
    printw("~~~~~~~~~~~~~~~~~~~");
}

void drawS(int x, int y){
    
    move(x,y);
    printw("~~~~~~~~~~~~~~~~~~~");
    x+=1;
    move(x,y);
    printw("~");
    x+=1;
    move(x,y);
    printw("~");
    x+=1;
    move(x,y);
    printw("~");
    x+=1;
    move(x,y);
    printw("~");
    x+=1;
    move(x,y);
    printw("~");
    x+=1;
    move(x,y);
    printw("~~~~~~~~~~~~~~~~~~~");
    y+=18;
    x+=1;
    move(x,y);
    printw("~");
    x+=1;
    move(x,y);
    printw("~");
    x+=1;
    move(x,y);
    printw("~");
    x+=1;
    move(x,y);
    printw("~");
    x+=1;
    y-=18;
    move(x,y);
    printw("~~~~~~~~~~~~~~~~~~~");

    
}