/** ternaryTree.h
 * ===========================================================
 * Name: Song Caleb
 * Section: M3
 * Project: PEX4
 * Purpose: Use a ternary tree hold a dictionary for a spell checker
 * ===========================================================
 */
#ifndef TERNARYTREE_H
#define TERNARYTREE_H

#include "wordList.h"
#include <stdbool.h>
// The definition of a node
typedef struct nodeStruct {
    char key;
    struct nodeStruct* left;
    struct nodeStruct* center;
    struct nodeStruct* right;
} TTreeNode;

/** printPreOrderTraversal()
 * @brief  prints to the console a preorder traversal of
 *           the ternary tree given (not required for gate check)
 * @param  root - pointer to root of a ternary tree
 * @pre    a ternary tree exists
 * @post   none
 */
void printPreOrderTraversal(TTreeNode* root);
/** collectWords()
 * @brief  - Collects words from file and puts it into a WordList
 * @param list - WordList
 * @param filename - file to take words from
 * @return - none
 */
void collectWords (WordList* list, char filename[100]);
/** treePrint()
 * @brief  - prints Insert order into tree
 * @param list - WordList
 * @param lBound - left bound of wordList
 * @param rBound - right bound of wordList
 * @return - none
 */
void treePrint (WordList* list, int lBound, int rBound);
/** createNode()
 * @brief  - initializes node
 * @param insertChar - character to insert into key value
 * @return - node
 */
TTreeNode* createNode(char insertChar);
/** insertWordLoop()
 * @brief  - Loop to insert words into tree
 * @param list - WordList
 * @param lBound - left bound of wordList
 * @param rBound - right bound of wordList
 * @param root - tree to insert words into
 * @return - tree with words inserted
 */
TTreeNode* insertWordLoop(WordList* list, int lBound, int rBound, TTreeNode* root);
/** insertWord()
 * @brief  - prints Insert word into tree
 * @param root - tree
 * @param word - word to insert
 * @return - tree with inserted word
 */
TTreeNode* insertWord(TTreeNode* root, char* word);
/** searchTree()
 * @brief  - searches tree for word
 * @param root - tree
 * @param searchWord - word to search for
 * @return - true if searchWord found, false if not
 */
bool searchTree(TTreeNode* root, char* searchWord);
/** spellChecker()
 * @brief  - spellChecks wordlist against dictionary in tree
 * @param root - tree
 * @param listToCheck - list to spellcheck
 * @return - none
 */
void spellChecker(TTreeNode* root, WordList* listToCheck);
/** deleteTree()
 * @brief  - deletes entire tree
 * @param root - tree to delete
 * @return - none
 */
void deleteTree(TTreeNode* root);
/** deleteNode()
 * @brief  - deletes node
 * @param root - node to delete
 * @return - none
 */
void deleteNode (TTreeNode* root);

#endif  // TERNARYTREE_H