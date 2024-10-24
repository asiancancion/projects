 /* =============================================================
 * Name: Caleb Song, 12/01/22
 * Section:  T6 Sample
 * Project:  Final Project - Memory
 * Purpose:  Functions to play game, create the deck, set cards in deck, have a playerTurn to change the board, write final deck and scores to a file, 
 *           free deck, print deck, and check winner
 * ============================================================= */
/** pex3functs.h
 */
#ifndef FINALPROJECTFUNCTS_H
#define FINALPROJECTFUNCTS_H
typedef struct player_struct {
    char name[50];
    int score;
} Player;
/**
* @brief plays the game, welcomes user, asks user for names, asks user for deck size
*/
void playGame();
/**
* @brief Creates deck of row size numRows and column size numCols
* @param numRows number of rows
* @param numCols number of columns
* @pre numRows and numCols must be an int
* @post numRows and numCols does not change
*/
char** createDeck(int numRows, int numCols);
/**
* @brief Goes through deck and assigns character pairs to random cards
* @param deck created in createDeck
* @param numRows number of rows
* @param numCols number of columns
* @pre numRows and numCols must be an int originalBoard must be a char**
* @post returns a filled out Deck
*/
char** setCards(char** deck, int numRows, int numCols);
/**
* @brief Takes user cards reveals them, compares two cards, and adds 1 to playerScore if they are the same
* @param deck deck with pairs filled out
* @param card1Row first card's row
* @param card1Col first card's col
* @param card2Row second card's row
* @param card2Col second card's col
* @param playerScore pointer to current player's score
* @pre Deck must be a char**, card1Row, card1Col, card2Row, card2Col must all be in array, playerScore must be int
* @post returns updated Deck and playerScore all other variables stay the same
*/
char** playerTurn(char** deck, char** answer, int card1Row, int card1Col, int card2Row, int card2Col, int numRows, int numCols, int* playerScore);
/**
* @brief frees Deck memory
* @param deck created in createDeck
* @param numRows number of rows
* @param numCols number of columns
* @pre numRows and numCols must be an int deck must be a char**
* @post numRows and numCols don't change deck memory is freed
*/
void freeDeck(char** deck, int numRows, int numCols);
/**
* @brief prints deck
* @param deck deck created in createDeck
* @param numRows number of rows
* @param numCols number of columns
* @pre numRows and numCols must be an int deck must be a char**
* @post numRows, numCols, deck don't change
*/
void printDeck(char** deck, int numRows, int numCols);
/**
* @brief writes final deck to a file, player scores, and winner
* @param deck created in createDeck
* @param numRows number of rows
* @param numCols number of columns
* @param player1Score player1's Score
* @param player2Score player2's Score
* @param player1Name player1's Name
* @param player2Name player2's Name
* @param filename name of file printed
* @pre numRows and numCols must be an int deck must be a char** filename must be a char* names must be chars and scores must be ints
* @post numRows, numCols, deck, filename don't change
*/
void writeDecktoFile(char** deck, int numRows, int numCols, int player1Score, int player2Score, char player1Name[], char player2Name[], char* filename);
/**
* @brief Checks to see if deck is cleared and prints out the winner
* @param deck deck created in createDeck
* @param numRows number of rows
* @param numCols number of columns
* @param player1Score score of player 1
* @param player2Score score of player 2
* @pre   player1Score, player2Score numRows, numCols are ints, deck is a char**, player1name, player2name is char
* @post numRows, numCols, Deck, player1Score, player2Score, player1Name, player2Name do not change
* @post returns 1 if player1 wins, 2 if player2 wins, 3 if there is a tie, and 0 is the board is not filled out
*/
int checkWinner(char** deck, int numRows, int numCols, int* player1Score, int* player2Score);
#endif // PEX3FUNCTS_H