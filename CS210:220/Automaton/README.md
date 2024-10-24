# PEX 3 - Automaton

## Name: Caleb Song  
**Date**: 11/07/22  
**Section**: T6 Sample  
**Project**: PEX 3 - Cellular Automaton  
**Purpose**:  
This project simulates a **Cellular Automaton**. The automaton evolves based on user-defined rules over a grid of cells. The program implements the following functionalities:
- Board creation and memory management
- Copying and comparing boards
- Printing and writing the final board to a file
- Iteratively updating the board state based on specific rules
- Allowing users to interact with the simulation by advancing iterations or running to completion.

## Functions Overview

### `getBit(int value, int bit)`
This function converts an integer to its binary representation and extracts a specific bit from that value. The rightmost bit is considered bit 0. This function is used to apply the automaton's rule set during board updates.

```c
int getBit(int value, int bit) {
    unsigned int mask = 0b00000000000000000000000000000001 << bit;
    return (value & mask) >> bit;
}


```

### `createBoard(int numRows, int numCols)`
This function dynamically allocates memory for the board and initializes it. The board is set up such that all cells are initially blank, except for the middle of the top row, which is filled.

```c
char** createBoard(int numRows, int numCols) {
    char** board = (char**) malloc(numRows * sizeof(char*));
    for (int i = 0; i < numRows; i++) {
        board[i] = (char*) malloc(numCols * sizeof(char));
    }
    // Set all values to BLANK
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            board[i][j] = BLANK;
        }
    }
    board[0][numCols / 2] = FILLED;  // Fill the center of the top row
    return board;
}

```

### `copyBoard(char** originalBoard, int numRows, int numCols)`
This function creates a copy of the original board. It dynamically allocates memory for a new board and copies the contents of originalBoard to the new one.

```c
char** copyBoard(char** originalBoard, int numRows, int numCols) {
    char** board = (char**) malloc(numRows * sizeof(char*));
    for (int i = 0; i < numRows; i++) {
        board[i] = (char*) malloc(numCols * sizeof(char));
    }
    // Copy original board values
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            board[i][j] = originalBoard[i][j];
        }
    }
    return board;
}

```

### `compareBoards(char** board1, char** board2, int numRows, int numCols)`
This function compares two boards and counts the number of differences between them. It returns the count of differing cells.

```c
int compareBoards(char** board1, char** board2, int numRows, int numCols) {
    int counter = 0;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (board1[i][j] != board2[i][j]) {
                counter++;
            }
        }
    }
    return counter;
}

```

### `freeBoard(char** board, int numRows, int numCols)`
This function frees the memory allocated for the board.
```c
void freeBoard(char** board, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        free(board[i]);
    }
    free(board);
}

```

### `printBoard(char** board, int numRows, int numCols)`
This function prints the current state of the board to the console.


```c
void printBoard(char** board, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}
```

### `writeBoardToFile(char** board, int numRows, int numCols, char* filename)`
This function writes the final state of the board to a file.

```c
void writeBoardToFile(char** board, int numRows, int numCols, char* filename) {
    FILE* file = fopen(filename, "w");
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            fprintf(file, "%c", board[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

```

### `updateBoard(char** board, int automaton, int numRows, int numCols)`
This function updates the board based on the selected rule (automaton). It applies the rule to each cell based on its neighbors and updates the board for the next iteration.


```c
char** updateBoard(char** board, int automaton, int numRows, int numCols) {
    char** newboard = copyBoard(board, numRows, numCols);
    newboard[0][numCols / 2] = FILLED;
    int row = -1;

    // Identify which row will be updated
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (newboard[i][j] == FILLED) {
                break;
            } else if (j == numCols - 1) {
                row = i;
                break;
            }
        }
        if (row != -1) {
            break;
        }
    }

    // Update the board based on the rule
    for (int j = 0; j < numCols; j++) {
        char block1 = newboard[row - 1][j];
        char block2 = newboard[row - 1][j + 1];
        char block3 = newboard[row - 1][j + 2];

        // Apply the automaton rules (handles edges and general cases)
        // ... [logic for updating board based on rule] ...
    }

    freeBoard(board, numRows, numCols);
    return newboard;
}

```
### `playGame()`
This function manages the entire game loop. It allows the user to play the game by advancing one iteration at a time or running the automaton to completion. It also prints the board after each iteration and writes the final board to a file.

```c
void playGame() {
    int rows, cols, rule, iteration = 0;
    char** board;
    char choice[10];

    printf("===================\n");
    printf("Welcome to Automata\n");
    printf("===================\n");

    // Get user input for rows, columns, and rule
    printf("How many Rows: ");
    scanf("%d", &rows);
    printf("How many Cols: ");
    scanf("%d", &cols);
    printf("Which Rule: ");
    scanf("%d", &rule);

    board = createBoard(rows, cols);
    printf("==== AUTOMATAN %d after %d iterations====\n", rule, iteration);
    printBoard(board, rows, cols);

    // Game loop
    printf("Press Enter to advance one iteration; Type 'c' to run to completion. Type 'e' to exit: ");
    fgets(choice, 10, stdin);
    iteration++;

    while (iteration < rows) {
        if (*choice == '\n') {
            printf("==== AUTOMATAN %d after %d iterations====\n", rule, iteration);
            board = updateBoard(board, rule, rows, cols);
            printBoard(board, rows, cols);
            printf("Press Enter to advance one iteration; Type 'c' to run to completion. Type 'e' to exit: ");
            fgets(choice, 10, stdin);
            iteration++;
        } else if (*choice == 'c') {
            while (iteration < rows) {
                board = updateBoard(board, rule, rows, cols);
                iteration++;
            }
            printf("==== AUTOMATAN %d after %d iterations====\n", rule, iteration);
            printBoard(board, rows, cols);
            break;
        } else if (*choice == 'e') {
            break;
        }
    }

    // Write final board to file
    writeBoardToFile(board, rows, cols, "final_board.txt");
    printf("Program Complete\n");
    freeBoard(board, rows, cols);
}

```



