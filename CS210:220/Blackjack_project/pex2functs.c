/** pex2functs.c
 * =============================================================
 * Name: Caleb Song, 09/26/22
 * Section:  T6 Sample
 * Project:  PEX 2 - Blackjack
 * Purpose:  getNextCard to get next card on a hit or start of game, getProbabilityOfCardOrLower for probability of desired value, 
 *           getWinningPlayer to determine who wins, getCharSafe to get safe character input, displayGameState to show current game,
 *           playBlackjack to play game for each player, playGame to play blackjack vs testing functions 
 * ============================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>
#include <ctype.h>
char getCharSafe(){
    char value;
    int scanfReturn=0;

    //attempt to read a character value
    scanfReturn = scanf(" %c", &value);
    fflush(stdin);
    //quit if scanfReturn is not a character
    if(isalpha(scanfReturn) != 0){
        fprintf(stderr, "Bad char input - terminating\n");
        exit(1);
    }
    return value;
}

int getNextCard(){
    srand(time(0));
    int nextcard;
    //obtain values from 2 to 14 to simulate probability of drawing a 10
    nextcard = rand()%14+2;
    //To ensure the probability of getting a 10 is simulated, values of 12-14 an 11 will also be considered a 10
    if (nextcard>11){
        nextcard = 10;
    }
    return nextcard;
}

double getProbabilityOfValueOrLower(int desiredValue){
    double probability;
    //if potential value is >11 always be a 100% probability of not busting
    if (desiredValue >= 11){
        probability = 100.0;
    }
    //Probability of getting a 10
    else if (desiredValue == 10){
        probability = 48.0/52.0 * 100;
    }
    //Probability of getting 1 or less is 0%
    else if (desiredValue < 1){
        probability = 0.0;
    }
    //Probability of getting number from 2->9
    else{
        probability = ((4.0*(desiredValue-1))/52.0) * 100;
    }
    return probability;
}

void displayGameState(char* player1Name, int player1Score){
    int highestCard;
    double probability;
    //highestCard possible will be 21-playerscore
    highestCard = 21 - player1Score;
    probability = getProbabilityOfValueOrLower(highestCard);
    printf("%s your current total is %d\n", player1Name, player1Score);
    printf("You need a %d or lower to keep playing\n", highestCard);
    printf("The probability of you recieving a %d or lower is %.2lf%%\n", highestCard, probability);

}

int getWinningPlayer(int player1Score, int player2Score){
    //Returns 1 if player1 has higher card value or if player2 busts
    if ((player1Score > player2Score && player1Score <=21) || (player1Score <= 21 && player2Score > 21)){
        return 1;
    }
    //Returns 2 if player2 has higher card value or if player1 busts
    else if ((player2Score > player1Score && player2Score <=21) || (player2Score <= 21 && player1Score > 21)){
        return 2;
    }
    //Returns 3 if both players equal and don't bust
    else if (player1Score == player2Score && player1Score <= 21 && player2Score <= 21){
        return 3;
    }
    //Returns 0 if both players bust
    else{
        return 0;
    }
}

int playBlackjack(char* playerName){
    int card;
    int total;
    char action;
    total = 0;
    action = 'h';
    printf("\n");
    printf("Player Turn: %s\n", playerName);
    card = getNextCard();
    printf("CARD: %d\n", card);
    total += card;
    //Until player stands keep hitting
    while (action == 'h'){
        card = getNextCard();
        //If total = 11 and next card is 11 then will redraw so that total will never start over 21
        while (total == 11 && card == 11){
            card = getNextCard();
        }
        printf("CARD: %d\n", card);
        total += card;
        //if total is greater than 11 at any point will print Bust! and break from the loop
        if (total > 21){
            printf("Bust! \n");
            break;
        }
        //if total is equal to 21 then will print Blackjack! and will break from the loop
        else if (total == 21){
            printf("Blackjack!\n");
            break;
        }
        else{
            displayGameState(playerName, total);
            printf("Do you want to hit (h) or stay (s)?\n");
            action = getCharSafe();
            printf("\n");
        }
        
    }
    return total;
}

void playGame(){
    char player1Name[50];
    char player2Name[50];
    int player1Score;
    int player2Score;
    int winner;
    printf("Welcome to BlackJack\n");
    printf("Please Enter Player's Name: ");
    scanf("%s", player1Name);
    printf("Please Enter Dealer's Name: ");
    scanf("%s", player2Name);
    player1Score = playBlackjack(player1Name);
    player2Score = playBlackjack(player2Name);
    winner = getWinningPlayer(player1Score, player2Score);
    if (winner == 1){
        printf("%s won!\n", player1Name);
    }
    else if (winner == 2){
        printf("%s won!\n", player2Name);
    }
    else if (winner == 3){
        printf("It's a tie!\n");
    }
    else{
        printf("Both players bust\n");
    }
}