/** pex2functs.h
 * =============================================================
 * Name: Caleb Song, 09/26/22
 * Section:  T6 Sample
 * Project:  PEX 2 - Blackjack
 * Purpose:  Declare functions to get a safe character, get next card, get probability of getting value or lower
 *           display current game state, get the winning player, and play the game
 * ============================================================= */
/** pex2functs.h
 */
#ifndef PEX2FUNCTS_H
#define PEX2FUNCTS_H
/**
* @brief Ensures that user inputs a safe character
*/
char getCharSafe();
/**
* @brief Get the next card to start the game and if the user "hits"
*/
int getNextCard();
/**
* @brief returns the probability that the next card will be a desired value (which would give blackjack) or lower
* @param desiredValue card value that will give blackjack; any value over desiredValue will result in a bust
* @pre desiredValue must be an integer
* @post desiredValue does not change
*/
double getProbabilityOfValueOrLower(int desiredValue);
/**
* @brief Displays the current game state with current total, value to get blackjack, and probability of getting that value
* @param player1Name name of player currently being dealt
* @param player1Score total card value of player1Name
* @pre player1Name must be a string and player1Score must be an integer
* @post player1Name and player1Score do not change
*/
void displayGameState(char* player1Name, int player1Score);
/**
* @brief returns a 1 if player1 wins, 2 if player2 wins, 3 if they tie, and 0 if both bust
* @param player1Score card value of player1
* @param player2Score card value of player2
* @pre player1Score and player2Score must be integers 
* @post player1Score and player2Score do not change
*/
int getWinningPlayer(int player1Score, int player2Score);
/**
* @brief Plays blackjack for the playerName provided
* @param playerName player who is currently playing blackjack
* @pre playerName must be a string
* @post playerName does not change
*/
int playBlackjack(char* playerName);
/**
* @brief plays the game when uncommented in main of pex2.c file
*/
void playGame();
#endif // PEX2FUNCTS_H
