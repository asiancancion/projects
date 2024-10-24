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
#include "pex0functs.h"

int main(int argc, char* argv[]){
    char filename [100];
    char row[100];
    char col[100];
    char sentence[80];
    char sentence2[80];
    //colects user inputed command line arguments and stores in char arrays
    strcpy(filename, argv[1]);
    strcpy(row, argv[2]);
    strcpy(col, argv[3]);

    //parseIt() implementation 
    printf("Enter a sentence: ");
    fgets(sentence, 80, stdin);
    parseIt(sentence);
    printf("New Sentence: %s", sentence);

    //modifyIt() implementation
    printf("Enter a second sentence: ");
    fgets(sentence2, 80, stdin);
    strcpy(sentence2,modifyIt(sentence2));
    printf("New String: %s\n", sentence2);
    
    //getInfo() implementation stores name and age in student1 struct
    StudentRecType student1;
    getInfo(&student1);
    printf("Name: %s", student1.name);
    printf(" Age: %d\n", student1.age);

    //fillIt() implementation fills int array with numbers from 0 to 100
    int numRows;
    int numCols;
    //converts command line argument from char array to int
    numRows = atoi(argv[2]);
    numCols = atoi(argv[3]);
    int** array = NULL;
    //dynamically allocating memory for 2d array
    array = (int**) malloc(numRows* sizeof(int*));
    for (int i = 0; i < numRows; i++){
        array[i] = (int*) malloc(numCols * sizeof(int));
    }
    fillIt(array, numRows,numCols);

    //dumpIt() implementation - dumps array into filename.txt
    dumpIt(array,numRows,numCols,filename);


    printf("Time to complete: 45 mins");

    return 0;
}