/** pex3functs.c
 * =============================================================
 * Name: Caleb Song, 11/07/22
 * Section:  T6 Sample
 * Project:  PEX 3 - Automaton
 * Purpose:  Declare functions to create a board, copy a board, compare two boards, free board memory,
 *           print the board, write the final board to a file, update the board with iterations, and playing the game
 * ============================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pex3functs.h"
/** 
 * @brief Converts an integer to binary, and gets a specific bit from the number
 *        the rightmost bit is bit 0.  This function works--don't break it!
 * @param value the integer we want to convert to binary
 * @param bit the bit we want to extract from the binary
 * @return a 1 or a 0, depending on what value is stored at the specified bit
 */ 
int getBit(int value, int bit) {
    unsigned int mask = 0b00000000000000000000000000000001 << bit;
    return (value & mask) >> bit;
}
char** createBoard(int numRows, int numCols){
    char** board = NULL;
    board = (char**) malloc(numRows * sizeof(char*));
    for (int i = 0; i <numRows; i++){
        board[i] = (char*) malloc(numCols * sizeof(char));
    }
    //set all values of board to BLANK
    for (int i=0; i <numRows; i++){
        for (int j=0; j<numCols; j++){
            board[i][j] = BLANK;
        }
    }
    //set middle top row value to FILLED
    board[0][numCols/2]=FILLED;
    return board;
}
char** copyBoard(char** originalBoard, int numRows, int numColumns){
    //creates new board to copy
    char** board = NULL;
    board = (char**) malloc(numRows * sizeof(char*));
    for (int i = 0; i <numRows; i++){
        board[i] = (char*) malloc(numColumns * sizeof(char));
    }
    //Copies each value of originalBoard to board
    for (int i=0; i <numRows; i++){
        for (int j=0; j<numColumns; j++){
            board[i][j] = originalBoard[i][j];
        }
    }
    return board;
}
int compareBoards(char** board1, char** board2, int numRows, int numCols){
    int counter =0;
    //Compares each value of board1 and board2 and counts difference
    for (int i=0; i <numRows; i++){
        for (int j=0; j<numCols; j++){
            if(board1[i][j] != board2[i][j]){
                counter+=1;
            }
        }
    }
    return counter;
}
void freeBoard(char** board, int numRows, int numCols){
    //frees board memory
    for (int i =0; i<numRows; i++){
        free(board[i]);
    }
    free(board);
}
void printBoard(char** board, int numRows, int numCols){
    //goes through each row and column and prints
    for (int i=0; i <numRows; i++){
        for (int j=0; j<numCols; j++){
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}
void writeBoardToFile(char** board, int numRows, int numCols, char* filename){
    //writes final board to file
    FILE* file = fopen(filename,"w");
    for (int i=0; i <numRows; i++){
        for (int j=0; j<numCols; j++){
            fprintf(file,"%c", board[i][j]);
        }
        fprintf(file,"\n");
    }
}
char** updateBoard(char** board, int automaton, int numRows, int numCols){
    char block1;
    char block2;
    char block3;
    int row = -1;
    //copies board to a newboard
    char** newboard = copyBoard(board, numRows, numCols);
    newboard[0][numCols/2] = FILLED;
    //Determines which row will be updated
    for (int i=0; i <numRows; i++){
        for (int j=0; j<numCols; j++){
            if(newboard[i][j] == FILLED){
                break;
            }
            else if(j == numCols-1){
                row = i;
                break;
            }
            else{
                continue;
            }
        }
        if (row != -1){
            break;
        }

    }
    for (int j=0; j<numCols; j++){
        block1 = newboard[row-1][j];
        block2 = newboard[row-1][j+1];
        block3 = newboard[row-1][j+2];
        //For the leftmost part of the automaton assumes first block is a blank
        if (j == 0){
            if ((block1 == BLANK) && (block2 == FILLED) && (getBit(automaton,1) == 1)){
                newboard[row][j] = FILLED;
            }
            else if((block1 == FILLED) && (block2 == BLANK) && (getBit(automaton,2) == 1)){
                newboard[row][j] = FILLED;
            }
            else if((block1 == FILLED) && (block2 == FILLED) && (getBit(automaton,3) == 1)){
                newboard[row][j] = FILLED;
            }
        }
        //For the rightmost part of the automaton assumes third block is a blank
        else if (j == numCols-2){
            if ((block1 == BLANK) && (block2 == FILLED) && (getBit(automaton,2) == 1)){
                newboard[row][j+1] = FILLED;
            }
            else if((block1 == FILLED) && (block2 == BLANK) && (getBit(automaton,4) == 1)){
                newboard[row][j+1] = FILLED;
            }
            else if((block1 == FILLED) && (block2 == FILLED) && (getBit(automaton,6) == 1)){
                newboard[row][j+1] = FILLED;
            }
        }
        //Checks to ensure 3 blocks are satisfied with rule
        if ((block1 == BLANK) && (block2 == BLANK) && (block3 == BLANK) && (getBit(automaton,0) == 1)){
            newboard[row][j+1] = FILLED;
        }
        else if ((block1 == BLANK) && (block2 == BLANK) && (block3 == FILLED) && (getBit(automaton,1) == 1)){
            newboard[row][j+1] = FILLED;
        }
        else if ((block1 == BLANK) && (block2 == FILLED) && (block3 == BLANK) && (getBit(automaton,2) == 1)){
            newboard[row][j+1] = FILLED;
        }
        else if ((block1 == BLANK) && (block2 == FILLED) && (block3 == FILLED) && (getBit(automaton,3) == 1)){
            newboard[row][j+1] = FILLED;
        }
        else if ((block1 == FILLED) && (block2 == BLANK) && (block3 == BLANK) && (getBit(automaton,4) == 1)){
            newboard[row][j+1] = FILLED;
        }
        else if ((block1 == FILLED) && (block2 == BLANK) && (block3 == FILLED) && (getBit(automaton,5) == 1)){
            newboard[row][j+1] = FILLED;
        }
        else if ((block1 == FILLED) && (block2 == FILLED) && (block3 == BLANK) && (getBit(automaton,6) == 1)){
            newboard[row][j+1] = FILLED;
        }
        else if ((block1 == FILLED) && (block2 == FILLED) && (block3 == FILLED) && (getBit(automaton,7) == 1)){
            newboard[row][j+1] = FILLED;
        }
    }
    freeBoard(board, numRows, numCols);
    return newboard;
}

void playGame(){
    int rows;
    int cols;
    int rule;
    int iteration =0;
    char** board;
    char choice[10];
    printf("===================\n");
    printf("Welcome to Automata\n");
    printf("===================\n");
    //get player rows
    printf("How many Rows: ");
    scanf("%d", &rows);
    //get player columns
    printf("How many Cols: ");
    scanf("%d", &cols);
    printf("Which Rule: ");
    scanf("%d", &rule);
    board = createBoard(rows,cols);
    printf("==== AUTOMATAN %d after %d iterations====\n", rule, iteration);
    printBoard(board, rows, cols);
    printf("Press Enter to advance one iteration; Type 'c' to run to completion. Type 'e' to exit: ");
    printf("\n");
    fgets(choice, 10, stdin);
    iteration+=1;
    while (iteration < rows){
        //checks to see if user entered
        if (*choice == '\n'){
            printf("==== AUTOMATAN %d after %d iterations====\n", rule, iteration);
            board = updateBoard(board, rule, rows, cols);
            printBoard(board, rows, cols);
            printf("Press Enter to advance one iteration; Type 'c' to run to completion. Type 'e' to exit: ");
            fgets(choice, 10, stdin);
            iteration+=1;
        }
        //if user wants to complete the automaton
        else if (*choice == 'c'){
            while (iteration < rows){
                board = updateBoard(board, rule, rows, cols);
                iteration+=1;
            }
            iteration -=1;
            printf("==== AUTOMATAN %d after %d iterations====\n", rule, iteration);
            printBoard(board, rows, cols);
            break;
        }
        //if user wants to exit
        else if (*choice == 'e'){
            break;
        }
    }
    //writes final board to final_board.txt file
    writeBoardToFile(board, rows, cols, "final_board");
    printf("Program Complete\n");
    freeBoard(board,rows,cols);
}