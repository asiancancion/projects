# Ternary Tree Spell Checker

## Name: Caleb Song  
**Section**: M3  
**Project**: PEX 4 - Ternary Tree Spell Checker  
**Purpose**:  
The purpose of this project is to implement a **ternary tree** to hold a dictionary for a spell checker. The ternary tree structure is efficient for storing and searching words, making it ideal for dictionary-based spell checking.

## Overview
This program takes two input files:
1. **Dictionary file**: A file containing a list of correct words.
2. **File to spell check**: A file containing words to be checked against the dictionary.

The program builds a ternary tree from the dictionary and uses it to perform a spell check on the second file, identifying any words that are not found in the dictionary.

## Program Workflow
1. The program reads the dictionary and the file to be spell-checked.
2. The words from both files are stored in two separate word lists.
3. A ternary search tree is constructed from the dictionary words.
4. The words from the file to be checked are searched in the ternary tree, and any misspelled words are identified.
5. The ternary tree is deleted from memory after the spell check is complete.

## Code Explanation

### `main()`

The main() function handles user input, builds the ternary tree, and runs the spell checker.

```c
int main(int argc, char *argv[]) {
    if (TEST) {
        runAllTests();
        return 0;
    } else {
        // 1st argument: dictionary
        // 2nd argument: file to spell check
        char dictionary[100];
        char filename[100];

        // Collect user-inputted command-line arguments
        strcpy(dictionary, argv[1]);
        strcpy(filename, argv[2]);

        // List of words to spell check
        WordList* list = wordListCreate();

        // List of words in the dictionary
        WordList* dictionaryList = wordListCreate();

        // Populate word lists from files
        collectWords(list, filename);
        collectWords(dictionaryList, dictionary);

        // Create the ternary tree and insert words from the dictionary
        TTreeNode* root = NULL;
        root = insertWordLoop(dictionaryList, 0, wordListSize(dictionaryList) - 1, root);

        // Perform spell check
        spellChecker(root, list);

        // Delete the ternary tree
        deleteTree(root);

        return 0;
    }
}

```

### `printPreOrderTraversal()`

This function performs a pre-order traversal of the ternary tree and prints the characters. If the key is \0, it prints \\0 to represent the null character.

```c
void printPreOrderTraversal(TTreeNode* root) {
    if (root == NULL) {
        // Do nothing
    } else {
        if (root->key == '\0') {
            printf("\\0 ");
        } else {
            printf("%c ", root->key);
        }
        printPreOrderTraversal(root->left);
        printPreOrderTraversal(root->center);
        printPreOrderTraversal(root->right);
    }
}
```

### `collectWords()`

This function reads words from a file and stores them in a WordList.


```c
void collectWords(WordList* list, char filename[100]) {
    char line[100];
    FILE* file = fopen(filename, "r");
    do {
        fgets(line, 100, file); // Read line from file
        stripNewline(line);     // Remove newline character
        wordListAdd(list, line); // Add word to list
    } while (!feof(file));
}
```

### `treePrint()`
This function prints the order in which words are inserted into the ternary tree from a word list.

```c
void treePrint(WordList* list, int lBound, int rBound) {
    if (lBound > rBound) {
        return;
    } else {
        int middle = (lBound + rBound) / 2;
        printf("Insert: %s\n", wordListGet(list, middle));
        treePrint(list, lBound, middle - 1);
        treePrint(list, middle + 1, rBound);
    }
}

```

### `createNode()`
This function creates a new TTreeNode with a given character key and returns the pointer to the node.


```c
TTreeNode* createNode(char insertChar) {
    TTreeNode* node = (TTreeNode*)malloc(sizeof(TTreeNode));
    node->center = NULL;
    node->left = NULL;
    node->right = NULL;
    node->key = insertChar;
    return node;
}

```

### `insertWordLoop()`
This function recursively inserts words into the ternary tree in a balanced manner.


```c
TTreeNode* insertWordLoop(WordList* list, int lBound, int rBound, TTreeNode* root) {
    if (lBound > rBound) {
        return root;
    } else {
        int middle = (lBound + rBound) / 2;
        root = insertWord(root, wordListGet(list, middle));
        insertWordLoop(list, lBound, middle - 1, root);
        insertWordLoop(list, middle + 1, rBound, root);
    }
    return root;
}

```

### `insertWord()`
This function inserts a word into the ternary tree. The function uppercases letters for consistency and places the word's characters into the tree.


```c
TTreeNode* insertWord(TTreeNode* root, char* word) {
    char letter = toupper(word[0]);
    if (root == NULL) {
        root = createNode(letter);
    }
    if (letter < root->key) {
        root->left = insertWord(root->left, word);
    } else if (letter > root->key) {
        root->right = insertWord(root->right, word);
    } else {
        if (letter == '\0') {
            root = createNode('\0');
        } else {
            root->center = insertWord(root->center, word + 1);
        }
    }
    return root;
}

```

### `searchTree()`
This function searches for a word in the ternary tree. It returns true if the word is found, and false otherwise.


```c
bool searchTree(TTreeNode* root, char* searchWord) {
    char searchLetter = toupper(searchWord[0]);
    if (root == NULL) {
        return false;
    }
    if (searchLetter < root->key) {
        return searchTree(root->left, searchWord);
    } else if (searchLetter > root->key) {
        return searchTree(root->right, searchWord);
    } else {
        if (searchLetter == '\0') {
            return true;
        } else {
            return searchTree(root->center, searchWord + 1);
        }
    }
    return false;
}

```

### `spellChecker()`
This function checks each word in the provided word list against the ternary tree (which contains the dictionary). If a word is found in the tree, it is considered spelled correctly; otherwise, it is misspelled.



```c
void spellChecker(TTreeNode* root, WordList* listToCheck) {
    int length = wordListSize(listToCheck);
    char* wordToCheck;
    for (int i = 0; i < length; i++) {
        wordToCheck = wordListGet(listToCheck, i);
        if (searchTree(root, wordToCheck)) {
            printf("%s Spelled Correctly\n", wordToCheck);
        } else {
            printf("%s Spelled Incorrectly\n", wordToCheck);
        }
    }
}
```

### `deleteNode()` and `deleteTree()`

These functions handle memory management by deleting individual nodes and the entire ternary tree using post-order traversal.


```c
void deleteNode(TTreeNode* root) {
    root->center = NULL;
    root->right = NULL;
    root->left = NULL;
    free(root);
}

void deleteTree(TTreeNode* root) {
    if (root == NULL) {
        // Do nothing
    }
    if (root->left != NULL) {
        deleteTree(root->left);
    }
    if (root->center != NULL) {
        deleteTree(root->center);
    }
    if (root->right != NULL) {
        deleteTree(root->right);
    }
    deleteNode(root);
}

```


