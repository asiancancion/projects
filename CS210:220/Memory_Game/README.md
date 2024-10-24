# Memory Game Implementation

**Author**: Caleb Song  
**Section**: T6 Sample  
**Project**: Final Project - Memory Game  
**Date**: 12/01/22  

## Purpose
This project implements a classic memory card game where two players take turns selecting two cards to match. The game board contains a random selection of pairs of cards, and players reveal the cards by inputting the row and column of each card. If the two selected cards match, the player earns a point, and the cards remain revealed. The game continues until all cards are matched, and the player with the most points wins.

## Game Flow

1. **Player Names & Setup**: 
   - The game begins by asking for player names and the number of cards they wish to play with.
   - The number of cards must be an even number between 4 and 52.

2. **Board Creation**: 
   - Two game boards are created: a hidden board where all cards are represented as "?" and an answer board that holds the actual card values.
   - The cards are randomly placed on the board in pairs.

3. **Player Turns**: 
   - Players take turns choosing two cards by entering their coordinates.
   - If the two cards match, they remain revealed, and the player earns a point.
   - If the cards don't match, they are briefly revealed and then hidden again.

4. **Game End**: 
   - The game ends when all cards have been matched.
   - The player with the most points wins, and in case of a tie, both players are declared tied.

5. **Result Storage**: 
   - The game saves the final board and player scores to a file.

---

## Functions

### `playGame()`
The main function of the game that handles the setup, player turns, and checking for the winner.

- **Player Input**: Prompts for player names and the number of cards.
- **Board Setup**: Initializes both the hidden and answer boards.
- **Player Turns**: Alternates turns between the two players until the game is finished.
- **Winner Announcement**: Determines the winner based on the score and displays the results.

### `createDeck()`
Creates a deck of a given size and initializes all positions with '?' to represent hidden cards.

### `setCards()`
Randomly assigns pairs of characters (cards) to the board. Each card is assigned to two random positions on the answer board.

### `playerTurn()`
Handles the logic for each player's turn, revealing the chosen cards, checking for matches, and updating the player's score.

### `writeDecktoFile()`
Saves the final game state, including the revealed cards and scores, to a file.

### `freeDeck()`
Frees the memory allocated for the game board.

### `printDeck()`
Prints the current state of the game board, showing hidden and revealed cards.

### `checkWinner()`
Checks if the game is over and determines the winner or if the game ends in a tie.

---

## Sample Gameplay

1. **Setup**:
   - Players enter their names.
   - The game asks how many cards to play with (must be an even number between 4 and 52).

2. **Game Loop**:
   - Player 1 selects two cards.
   - If the cards match, they stay revealed, and Player 1 earns a point.
   - If the cards don't match, they are hidden again.
   - Player 2 takes their turn.
   - The game continues until all cards are revealed.

3. **End Game**:
   - The game announces the winner or declares a tie.
   - The final board and scores are saved to a file.

