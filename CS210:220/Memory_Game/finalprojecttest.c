/** pex3test.h
 * =============================================================
 * Name: Caleb Song, 12/01/22
 * Section:  T6 Sample
 * Project:  Final Project - Memory
 * Purpose:  Test createDeck, setCards, and checkWinner
 * ============================================================= */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "finalprojecttest.h"
#include "finalprojectfuncts.h"
void runAllTests() {
    testCreateDeck();
    testSetCards();
    testCheckWinner();
    //If all functions pass tests, prints "all tests passed"
    printf("All tests passed!\n");
}


void testCreateDeck(){
    int rows;
    int cols;
    rows = 5;
    cols = 6;
    //Test all characters in array are ? for the preset hidden board
    for (int i =0; i< rows; i++){
        for (int j=0; j<cols;j++){
            assert(createDeck(rows, cols)[i][j] == '?');
        }
    }
    rows = 13;
    cols = 4;
    //Test all characters in array are ? for the preset hidden board
    for (int i =0; i< rows; i++){
        for (int j=0; j<cols;j++){
            assert(createDeck(rows, cols)[i][j] == '?');
        }
    }
}

void testSetCards(){
    int rows;
    int cols;
    rows = 5;
    cols = 6;
    //creates deck filled with ?
    char** deck;
    deck = createDeck(rows,cols);
    deck = setCards(deck,rows,cols);
    for (int i =0; i< rows; i++){
        for (int j=0; j<cols;j++){
            assert(deck[i][j]!= '?');
        }
    }
    freeDeck(deck,rows,cols);
    rows = 4;
    cols = 4;
    deck = createDeck(rows,cols);
    setCards(deck,rows, cols);
    for (int i =0; i< rows; i++){
        for (int j=0; j<cols;j++){
            assert(deck[i][j] != '?');
        }
    }
    freeDeck(deck,rows,cols);
    
    rows = 5;
    cols = 6;
    int countcharA = 0;
    int countcharB = 0;
    int countcharC = 0;
    int countcharD = 0;
    int countcharE = 0;
    int countcharF = 0;
    int countcharG = 0;
    int countcharH = 0;
    int countcharI = 0;
    int countcharJ = 0;
    int countcharK = 0;
    int countcharL = 0;
    int countcharM = 0;
    int countcharN = 0;
    int countcharO = 0;

    char testcharA = 'a';
    char testcharB = 'b';
    char testcharC = 'c';
    char testcharD = 'd';
    char testcharE = 'e';
    char testcharF = 'f';
    char testcharG = 'g';
    char testcharH = 'h';
    char testcharI = 'i';
    char testcharJ = 'j';
    char testcharK = 'k';
    char testcharL = 'l';
    char testcharM = 'm';
    char testcharN = 'n';
    char testcharO = 'o';
    //creates deck filled with ?
    deck = createDeck(rows,cols);
    deck = setCards(deck,rows,cols);
    for (int i =0; i< rows; i++){
        for (int j=0; j<cols;j++){
            if (deck[i][j] == testcharA){
                countcharA+=1;
            }
            else if (deck[i][j] == testcharB){
                countcharB+=1;
            }
            else if (deck[i][j] == testcharC){
                countcharC+=1;
            }
            else if (deck[i][j] == testcharD){
                countcharD+=1;
            }
            else if (deck[i][j] == testcharE){
                countcharE+=1;
            }
            else if (deck[i][j] == testcharF){
                countcharF+=1;
            }
            else if (deck[i][j] == testcharG){
                countcharG+=1;
            }
            else if (deck[i][j] == testcharH){
                countcharH+=1;
            }
            else if (deck[i][j] == testcharI){
                countcharI+=1;
            }
            else if (deck[i][j] == testcharJ){
                countcharJ+=1;
            }
            else if (deck[i][j] == testcharK){
                countcharK+=1;
            }
            else if (deck[i][j] == testcharL){
                countcharL+=1;
            }
            else if (deck[i][j] == testcharM){
                countcharM+=1;
            }
            else if (deck[i][j] == testcharN){
                countcharN+=1;
            }
            else if (deck[i][j] == testcharO){
                countcharO+=1;
            }
        }
    }
    assert(countcharA == 2);
    assert(countcharB == 2);
    assert(countcharC == 2);
    assert(countcharD == 2);
    assert(countcharE == 2);
    assert(countcharF == 2);
    assert(countcharG == 2);
    assert(countcharH == 2);
    assert(countcharI == 2);
    assert(countcharJ == 2);
    assert(countcharK == 2);
    assert(countcharL == 2);
    assert(countcharM == 2);
    assert(countcharN == 2);
    assert(countcharO == 2);

}

void testCheckWinner(){
    int rows;
    int cols;
    int player1Score;
    int player2Score;
    rows = 5;
    cols = 6;
    char** deck;
    deck = createDeck(rows,cols);
    // Test if not all of the deck has been flipped returns 0
    assert(checkWinner(deck,rows,cols,&player1Score,&player2Score) == 0);
    freeDeck(deck, rows, cols);
    //Test if player1Score > player2Score after all cards are flipped returns 1
    player1Score = 2;
    player2Score = 1;
    deck = createDeck(rows,cols);
    deck = setCards(deck, rows, cols);
    assert(checkWinner(deck, rows, cols, &player1Score, &player2Score)==1);
    freeDeck(deck, rows, cols);
    //Test if player2Score > player1Score after all cards are flipped returns 2
    player1Score = 1;
    player2Score = 2;
    deck = createDeck(rows,cols);
    deck = setCards(deck, rows, cols);
    assert(checkWinner(deck, rows, cols, &player1Score, &player2Score)==2);
    freeDeck(deck, rows, cols);
    //Test if player1Score = player2Score after all cards are flipped returns 3
    player1Score = 2;
    player2Score = 2;
    deck = createDeck(rows,cols);
    deck = setCards(deck, rows, cols);
    assert(checkWinner(deck, rows, cols, &player1Score, &player2Score)==3);
    freeDeck(deck, rows, cols);

}