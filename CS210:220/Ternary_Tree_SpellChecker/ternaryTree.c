/** ternaryTree.c
 * ===========================================================
 * Name: Song Caleb
 * Section: M3
 * Project: PEX4
 * Purpose: Use a ternary tree hold a dictionary for a spell checker
 * ===========================================================
 */
#include "ternaryTree.h"
#include "wordList.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


/** printPreOrderTraversal()
 * @brief  prints to the console a preorder traversal of
 *           the ternary tree given (not required for gate check)
 * @param  root - pointer to root of a ternary tree
 * @pre    a ternary tree exists
 * @post   none
 */
void printPreOrderTraversal(TTreeNode* root) {
    if (root == NULL){
        //do nothing
    }
    else{
        //manually print \0 char if it is \0 character because it just prints a blank space if you do not
        if (root->key == '\0'){
            printf("\\0 ");
        }
        else{
            printf("%c ", root->key);
        }
        printPreOrderTraversal(root->left);
        printPreOrderTraversal(root->center);
        printPreOrderTraversal(root->right);
    }
}
/** collectWords()
 * @brief  - Collects words from file and puts it into a WordList
 * @param list - WordList
 * @param filename - file to take words from
 * @return - none
 */
void collectWords(WordList* list, char filename[100]){
    char line [100];
    FILE* file = fopen(filename, "r");
    do{
        //Copy line from file
        fgets(line,100,file);
        //strip \n character
        stripNewline(line);
        //add to list
        wordListAdd(list,line);
    }
    while(!feof(file));
}
/** treePrint()
 * @brief  - prints Insert order into tree
 * @param list - WordList
 * @param lBound - left bound of wordList
 * @param rBound - right bound of wordList
 * @return - none
 */
void treePrint (WordList* list, int lBound, int rBound){
    if (lBound > rBound){
        return;
    }
    else{
        int middle = (lBound+rBound)/2;
        printf("Insert: %s\n",wordListGet(list,middle));
        treePrint(list,lBound,middle-1);
        treePrint(list,middle+1,rBound);
    }
}
/** createNode()
 * @brief  - initializes node
 * @param insertChar - character to insert into key value
 * @return - node
 */
TTreeNode* createNode(char insertChar){
    TTreeNode* node = (TTreeNode*)malloc(sizeof(TTreeNode));
    node->center = NULL;
    node->left = NULL;
    node->right = NULL;
    node->key = insertChar;
    return node;
}
/** insertWordLoop()
 * @brief  - Loop to insert words into tree
 * @param list - WordList
 * @param lBound - left bound of wordList
 * @param rBound - right bound of wordList
 * @param root - tree to insert words into
 * @return - tree with words inserted
 */
TTreeNode* insertWordLoop(WordList* list, int lBound, int rBound, TTreeNode* root){
    if (lBound > rBound){
        return root;
    }
    else{
        //inserts into tree in balanced way
        int middle = (lBound+rBound)/2;
        root = insertWord(root, wordListGet(list,middle));
        insertWordLoop(list,lBound,middle-1, root);
        insertWordLoop(list,middle+1,rBound, root);
    }
    return root;
}
/** insertWord()
 * @brief  - prints Insert word into tree
 * @param root - tree
 * @param word - word to insert
 * @return - tree with inserted word
 */
TTreeNode* insertWord(TTreeNode* root, char* word){
    //uppercases the letter if it is lowercase
    char letter = toupper(word[0]);
    //when root is NULL then creates the node at that place in memory
    if (root == NULL){
        root = createNode(letter);
    }
    //Less than goes to left side of root
    if (letter < root->key){
        root->left = insertWord(root->left, word);
    }
    //Greater than goes to right side of root
    else if (letter > root->key){
        root->right = insertWord(root->right, word);
    }
    else{
        //If the letter is \0 adds \0 node end of the word
        if (letter == '\0'){
            root = createNode('\0');
        }
        //If letter is the same go down the center
        else{
            root->center = insertWord(root->center, word+1);
        }
    }
    return root;

}
/** searchTree()
 * @brief  - searches tree for word
 * @param root - tree
 * @param searchWord - word to search for
 * @return - true if searchWord found, false if not
 */
bool searchTree(TTreeNode* root, char* searchWord){
    //capitalizes word that we are searching for
    char searchLetter = toupper(searchWord[0]);
    //If we end up where root == NULL then the word does not exist in the tree
    if(root == NULL){
        return false;
    }
    //If search letter is less than root->key then the letter should be to left of the tree
    if (searchLetter < root->key){
        return searchTree(root->left, searchWord);
    }
    //If search letter is greater than root->key then the letter should be to the left of the tree
    else if (searchLetter > root->key){
        return searchTree(root->right, searchWord);
    }
    //else we continue with the next letter or if the char is \0 we found the word
    else{
        if (searchLetter == '\0'){
            return true;
        }
        else{
            return searchTree(root->center, searchWord+1);
        }
    }
    return false;
}
/** spellChecker()
 * @brief  - spellChecks wordlist against dictionary in tree
 * @param root - tree
 * @param listToCheck - list to spellcheck
 * @return - none
 */
void spellChecker(TTreeNode* root, WordList* listToCheck){
    int length = wordListSize(listToCheck);
    char* wordToCheck;
    for (int i =0; i<length; i++){
        wordToCheck = wordListGet(listToCheck,i);
        //searchTree returns True spelled correctly
        if (searchTree(root,wordToCheck)){
            printf("%s Spelled Correctly\n", wordToCheck);
        }
        //search Tree returns False spelled incorrectly
        else{
            printf("%s Spelled Incorrectly\n", wordToCheck);
        }
    }
}
/** deleteNode()
 * @brief  - deletes node
 * @param root - node to delete
 * @return - none
 */
void deleteNode (TTreeNode* root){
    root->center = NULL;
    root->right = NULL;
    root->left = NULL;
    free(root);
}
/** deleteTree()
 * @brief  - deletes entire tree
 * @param root - tree to delete
 * @return - none
 */
void deleteTree(TTreeNode* root){
    if (root == NULL){
        //do nothing
    }
    if (root->left != NULL){
        deleteTree(root->left);
    }
    if (root->center != NULL){
        deleteTree(root->center);
    }
    if (root->right != NULL){
        deleteTree(root->right);
    }
    deleteNode(root);
}