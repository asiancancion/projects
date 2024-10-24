/** pex2test.h
 * =============================================================
 * Name: Caleb Song, 09/26/22
 * Section:  T6 Sample
 * Project:  PEX 2 - Blackjack
 * Purpose:  Declare functions to test functions in pex2functs.h
 * ============================================================= */
/** pex2test.h
 */
#ifndef PEX2TEST_H
#define PEX2TEST_H
/**
* @brief Runs all test functions
*/
void runAllTests();
/**
* @brief Tests to ensure getNextCard gets a value over or equal to 2, less than or equal to 11
*        and roughly accounts for the amount of 10s that should appear given 50 draws
*/
void testGetNextCard();
/**
* @brief Tests to ensure that getProbabilityOfCardOrLower returns the next value of greater than or equal to 11,
         equal to 10, less than 10 but greater than 1, less than or equal to 1
*/
void testGetProbabilityOfCardOrLower();
/**
* @brief Tests to ensure that getWinningPlayer returns a 1 if player1 wins, 2 if player2 wins, 3 if there is a tie,
*        or a 0 if both players bust
*/
void testGetWinningPlayer();
#endif // PEX2TEST_H