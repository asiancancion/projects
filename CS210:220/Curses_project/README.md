# Curses Initials

## Project Overview
This project uses the **ncurses** library to create a simple text-based graphical application that draws the letters "C" and "S" on the terminal. The application is implemented using C and leverages the power of ncurses for handling terminal output, colors, and screen manipulation. It writes my intials :D

## Features
- **Curses Library Usage**: Uses the ncurses library to manipulate the terminal and print characters with colors.
- **Custom Drawing Functions**: Includes custom functions `drawC()` and `drawS()` to draw the letters "C" and "S" in specific locations on the terminal screen.
- **Color Setup**: Configures background and foreground colors using `init_pair()` for enhanced visuals.

## Code Explanation

### `colorsetup()`
This function initializes the curses environment and sets up color pairs for the terminal. It changes the background to blue and white and sets the text color to red and white.
```c
void colorsetup(){
    initscr();
    start_color();
    init_pair(BLUE_WHITE, COLOR_BLUE, COLOR_WHITE);
    init_pair(RED_WHITE, COLOR_RED, COLOR_WHITE);
    wbkgd(stdscr, COLOR_PAIR(BLUE_WHITE));
    attron(COLOR_PAIR(RED_WHITE));
}
