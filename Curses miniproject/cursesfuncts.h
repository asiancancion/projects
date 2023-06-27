
#ifndef CURSESFUNCTS_H
#define CURSESFUNCTS_H


#include <ncurses.h>
#define BLUE_WHITE 1
#define RED_WHITE 2
/**
* @brief starts window, initiates color pair, and turns on red_white color pair
*/
void colorsetup();
/**
* @brief draws the letter "C"
* @param x starting x coordinate at top left of letter "C"
* @param y starting y coordinate at top left of letter "C"
* @pre x and y must be integers, colorsetup() must be run first
* @post x and y changes to bottom left of letter "C"
*/
void drawC(int x, int y);
/**
* @brief draws the letter "S"
* @param x starting x coordinate at top left of letter "S"
* @param y starting y coordinate at top left of letter "S"
* @pre x and y must be integers, colorsetup() must be run first
* @post x and y changes to bottom left of letter "S"
*/
void drawS(int x, int y);

#endif // CURSESFUNCTS_H