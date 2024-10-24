/** finalprojectfuncts.c
 * =============================================================
 * Name: Caleb Song, 12/01/22
 * Section:  T6 Sample
 * Project:  Final Project - Memory
 * Purpose:  Functions to play game, create the deck, set cards in deck, have a playerTurn to change the board, write final deck and scores to a file, 
 *           free deck, print deck, and check winner
 * ============================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "finalprojectfuncts.h"

void playGame(){
    srand(time(NULL));   // Initialization, should only be called once.
    Player player1;
    Player player2;
    player1.score = 0;
    player2.score = 0;
    int size;
    int numRows;
    int numCols;
    int check;
    int card1Row;
    int card1Col;
    int card2Row;
    int card2Col;
    char** answerBoard;
    char** hiddenBoard;
    //Welcomes users and gets names
    printf("+=================+\n");
    printf(" Welcome to Memory\n");
    printf("+=================+\n");
    printf("Enter first user's name: ");
    scanf("%s",player1.name);
    printf("Hello %s\n", player1.name);
    printf("Enter second user's name: ");
    scanf("%s",player2.name);
    printf("Hello %s\n", player2.name);
    //Collects amount of cards users want to play with - if it is not even or between 4 and 52 it will keep asking
    do {
        printf("How many cards would you like to have (this must be an even number between 4 and 52): ");
        scanf("%d", &size);
    }while((size%2!=0) || size < 4 || size > 52);
    //Create the board parameters based on user's selected size
    if (size <= 10 || size == 14 || size == 22 || size == 26 || size == 34 || size == 38 || size == 46){
        numRows = 2;
        numCols = size/numRows;
    }
    else if (size == 12 || size == 16 || size == 20 || size == 24 || size == 28 || size == 32 || size == 44 || size == 52){
        numRows = 4;
        numCols = size/numRows;
    }
    else if (size == 18){
        numRows = 3;
        numCols = size/numRows;
    }
    else if (size == 40 || size == 50){
        numRows = 5;
        numCols = size/numRows;
    }
    else if (size == 30 || size == 36 || size == 42 || size == 48){
        numRows = 6;
        numCols = size/numRows;
    }
    //Create two boards - one with the pairs and the other with ? to show the "backs" of the cards
    hiddenBoard = createDeck(numRows,numCols);
    answerBoard = createDeck(numRows,numCols);
    answerBoard = setCards(answerBoard, numRows, numCols);
    //printDeck(answerBoard,numRows,numCols);
    printf("\n");
    printDeck(hiddenBoard,numRows,numCols);
    //Plays the game until check != 0 meaning there is a tie, player1 wins or player2 wins
    while(check == 0){
        //Will loop until player picks a card that has not yet been revealed
        do {
           
            printf("%s input coordinate of card 1: ",player1.name);
            scanf("%d %d", &card1Row,&card1Col);
            printf("%s input coordinate of card 2: ",player1.name);
            scanf("%d %d", &card2Row,&card2Col);
        }while(hiddenBoard[card1Row][card1Col] != '?' || hiddenBoard[card2Row][card2Col] != '?' || card1Row > numRows-1 || card1Col > numCols-1 || card2Row > numRows-1 || card2Col > numCols-1);
        //Check board to see if there is match
        hiddenBoard = playerTurn(hiddenBoard, answerBoard, card1Row, card1Col, card2Row, card2Col, numRows, numCols, &player1.score);
        printDeck(hiddenBoard,numRows,numCols);
        //Will return 0 if the board is not filled if not will return if a player wins or there is a tie
        check = checkWinner(hiddenBoard,numRows,numCols,&player1.score,&player2.score);
        //If board is fully revealed will break from the loop
        if (check !=0){
            break;
        }
        do {
            printf("%s input coordinate of card 1: ",player2.name);
            scanf("%d %d", &card1Row,&card1Col);
            printf("%s input coordinate of card 2: ",player2.name);
            scanf("%d %d", &card2Row,&card2Col);
        }while(hiddenBoard[card1Row][card1Col] != '?' || hiddenBoard[card2Row][card2Col] != '?' || card1Row > numRows-1 || card1Col > numCols-1 || card2Row > numRows-1 || card2Col > numCols-1);
        hiddenBoard = playerTurn(hiddenBoard, answerBoard, card1Row, card1Col, card2Row, card2Col, numRows, numCols, &player2.score);
        printDeck(hiddenBoard,numRows,numCols);
        check = checkWinner(hiddenBoard,numRows,numCols,&player1.score,&player2.score);
    }
    //prints out players and score after game is finished
    printf("Player1: %s\n", player1.name);
    printf("Score: %d\n", player1.score);
    printf("Player2: %s\n", player2.name);
    printf("Score: %d\n", player2.score);
    if(check == 1){
        printf("%s wins with a score of %d!\n", player1.name, player1.score);
    }
    else if(check == 2){
        printf("%s wins with a score of %d!\n", player2.name, player2.score);
    }
    else{
        printf("Tied! Both players got a score of %d\n", player2.score);
    }
    //Writes answer key to file with score and winner
    writeDecktoFile(answerBoard, numRows, numCols, player1.score, player2.score, player1.name, player2.name, "answerkey");
    sleep(3);
    printf("Answer Board:\n");
    for (int i=0; i <numRows; i++){
        for (int j=0; j<numCols; j++){
            printf("%c", answerBoard[i][j]);
        }
        printf("\n");
    }
}

char** createDeck(int numRows, int numCols){
    char** deck = NULL;
    deck = (char**) malloc(numRows * sizeof(char*));
    for (int i = 0; i <numRows; i++){
        deck[i] = (char*) malloc(numCols * sizeof(char));
    }
    //set all values of board to char '?'
    for (int i=0; i <numRows; i++){
        for (int j=0; j<numCols; j++){
            deck[i][j] = '?';
        }
    }
    return deck;
    
}

char** setCards(char** deck, int numRows, int numCols){
    char letters[] = {'a', 'b', 'c', 'd','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int iterations = (numRows * numCols)/2;
    int ranRow;
    int ranCol;
    char ranChar;
    //Randomly assigns letters in array to cards
    for (int i = 0; i < iterations; i++){
        ranChar = letters[i];
        do{
        ranRow = rand() % numRows;
        ranCol = rand() % numCols;
        }
        while(deck[ranRow][ranCol] != '?');
        //ensures that if a already assigned character is chosen it will try again
        deck[ranRow][ranCol] = ranChar;
        do{
        ranRow = rand() % numRows;
        ranCol = rand() % numCols;
        }
        while(deck[ranRow][ranCol] != '?');
        deck[ranRow][ranCol] = ranChar; 
    }
    return deck;

}

char** playerTurn(char** deck, char** answer, int card1Row, int card1Col, int card2Row, int card2Col, int numRows, int numCols, int* playerScore){
    char card1 = answer[card1Row][card1Col];
    char card2 = answer[card2Row][card2Col];
    char** temp;
    temp = createDeck(numRows,numCols);
    //goes through each row and column and sets temp deck to the hidden deck
    for (int i=0; i <numRows; i++){
        for (int j=0; j<numCols; j++){
            temp[i][j] = deck[i][j];
        }
    }
    //If there is match increases player score by 1 and changes hidden board to reveal cards
    if (card1 == card2){
        printf("Match!\n");
        deck[card1Row][card1Col] = card1;
        deck[card2Row][card2Col] = card1;
        *playerScore+= 1;
        return deck;
    }
    //If there is no match temporarily flips the cards then clears the board
    else{
        printf("No Match!\n");
        temp[card1Row][card1Col] = card1;
        temp[card2Row][card2Col] = card2;
        printDeck(temp,numRows,numCols);
        sleep(5);
        freeDeck(temp,numRows,numCols);
        system("clear");
        return deck;
    }

}

void writeDecktoFile(char** board, int numRows, int numCols, int player1Score, int player2Score, char player1Name[], char player2Name[], char* filename){
    //writes final deck to file
    FILE* file = fopen(filename,"w");
    fprintf(file,"Player1: %s\n", player1Name);
    fprintf(file,"Score: %d\n", player1Score);
    fprintf(file,"Player2: %s\n", player2Name);
    fprintf(file,"Score: %d\n", player2Score);
    if(player1Score > player2Score){
        fprintf(file,"%s wins with a score of %d\n", player1Name, player1Score);
    }
    else if(player2Score > player1Score){
        fprintf(file,"%s wins with a score of %d\n", player2Name, player2Score);
    }
    else{
        fprintf(file,"Tied! Both players got a score of %d\n", player2Score);
    }
    fprintf(file, "Answer Key:\n");
    for (int i=0; i <numRows; i++){
        for (int j=0; j<numCols; j++){
            fprintf(file,"%c", board[i][j]);
        }
        fprintf(file,"\n");
    }
}

void freeDeck(char** deck, int numRows, int numCols){
    //frees deck memory
    for (int i =0; i<numRows; i++){
        free(deck[i]);
    }
    free(deck);
}

void printDeck(char** deck, int numRows, int numCols){
    //goes through each row and column and prints
    printf("  ");
    for (int j=0; j<numCols; j++){
        if (j > 9){
            printf("..");
        }
        else{
            printf("%d ", j);
        }
    }
    printf("\n");
    for (int i=0; i <numRows; i++){
        printf("%d ", i);
        for (int j=0; j<numCols; j++){
            printf("%c ", deck[i][j]);
        }
        printf("\n");
    }
}

int checkWinner(char** deck, int numRows, int numCols, int* player1Score, int* player2Score){
    //not all cards revealed returns 0
    for (int i=0; i <numRows; i++){
        for (int j=0; j<numCols; j++){
            if (deck[i][j] == '?'){
                return 0;
            }
        }
    }
    //player 1 wins returns 1
    if (*player1Score > *player2Score){
        return 1;
    }
    //player 2 wins returns 2
    else if(*player2Score > *player1Score){
        return 2;
    }
    //tie returns 3
    else{
        return 3;
    }
}