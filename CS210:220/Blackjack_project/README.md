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

### `getNextCard()`

This function generates a random card value between 2 and 11. Cards with values of 12 to 14 are treated as 10 to simulate the behavior of face cards (Jack, Queen, King) in Blackjack.
```c
int getNextCard() {
    srand(time(0));
    int nextcard;

    // Generate card value and ensure 12-14 are treated as 10
    nextcard = rand() % 14 + 2;
    if (nextcard > 11) {
        nextcard = 10;
    }
    return nextcard;
}
```
### `getProbabilityOfValueOrLower(int desiredValue)`
This function calculates the probability of drawing a card of the given value or lower. It simulates the probability of avoiding a bust in Blackjack by calculating based on the deck composition.

```c
double getProbabilityOfValueOrLower(int desiredValue) {
    double probability;

    // Return 100% probability if desired value >= 11
    if (desiredValue >= 11) {
        probability = 100.0;
    }
    // Probability of drawing a 10
    else if (desiredValue == 10) {
        probability = 48.0 / 52.0 * 100;
    }
    // Probability for values between 2 and 9
    else {
        probability = ((4.0 * (desiredValue - 1)) / 52.0) * 100;
    }
    return probability;
}
```
### `displayGameState(char* player1Name, int player1Score)`
This function displays the current game state, including the player's name, score, and the probability of drawing a card without busting.

```c
void displayGameState(char* player1Name, int player1Score) {
    int highestCard = 21 - player1Score;
    double probability = getProbabilityOfValueOrLower(highestCard);

    printf("%s your current total is %d\n", player1Name, player1Score);
    printf("You need a %d or lower to keep playing\n", highestCard);
    printf("The probability of you receiving a %d or lower is %.2lf%%\n", highestCard, probability);
}
```

### `getWinningPlayer(int player1Score, int player2Score)`
This function compares the scores of the player and dealer to determine the winner of the game. It returns 1 if player 1 wins, 2 if player 2 wins, 3 for a tie, and 0 if both bust.

```c
int getWinningPlayer(int player1Score, int player2Score) {
    if ((player1Score > player2Score && player1Score <= 21) || (player1Score <= 21 && player2Score > 21)) {
        return 1;
    } else if ((player2Score > player1Score && player2Score <= 21) || (player2Score <= 21 && player1Score > 21)) {
        return 2;
    } else if (player1Score == player2Score && player1Score <= 21 && player2Score <= 21) {
        return 3;
    } else {
        return 0;
    }
}
```
### `playBlackjack(char* playerName)`
This function simulates a player's turn in Blackjack. It handles the "hit" and "stay" actions and ensures that players can keep drawing cards until they either "stay" or bust.

```c
int playBlackjack(char* playerName) {
    int card, total = 0;
    char action = 'h';

    printf("\nPlayer Turn: %s\n", playerName);

    // Keep hitting cards until player busts or stays
    while (action == 'h') {
        card = getNextCard();
        total += card;
        printf("CARD: %d\n", card);

        if (total > 21) {
            printf("Bust!\n");
            break;
        } else if (total == 21) {
            printf("Blackjack!\n");
            break;
        } else {
            displayGameState(playerName, total);
            printf("Do you want to hit (h) or stay (s)?\n");
            action = getCharSafe();
        }
    }
    return total;
}
```
### `playGame()`
This function manages the overall game logic, asking for player names, running each player's turn, and determining the winner.
```c
void playGame() {
    char player1Name[50], player2Name[50];
    int player1Score, player2Score, winner;

    printf("Welcome to Blackjack\n");
    printf("Please Enter Player's Name: ");
    scanf("%s", player1Name);
    printf("Please Enter Dealer's Name: ");
    scanf("%s", player2Name);

    // Player and dealer take turns
    player1Score = playBlackjack(player1Name);
    player2Score = playBlackjack(player2Name);

    // Determine winner
    winner = getWinningPlayer(player1Score, player2Score);
    if (winner == 1) {
        printf("%s won!\n", player1Name);
    } else if (winner == 2) {
        printf("%s won!\n", player2Name);
    } else if (winner == 3) {
        printf("It's a tie!\n");
    } else {
        printf("Both players bust\n");
    }
}
```

## How to Compile and Run
### Compilation
Use the following command to compile the program:

```c
gcc -o blackjack pex2functs.c -lm
```

### Running the Game

Once compiled, you can run the game with:

```c
./blackjack
```




