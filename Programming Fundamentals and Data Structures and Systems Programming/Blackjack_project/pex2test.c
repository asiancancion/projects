/** pex2test.c
 * =============================================================
 * Name: Caleb Song, 09/26/22
 * Section:  T6 Sample
 * Project:  PEX 2 - Blackjack
 * Purpose:  Test getNextCard, getProbabilityOfCardOrLower, and getWinningPlayer functions
 * ============================================================= */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "pex2test.h"
#include "pex2functs.h"
void runAllTests(){
    testGetNextCard();
    testGetProbabilityOfCardOrLower();
    testGetWinningPlayer();
    //If all functions pass tests, prints "all tests passed"
    printf("All tests passed!\n");
}

void testGetNextCard(){
    int counter;
    int card;
    counter = 0;
    //test card is greater than or equal to 2
    assert(getNextCard() >= 2);
    //test card is less than or equal to 11
    assert(getNextCard() <= 11);
    //Over 50 cards collects how many times a 10 appears
    for (int i=0; i<50; ++i){
        card = getNextCard();
        sleep(1);
        if (card == 10){
            counter+=1;
        }
    }
    /*A normal card should show up around 4 times in 50 draws, shows that 10 will show up
    more than a normal card*/
    if (counter > 8){
        printf("getNextCard function passed\n");
    }
    else{
        exit(1);
    }
}

void testGetProbabilityOfCardOrLower(){
    //tests probability if value of next card can be 11+
    assert(getProbabilityOfValueOrLower(11) == 100.0);
    //tests probability if value of next card is 10
    assert(round(getProbabilityOfValueOrLower(10)) == round((48.0/52.0)*100));
    //tests probability if value of next card is 1 or less 
    assert(round(getProbabilityOfValueOrLower(0)) == round(0.0));
    //tests probability if value of next card is between 2-9
    assert(round(getProbabilityOfValueOrLower(6)) == round(((5*4.0)/52.0)*100));
    printf("getProbabilityOfCardOrLower function passed\n");
}

void testGetWinningPlayer(){
    //tests if player1's score is greater than player2
    assert(getWinningPlayer(21, 10) == 1);
    //tests if player1 does not bust and player2 busts
    assert(getWinningPlayer(10, 23) == 1);
    //tests if player2's score is greater than player1
    assert(getWinningPlayer(10, 21) == 2);
    //tests if player2 does not bust and player1 busts
    assert(getWinningPlayer(23, 10) == 2);
    //tests if player1 ties with player2
    assert(getWinningPlayer(21, 21) == 3);
    //tests if players tie but both bust
    assert(getWinningPlayer(23, 23) == 0);
    //tests if both players bust
    assert(getWinningPlayer(24, 24) == 0);
    printf("getWinningPlayer function passed\n");
}