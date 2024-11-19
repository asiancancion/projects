/** unitTest.c
 * ===========================================================
 * Name: Song Caleb
 * Section: M3
 * Project: PEX4
 * Purpose: Unit tests for balanced tree insertion, tree insertion, spell check, and pre-order traversal
 * ===========================================================
 */
#include "unitTest.h"
#include "ternaryTree.h"
#include "wordList.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

/** unitTest1()
 * @brief  testing Balanced Tree Insertion
 */
void unitTest1() {
    //Manually check to see if passed in console
    printf("TEST 1: Balanced Tree Insertion\n");


    printf("Testing Insert order into ternary tree with test_dict2.txt first\n");
    printf("Contents of test_dict2.txt: \n");


    WordList* list = NULL;
    list = wordListCreate();
    char filename[100];
    strcpy(filename,"test_dict2.txt");
    collectWords(list,filename);
    wordListPrint(list);
    printf("\n");
    printf("Insert Order:\n");
    treePrint(list,0,wordListSize(list)-1);
    printf("\n");


    printf("Testing Insert order into ternary tree with test_dict1.txt second\n");
    printf("Contents of test_dict1.txt: \n");

    WordList* list2 = NULL;
    list2 = wordListCreate();
    char filename2[100];
    strcpy(filename2,"test_dict1.txt");
    collectWords(list2,filename2);
    wordListPrint(list2);
    printf("\n");
    printf("Insert Order:\n");
    treePrint(list2,0,wordListSize(list2)-1);

    printf("TEST 1: Balanced Tree Insertion PASSED\n");
    printf("\n");
}
/** unitTest2()
 * @brief  testing Tree Insertion
 */
void unitTest2() {
    printf("TEST 2: Testing Tree Insertion\n");

    char dictionary [100];

    //Testing tree insertion using test_dict2.txt
    strcpy(dictionary, "test_dict2.txt");

    WordList* dictionaryList = NULL;
    dictionaryList = wordListCreate();


    collectWords(dictionaryList,dictionary);

    TTreeNode* root = NULL;

    //Prints contents of test_dict2.txt to terminal
    printf("Contents of test_dict2.txt: \n");
    wordListPrint(dictionaryList);
    printf("\n");

    printf("Inserting contents into tree and testing each key value:\n");
    root = insertWordLoop(dictionaryList,0,wordListSize(dictionaryList)-1,root);

    //Testing each node key to ensure the wordlist inserted correctly

    printf("Root Key: S\n");
    assert(root->key == 'S');
    printf("PASSED\n");

    printf("Root->center Key: U\n");
    assert(root->center->key == 'U');
    printf("PASSED\n");

    printf("Root->center->center Key: C\n");
    assert(root->center->center->key == 'C');
    printf("PASSED\n");

    printf("Root->center->center->center Key: C\n");
    assert(root->center->center->center->key == 'C');
    printf("PASSED\n");

    printf("Root->center->center->center->center Key: E\n");
    assert(root->center->center->center->center->key == 'E');
    printf("PASSED\n");

    printf("Root->center->center->center->center->center Key: S\n");
    assert(root->center->center->center->center->center->key == 'S');
    printf("PASSED\n");

    printf("Root->center->center->center->center->center->center Key: S\n");
    assert(root->center->center->center->center->center->center->key == 'S');
    printf("PASSED\n");

    printf("Root->center->center->center->center->center->center->center Key: \\0\n");
    assert(root->center->center->center->center->center->center->center->key == '\0');
    printf("PASSED\n");

    printf("Root->center->center->center->center->right Key: U\n");
    assert(root->center->center->center->center->right->key == 'U');
    printf("PASSED\n");

    printf("Root->center->center->center->center->right->center Key: M\n");
    assert(root->center->center->center->center->right->center->key == 'M');
    printf("PASSED\n");

    printf("Root->center->center->center->center->right->center->center Key: B\n");
    assert(root->center->center->center->center->right->center->center->key == 'B');
    printf("PASSED\n");

    printf("Root->center->center->center->center->right->center->center->center Key: \\0\n");
    assert(root->center->center->center->center->right->center->center->center->key == '\0');
    printf("PASSED\n");

    printf("Root->center->center->center->center->center->left Key: E\n");
    assert(root->center->center->center->center->center->left->key == 'E');
    printf("PASSED\n");

    printf("Root->center->center->center->center->center->left->center Key: D\n");
    assert(root->center->center->center->center->center->left->center->key == 'D');
    printf("PASSED\n");

    printf("Root->center->center->center->center->center->left->center->center Key: \\0\n");
    assert(root->center->center->center->center->center->left->center->center->key == '\0');
    printf("PASSED\n");

    printf("TEST 2: Testing Tree Insertion PASSED\n");
    printf("\n");
}
/** unitTest3()
 * @brief  testing Spell Check
 */
void unitTest3() {
    printf("TEST 3: Testing Spell Check\n");
    //1st argument: dictionary
    //2nd argument: file to spellCheck
    char dictionary [100];
    char filename [100];

    //Testing test_dict1.txt dictionary against test.txt file to check
    strcpy(dictionary, "test_dict1.txt");
    strcpy(filename,"test.txt");

    WordList* list = NULL;
    list = wordListCreate();


    WordList* dictionaryList = NULL;
    dictionaryList = wordListCreate();


    collectWords(list,filename);
    collectWords(dictionaryList,dictionary);

    printf("\n");
    printf("Dictionary words: \n");
    wordListPrint(dictionaryList);
    printf("List of words to check: \n");
    wordListPrint(list);
    printf("\n");


    TTreeNode* root = NULL;

    root = insertWordLoop(dictionaryList,0,wordListSize(dictionaryList)-1,root);

    //spellChecker function call
    printf("Testing spellChecker full list:\n");
    printf("Should print: \nCAB Spelled Correctly\nCAD Spelled Correctly\nCAR Spelled Correctly\nCAT Spelled Correctly\ndog Spelled Incorrectly\ncat Spelled Correctly\n");
    printf("\n");
    spellChecker(root, list);

    printf("\n");
    //Testing each individual word after the Spell Checker
    printf("Now testing each individual word returns true or false if spelled correctly or incorrectly: \n");
    printf("Test CAB: true\n");
    assert(searchTree(root,wordListGet(list,0)) == true);
    printf("Test CAB: true PASSED\n");

    printf("Test CAD: true\n");
    assert(searchTree(root,wordListGet(list,1)) == true);
    printf("Test CAD: true PASSED\n");

    printf("Test CAR: true\n");
    assert(searchTree(root,wordListGet(list,2)) == true);
    printf("Test CAR: true PASSED\n");

    printf("Test CAT: true\n");
    assert(searchTree(root,wordListGet(list,3)) == true);
    printf("Test CAT: true PASSED\n");

    printf("Test dog: false\n");
    assert(searchTree(root,wordListGet(list,4)) == false);
    printf("Test dog: false PASSED\n");

    printf("Test cat: true\n");
    assert(searchTree(root,wordListGet(list,5)) == true);
    printf("Test cat: true PASSED\n");

    printf("TEST 3: Testing Spell Check PASSED\n");
    printf("\n");
}
/** unitTest4()
 * @brief  testing Pre-Order Traversal
 */
void unitTest4() {
    //Manually check in terminal
    printf("TEST 4: Testing Pre-order Traversal\n");

    char dictionary [100];

    strcpy(dictionary, "test_dict1.txt");

    WordList* dictionaryList = NULL;
    dictionaryList = wordListCreate();

    collectWords(dictionaryList,dictionary);

    TTreeNode* root = NULL;

    root = insertWordLoop(dictionaryList,0,wordListSize(dictionaryList)-1,root);


    printf("Should print: ");
    printf("C A T D B \\0 \\0 R \\0 \\0 O T P \\0 \\0 W \\0 U T \\0\n");
    printf("Actual print: ");
    printPreOrderTraversal(root);

    char filename [100];
    
    strcpy(filename, "test_dict2.txt");

    WordList* list = NULL;
    list = wordListCreate();

    collectWords(list,filename);

    TTreeNode* root2 = NULL;

    root2 = insertWordLoop(list,0,wordListSize(list)-1,root2);

    printf("\n");
    printf("Should print: ");
    printf("S U C C E S E D \\0 S \\0 U M B \\0\n");
    printf("Actual print: ");
    printPreOrderTraversal(root2);

    printf("\n");
    printf("TEST 4: Testing Pre-order Traversal PASSED\n");
    return;
}
/** runAllTests()
 * @brief  runs all tests
 */
int runAllTests() {
    unitTest1();
    unitTest2();
    unitTest3();
    unitTest4();
    printf("All Tests passed :D\n");

    return 0;
}
