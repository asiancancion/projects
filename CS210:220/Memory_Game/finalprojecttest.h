/** finalprojecttest.h
 * =============================================================
 * Name: Caleb Song, 12/01/22
 * Section:  T6 Sample
 * Project:  Final Project - Memory
 * Purpose:  Declare functions to test functions in finalprojectsfuncts.h
 * ============================================================= */

/** finalprojecttest.h
 */
#ifndef FINALPROJECTTEST_H
#define FINALPROJECTTEST_H
/**
* @brief Runs all test functions
*/
void runAllTests();
/**
* @brief tests CreateDeck
*/
void testCreateDeck();
/**
* @brief tests SetCards to ensure that no ? are still assigned, and there are pairs of cards
*/
void testSetCards();
/**
* @brief tests checkWinner so that it properly returns the correct values
*/
void testCheckWinner();
#endif // PEX3TEST_H