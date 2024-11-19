/** pex3test.h
 * =============================================================
 * Name: Caleb Song, 11/07/22
 * Section:  T6 Sample
 * Project:  PEX 3 - Automaton
 * Purpose:  Declare functions to test functions in pex3functs.h
 * ============================================================= */

/** pex3test.h
 */
#ifndef PEX2TEST_H
#define PEX2TEST_H
/**
* @brief Runs all test functions
*/
void runAllTests();
/**
* @brief tests CreateBoard sets the upper row middle value to filled and blanks the rests
*/
void testCreateBoard();
/**
* @brief tests copyBoard so that it correctly copies all parts of an original board
*/
void testCopyBoard();
/**
* @brief compares two boards and returns the amount of diffeerences
*/
void testCompareBoards();
/**
* @brief tests to ensure that the proper columns are filled out when updating board
*/
void testUpdateBoard();
#endif // PEX3TEST_H