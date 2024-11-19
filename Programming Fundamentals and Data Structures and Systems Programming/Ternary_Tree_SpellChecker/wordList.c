/** wordList.c
 * ===========================================================
 * Name: CS220
 * Section: N/A
 * Project: PEX4
 * Purpose: Create and manipulate a list of words.
 * ===========================================================
 */
#include "wordList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stripNewline(char *word) {
    char *newLine;
    // if a newline or return exists in the string replace it 
    // with a \0
    if ((newLine = strchr(word, '\n')) != NULL) {
        *newLine = '\0';
    }
    if ((newLine = strchr(word, '\r')) != NULL) {
        *newLine = '\0';
    }
}

WordList *wordListCreate() {
    // malloc space for an initialize values for
    // WordList
    WordList *list = malloc(sizeof(WordList));
    list->curIndex = -1;
    list->words = malloc(INITSIZE * sizeof(char *));
    return list;
}

char *wordListGet(WordList *listOfWords, int index) {
    // validate that listofwords isn't empty and index is in bounds
    if (listOfWords != NULL && index <= listOfWords->curIndex && index >= 0) {
        return listOfWords->words[index];
    }
    return NULL;
}

int wordListSize(WordList *listOfWords) {
    if (listOfWords == NULL) {
        return 0;
    }
    return listOfWords->curIndex + 1;
}

void wordListDelete(WordList *listOfWords) {
    // if empty return as nothing to free
    if (listOfWords == NULL) {
        return;
    }
    // free all words in the list
    for (int i = 0; i < wordListSize(listOfWords); i++) {
        free(listOfWords->words[i]);
    }
    // free array of pointers to words and then the WordList
    free(listOfWords->words);
    free(listOfWords);
}

int wordListAdd(WordList *listOfWords, char *word) {
    // if empty return 0 (false) failure
    if (listOfWords == NULL) {
        return 0;
    }
    static int newSize = INITSIZE;  // static vars retain value after funct terminates
    listOfWords->curIndex++;
    listOfWords->words[listOfWords->curIndex] = strdup(word);
    // after adding the word to the list check to see if we have run of of memory
    // if so, double the size of our current allocation using realloc (copies old to new
    // block of memory)
    if (listOfWords->curIndex + 1 >= newSize) {
        newSize = newSize * 2;
        listOfWords->words = realloc(listOfWords->words, newSize * sizeof(char *));
        if (listOfWords->words == NULL) {
            printf("Realloc failed try a larger INITSIZE\n");
        } else {
            //printf("Reallocated new size is %d\n", newSize);
        }
    }
    return 1;  // insert successful return 1 (true)
}

WordList *wordListCombine(WordList *dest, WordList *source) {
    // ensure there are two lists to merge
    if (dest == NULL || source == NULL) {
        return NULL;
    }
    
    // allocate a new list that is the combined size of dest, source
    WordList *newList = malloc(((dest->curIndex + 1) + (source->curIndex + 1)) * sizeof(char *));
    newList->curIndex = 0;
    int newSize = (dest->curIndex + 1) + (source->curIndex + 1);
    newList->words = malloc(newSize * sizeof(char *));
    
    // merge the lists copying the alphabetically first word into the merged list
    int sIndex = 0;
    int dIndex = 0;
    int i = 0;
    while (dIndex <= dest->curIndex && sIndex <= source->curIndex) {
        if (strcmp(dest->words[dIndex], source->words[sIndex]) <= 0) {
            newList->words[i] = strdup(dest->words[dIndex]);
            dIndex++;
        } else {
            newList->words[i] = strdup(source->words[sIndex]);
            sIndex++;
        }
        i++;
    }

    // if one list is empty copy the rest of the list into the new merged list
    while (dIndex <= dest->curIndex) {
        newList->words[i] = strdup(dest->words[dIndex]);
        dIndex++;
        i++;
    }
    // if one list is empty copy the rest of the list into the new merged list
    while (sIndex <= source->curIndex) {
        newList->words[i] = strdup(source->words[sIndex]);
        sIndex++;
        i++;
    }

    newList->curIndex = newSize - 1;
    return newList;
}

void wordListPrint(WordList *listOfWords) {
    if (listOfWords == NULL) {
        return;
    }
    for (int i = 0; i < wordListSize(listOfWords); i++) {
        printf("wordList[%d] = \"%s\"\n", i, listOfWords->words[i]);
    }
}