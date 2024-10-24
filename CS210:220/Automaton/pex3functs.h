/** pex3functs.h
 * =============================================================
 * Name: Caleb Song, 11/07/22
 * Section:  T6 Sample
 * Project:  PEX 3 - Automaton
 * Purpose:  Declare functions to create a board, copy a board, compare two boards, free board memory,
 *           print the board, write the final board to a file, update the board with iterations, and playing the game
 * ============================================================= */
/** pex3functs.h
 */
#ifndef PEX3FUNCTS_H
#define PEX3FUNCTS_H
#define BLANK '_'
#define FILLED 'x'
/**
* @brief Creates board of row size numRows and column size numCols
* @param numRows number of rows
* @param numCols number of columns
* @pre numRows and numCols must be an int
* @post numRows and numCols does not change
*/
char** createBoard(int numRows, int numCols);
/**
* @brief Creates board of row size numRows and column size numCols
* @param originalBoard board created in createBoard
* @param numRows number of rows
* @param numCols number of columns
* @pre numRows and numCols must be an int originalBoard must be a char**
* @post numRows and numCols does not change returns a copied board
*/
char** copyBoard(char** originalBoard, int numRows, int numCols);
/**
* @brief compares two boards: board1 and board2
* @param board1 1st board to compare
* @param board2 2nd board to compare
* @param numRows number of rows
* @param numCols number of columns
* @pre numRows and numCols must be an int board1 and board2 must be a char**
* @post numRows, numCols, board1, and board2 don't change returns number of differences
*/
int compareBoards(char** board1, char** board2, int numRows, int numCols);
/**
* @brief frees board memory
* @param board board created in createBoard
* @param numRows number of rows
* @param numCols number of columns
* @pre numRows and numCols must be an int board must be a char**
* @post numRows and numCols don't change board memory is freed
*/
void freeBoard(char** board, int numRows, int numCols);
/**
* @brief prints board
* @param board board created in createBoard
* @param numRows number of rows
* @param numCols number of columns
* @pre numRows and numCols must be an int board must be a char**
* @post numRows, numCols, board don't change
*/
void printBoard(char** board, int numRows, int numCols);
/**
* @brief writes final board to a file
* @param board board created in createBoard
* @param numRows number of rows
* @param numCols number of columns
* @param filename name of file printed
* @pre numRows and numCols must be an int board must be a char** filename must be a char*
* @post numRows, numCols, board, filename don't change
*/
void writeBoardToFile(char** board, int numRows, int numCols, char* filename);
/**
* @brief updates board for one iteration
* @param board board created in createBoard
* @param automaton automaton number
* @param numRows number of rows
* @param numCols number of columns
* @pre automaton, numRows, numCols are ints, board is a char**
* @post numRows, numCols, board, automaton don't change, board updates
*/
char** updateBoard(char** board, int automaton, int numRows, int numCols);
/**
* @brief plays the game
*/
void playGame();
#endif // PEX3FUNCTS_H