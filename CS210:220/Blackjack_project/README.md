# Blackjack Game

## Name: Caleb Song  
**Date**: 09/26/22  
**Section**: T6 Sample  
**Project**: PEX 2 - Blackjack  
**Purpose**:  
The goal of this project is to implement a basic Blackjack game in C, including functions for drawing cards, determining the winner, calculating probabilities, and managing game states. The game allows a player to play against the dealer, and supports all typical Blackjack actions such as "hit" and "stay."

## Functions Overview

### `getCharSafe()`
This function safely captures a character input from the user, ensuring that the input is a valid character. If the input is invalid, it prints an error message and terminates the program.

```c
char getCharSafe() {
    char value;
    int scanfReturn = 0;

    // Read a character and check if it's valid
    scanfReturn = scanf(" %c", &value);
    fflush(stdin);

    // If the input is not a valid character, exit with an error
    if (isalpha(scanfReturn) != 0) {
        fprintf(stderr, "Bad char input - terminating\n");
        exit(1);
    }
    return value;
}
```

### getNextCard()

