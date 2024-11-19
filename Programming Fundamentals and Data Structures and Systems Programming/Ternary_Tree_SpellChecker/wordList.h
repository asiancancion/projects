/** wordList.h
 * ===========================================================
 * Name: CS220
 * Section: N/A
 * Project: PEX4
 * Purpose: Create and manipulate a list of words.
 * ===========================================================
 */

#ifndef WORDLIST_H
#define WORDLIST_H

#define INITSIZE 200       // the initial size of a WordList
#define MAXSTRINGLENGTH 25  // max length of a word

// Defines the type for a WordList
typedef struct wordListStruct {
    int curIndex;   // the index of the last word in the list
    char **words;   // pointer to list of pointers to words
} WordList;

/**
 * @brief strips newline or carrage return from a string
 * @param word - a pointer to the string that is to be stripped
 */
void stripNewline(char *word);

/**
 * @brief creates a WordList
 * @return a pointer to the initialized empty WordList
 */
WordList *wordListCreate();

/**
 * @brief deallocates a WordList and any words added
 * @param listOfWords - an initialized WordList
 */
void wordListDelete(WordList *words);

/**
 * @brief adds a word to the end of a WordList
 * @param listOfWords - an initialized WordList
 * @param word - the word to add to the list
 * @return true if the word was added, false otherwise
 */
int wordListAdd(WordList *listOfWords, char *word);

/**
 * @brief returns the word at the index value
 * @param listOfWords - a WordList pointer
 * @param index - the index value of the word to retrieve
 * @return the word that was retrieved, or NULL if no such index exists
 */
char *wordListGet(WordList *listOfWords, int index);

/**
 * @brief Combines two wordlists together by copying the source WordList
 *        into the destination WordList, the combined WordList will be
 *        in sorted order
 * @param dest - a WordList pointer
 * @param source - a WordList pointer
 * @return the combined Wordlist
 */
WordList *wordListCombine(WordList *dest, WordList *source);

/**
 * @brief provides the number of words in the WordList
 * @param listOfWords - a WordList pointer
 * @return the number of words in the WordList, or 0 if words is empty
 */
int wordListSize(WordList *listOfWords);

/**
 * @brief prints a WordList
 * @param listOfWords - a WordList pointer
 */
void wordListPrint(WordList *listOfWords);

#endif  // WORDLIST_H