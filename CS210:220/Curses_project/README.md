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
```
### `drawC(int x, int y)`

This function draws the letter "C" at the specified x and y coordinates. The letter "C" is created using a series of characters (~ and |) to represent the shape of the letter.
```c
void drawC(int x, int y){
    move(x, y); 
    printw("~~~~~~~~~~~~~~~~~~~");  // Top part of 'C'
    for (int i = 1; i <= 10; i++) {
        move(x + i, y);
        printw("~");  // Left side of 'C'
    }
    move(x + 11, y);
    printw("~~~~~~~~~~~~~~~~~~~");  // Bottom part of 'C'
}
```

### `drawS(int x, int y)`
This function draws the letter "S" at the specified x and y coordinates. Similar to drawC(), it uses characters to form the shape of the letter "S" and prints each part on the screen accordingly.

```c
void drawS(int x, int y){
    move(x, y);
    printw("~~~~~~~~~~~~~~~~~~~");  // Top part of 'S'
    for (int i = 1; i <= 5; i++) {
        move(x + i, y);
        printw("~");  // Upper-left curve of 'S'
    }
    move(x + 6, y);
    printw("~~~~~~~~~~~~~~~~~~~");  // Middle of 'S'
    y += 18;
    for (int i = 1; i <= 5; i++) {
        move(x + 6 + i, y);
        printw("~");  // Lower-right curve of 'S'
    }
    move(x + 11, y - 18);
    printw("~~~~~~~~~~~~~~~~~~~");  // Bottom part of 'S'
}
```
