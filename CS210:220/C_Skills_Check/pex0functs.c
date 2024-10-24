/** pex0.c
 * =============================================================
 * Name: Caleb Song, 01/09/23
 * Section:  M3 Lt Col de Freitas
 * Project:  PEX 0 - Skills Check
 * Purpose:  Initial skills check of CS 210 skills
 * Documentation Statement: No outside help was recieved
 * ============================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "pex0functs.h"
/**
* @brief Replaces spaces with - and t with spaces
* @param string sentence that will be edited
* @pre string must be a char array
* @post string changes after parseIt is called
*/
void parseIt(char string[80]){
    int length;
    length = strlen(string);
    for (int i = 0; i < length; i++){
        //replaces with - if character in array is a space
        if (string[i] == ' '){
            string[i] = '-';
        }
        //replaces with a space if character in array is a lowercase or uppercase t
        else if (string[i] == 't' || string[i] == 'T'){
            string[i] = ' ';
        }
    }
}
/**
* @brief prepends "start->" and appends "<-end"
* @param string sentence that will have "start->" and "<-end" prepended and appended
* @pre string must be a char array
* @post string changes after modifyIt is called
*/
char* modifyIt(char string[80]){
    char* newString;
    int length;
    length = strlen(string);
    //allocates memory for extra 12 characters in "start->" and "<-end" to the original length of the character array
    length += 12;
    newString = (char*)malloc(length * sizeof(char));
    //copies "start-> into string"
    strcpy(newString, "start->");
    strcat(newString,string);
    strcat(newString,"<-end");
    return newString;
}
/**
* @brief Collects data and stores it into struct
* @param student is struct that will have information stored in
* @pre student must be a pointer to a struct
* @post values inside student struct changes after getInfo is called
*/
void getInfo(StudentRecType* student){
    printf("Please input name: ");
    fgets(student->name, 64, stdin);
    printf("Please input age: ");
    scanf("%d",&student->age);
}
/**
* @brief Fills array with numbers from 1 to 100
* @param array is 2d array that has memory dynamically allocated
* @param numRows is number of Rows array will have
* @param numCols is number of Cols array will have
* @pre numRows and numCols must be ints
* @post array will have values of 1 to 100 stored in it
*/
void fillIt(int** array, int numRows, int numCols){
    //srand called once to randomize
    srand(time(NULL));
    for(int i =0; i<numRows;i++){
        for(int j = 0; j<numCols;j++){
            //1 is added to rand number as rand() % 100 collects numbers from 0 to 99
            array[i][j] = 1 + (rand() % 100);
        }
    }
}
/**
* @brief "dumps" array of numbers into file
* @param array is 2d array that has memory dynamically allocated filled with values from 1 to 100
* @param numRows is number of Rows array will have
* @param numCols is number of Cols array will have
* @param filename is name of file that values of array will be dumped into
* @pre numRows and numCols must be ints, array must be filled with integers from 1 to 100, filename must be a char array
* @post No variables will change, a txt file will be created with stored values
*/
void dumpIt(int** array, int numRows, int numCols, char filename[100]){
    FILE* file = fopen(filename,"w");
    for(int i =0; i<numRows;i++){
        for(int j = 0; j<numCols;j++){
            //for formatting purposes if it is a 3 digit number then the number is separated by one space
            if (array[i][j] == 100){
                fprintf(file,"%d ", array[i][j]);
            }
            //for formatting purposes if it is a 2 digit number then the number has one space in front to align with 3 digit numbers
            else if(array[i][j] > 9){
                fprintf(file," %d ", array[i][j]);
            }
            //for formatting purposes if it is a 1 digit number then the number has two spaces in front to align with 2+ digit numbers
            else{
                fprintf(file,"  %d ", array[i][j]);
            }
        }
        //prints new line after each row
        fprintf(file,"\n");
    }
}