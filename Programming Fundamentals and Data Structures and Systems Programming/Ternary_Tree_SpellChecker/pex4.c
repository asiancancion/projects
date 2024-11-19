/** pex4.c
 * ===========================================================
 * Name: Song Caleb
 * Section: M3
 * Project: PEX4
 * Purpose: Use a ternary tree hold a dictionary for a spell checker
 * Documentation: C3C Lefebreve helped me implement my deleteTree function by telling me to do it in a post-order traversal way.
 * ===========================================================
 */
#include "ternaryTree.h"
#include "unitTest.h"
#include "wordList.h"
#include <stdio.h>
#include <string.h>

//change to 1 to run unit tests
#define TEST 0


int main(int argc, char *argv[]) {
    if (TEST) {
        runAllTests();
        return 0;
    }
    else{
        //1st argument: dictionary
        //2nd argument: file to spellCheck
        char dictionary [100];
        char filename [100];

        //colects user inputed command line arguments and stores in char array
        strcpy(dictionary, argv[1]);
        strcpy(filename,argv[2]);

        //list of words to spellcheck
        WordList* list = NULL;
        list = wordListCreate();

        //list of words in dictionary to spellcheck against
        WordList* dictionaryList = NULL;
        dictionaryList = wordListCreate();

        //Put words from files into list and dictionaryList
        collectWords(list,filename);
        collectWords(dictionaryList,dictionary);

        // treePrint(list,0,wordListSize(list)-1);

        //create tree
        TTreeNode* root = NULL;

        //Insert words into root
        root = insertWordLoop(dictionaryList,0,wordListSize(dictionaryList)-1,root);

        // Print preorder traversal
        

        //spellChecker function call
        spellChecker(root, list);

        // printPreOrderTraversal(root);
        // printf("\n");

        //delete TTree
        deleteTree(root);

        //printPreOrderTraversal(root);

        return 0;
    }

    
}