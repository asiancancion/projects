/** pex0functs.h
 * =============================================================
 * Name: Caleb Song, 01/09/23
 * Section:  M3 Lt Col de Freitas
 * Project:  PEX 0 - Skills Check
 * Purpose:  Initial skills check of CS 210 skills
 * Documentation Statement: No outside help was recieved
 * ============================================================= */

#ifndef PEX0FUNCTS_H
#define PEX0FUNCTS_H
typedef struct StudentRecType_struct{
    char name[64];
    int age;
}StudentRecType;
/**
* @brief Replaces spaces with - and t with spaces
* @param string sentence that will be edited
* @pre string must be a char array
* @post string changes after parseIt is called
*/
void parseIt(char string[80]);
/**
* @brief prepends "start->" and appends "<-end"
* @param string sentence that will have "start->" and "<-end" prepended and appended
* @pre string must be a char array
* @post string changes after modifyIt is called
*/
char* modifyIt(char string[80]);
/**
* @brief Collects data and stores it into struct
* @param student is struct that will have information stored in
* @pre student must be a pointer to a struct
* @post values inside student struct changes after getInfo is called
*/
void getInfo(StudentRecType* student);
/**
* @brief Fills array with numbers from 1 to 100
* @param array is 2d array that has memory dynamically allocated
* @param numRows is number of Rows array will have
* @param numCols is number of Cols array will have
* @pre numRows and numCols must be ints
* @post array will have values of 1 to 100 stored in it
*/
void fillIt(int** array, int numRows, int numCols);
/**
* @brief "dumps" array of numbers into file
* @param array is 2d array that has memory dynamically allocated filled with values from 1 to 100
* @param numRows is number of Rows array will have
* @param numCols is number of Cols array will have
* @param filename is name of file that values of array will be dumped into
* @pre numRows and numCols must be ints, array must be filled with integers from 1 to 100, filename must be a char array
* @post No variables will change, a txt file will be created with stored values
*/
void dumpIt(int** array, int numRows, int numCols, char filename[100]);
#endif // PEX0FUNCTS_H