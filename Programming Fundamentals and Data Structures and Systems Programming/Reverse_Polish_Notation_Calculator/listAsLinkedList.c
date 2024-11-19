/** listAsLinkedList.c
 * ===========================================================
 * Name: Caleb Song
 * Section: M3 De Freitas
 * Project: PEX 3 - RPN Calculator
 * Purpose: List ADT as linked list
 * ===========================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "listAsLinkedList.h"

/** createNumberNode()
 * @brief  - Creates a number Node with a double type and value
 * @param  theNumber - double value to be stored in Node
 * @return - ptr to Node
 */
Node* createNumberNode(double theNumber){
    Node* newNode = (Node*)malloc(sizeof(newNode));

    //set values in node
    newNode->next = NULL;
    newNode->type = REAL_NUMBER;

    newNode->data = (double*)malloc(sizeof(double));
    *(double*)newNode->data = theNumber;
    //return the node
    return newNode;
}

/** createOperatorNode()
 * @brief  - Creates a Operator Node with a char type and value
 * @param  theOperator - char value to be stored in Node
 * @return - ptr to Node
 */
Node* createOperatorNode(char theOperator){
    Node* newNode = (Node*)malloc(sizeof(newNode));

    //set values in node
    newNode->next = NULL;
    newNode->type = MATH_OPERATOR;

    newNode->data = (char*)malloc(sizeof(char));
    *(char*)newNode->data = theOperator;
    //return the node
    return newNode;
    
}

/** linkedListInit()
 * @brief  - initializes the linked list structure
 * @return - pointer to linked list
 */
LinkedList* linkedListInit() {
    // Creates the List
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
  
    // Initializes the Values
    list->head = NULL;
    list->tail = NULL;
    list->numberOfItems = 0;
    return list;
}

/** deleteLinkedList(()
 * @brief  - deletes linked list and nodes, freeing all memory used
 * @param list - a ptr to the linked list structure
 */
void deleteLinkedList(LinkedList* list) {
    Node* tmp;
    //Goes through list and frees memory deleting list
    while(list->head != NULL){
        tmp = list->head;
        list->head = list->head->next;
        free(tmp);
    }
    list->numberOfItems = 0;
}

/** appendElementLinkedList()
 * @brief - addes a new node to the end of the linked list
 * @param list - a ptr to the linked list structure
 * @param newNode - a ptr to a Node to append to the list
 */
void appendElementLinkedList(LinkedList* list, Node* newNode) {
    newNode->next = NULL;
    //Appending to empty list
    if (list->numberOfItems == 0){
        list->head = newNode;
    }
    //Appending to end of list with data in it
    else{
        list->tail->next = newNode;
    }
    list->tail = newNode;
    list->numberOfItems++;
}

/** lengthOfLinkedList()
 * @brief  - returns the size of the linked list
 * @param list - a ptr to the linked structure
 * @return - number of items in the linked list
 */
int lengthOfLinkedList(LinkedList* list) {
    return list->numberOfItems;
}

/** printLinkedList()
 * @brief  - outputs the linked list to the console
 * @param list - the linked list structure
 */
void printLinkedList(LinkedList* list) {
    // Create a temp pointer that points at the head
    Node* currentNode = list->head;
    // Add some print statements so that we can see something
    // even if the list is empty
    // Iterate through all list elements and print out the values
    while (currentNode != NULL) {
        //prints a char the operator +,-,/,* etc. if it is a MATH_OPERATOR type
        if (currentNode->type == MATH_OPERATOR){
            printf("%c -> ", *(char*)currentNode->data);
        }
        //prints a double if it is a REAL_NUMBER type with 3 decimal places
        else if (currentNode->type == REAL_NUMBER){
            printf("%.3lf -> ", *(double*)currentNode->data);
        }
        currentNode = currentNode->next;
    }
    //prints NULL to end of list
    printf("NULL\n");
}

/** getElementLinkedList()
 * @brief  - Retrieves node at a given position
 * @param  list - a ptr to the linked list structure
 * @param  position - index of value requested
 * @return - ptr to Node at 'position', NULL if given an invalid position
 */
Node* getElementLinkedList(LinkedList* list, int position) {
    Node* currentNode;
    int currentposition = 0;
    currentNode = list->head;
    //Goes through list to try to find position if in range
    while(currentposition!=position && currentNode!=NULL){
        currentNode = currentNode->next;
        currentposition++;
    }
    //If not in range returns NULL
    if (position > currentposition){
        return NULL;
    }
    return currentNode;
}

/** deleteElementLinkedList()
 * @brief  - Deletes (i.e., frees) node at a given position.  Function will print an error message
 *           if given an invalid position.
 * @param  list - a ptr to the linked list structure
 * @param  position - index of value to delete
 */
void deleteElementLinkedList(LinkedList* list, int position) {
    Node* currentNode;
    int currentposition = 0;
    currentNode = list->head;
    //Deletes Node at position 0, sets head to heads next
    if (list->numberOfItems == 1){
        list->head = NULL;
        list->tail = NULL;
        list->numberOfItems--;
    }
    else if (position == 0){
        list->head = currentNode->next;
        free(currentNode);
        list->numberOfItems--;
    }
    //Deletes Node at end of list, sets tail to previous node
    else if (position == lengthOfLinkedList(list)-1){
        while(currentposition!=position-1){
            currentNode = currentNode->next;
            currentposition++;
        }
        list->tail = currentNode;
        list->tail->next = NULL;
        currentNode = currentNode->next;
        free(currentNode);
        list->numberOfItems--;
    }
    //Deletes Node in middle of list
    else if (position > 0  && position < lengthOfLinkedList(list)) {
        Node* tmp = list->head;
        // Find the node just before the position we want to insert
        for (int i=0; i<position-1; i++) {
            tmp = tmp->next;
        }
        // Inserts the node in the middle
        currentNode = tmp;
        tmp=tmp->next;
        currentNode->next = tmp->next;
        free(tmp);
        list->numberOfItems--;
    }
    //Prints error message if Node to delete is not in range
    else{
        printf("Error invalid position\n");
    }
}

/** insertElementLinkedList()
 * @brief  - Inserts a node at a given position.  Function should print an error message
 *           if given an invalid position.
 * @param  list - a ptr to the linked list structure
 * @param  position - index of node to add
 * @param  newNode - ptr to Node to be added
 */
void insertElementLinkedList(LinkedList* list, int position, Node* newNode) {
    newNode->next = NULL;
    if (position < 0){
        printf("Error invalid position\n");
    }
    else if (lengthOfLinkedList(list) == 0) {
        // CASE 1:  Adding to an empty list
        list->head = newNode;
        list->tail = newNode;
        list->numberOfItems++;
    }
    else if (position == 0) {
        // CASE 2:  Adding to the front
        newNode->next = list->head;
        list->head = newNode;
        list->numberOfItems++;
    }
    else if (position == lengthOfLinkedList(list)) {
        // CASE 3:  Adding to the end (i.e., appending)
        list->tail->next = newNode;
        list->tail = newNode;
        list->numberOfItems++;
    }
    else if (position > 0  && position < lengthOfLinkedList(list)) {
        // CASE 4:  Adding in the middle
        Node* tmp = list->head;
        // Find the node just before the position we want to insert
        for (int i=0; i<position-1; i++) {
            tmp = tmp->next;
        }
        // Inserts the node in the middle
        newNode->next = tmp->next;
        tmp->next = newNode;
        list->numberOfItems++;
    }
    //prints error if position to insert is out of range
    else{
        printf("Error invalid position\n");
    }
}

/** changeElementLinkedList()
 * @brief  - Replaces the node at a given position.  Function will print an error message
 *           if given an invalid position.
 * @param  list - a ptr to the linked list structure
 * @param  position - index of node to replace
 * @param  newNode - replacment Node
 */
void changeElementLinkedList(LinkedList* list, int position, Node* newNode) {
    Node* currentNode;
    int currentposition = 0;
    currentNode = list->head;
    //Changes element at position 0
    if (position == 0){
        newNode->next = list->head->next;
        list->head=newNode;
    }
    //Changes element at end of list
    else if (position == lengthOfLinkedList(list)-1){
        while(currentposition!=position-1){
            currentNode = currentNode->next;
            currentposition++;
        }
        currentNode->next = newNode;
        list->tail = newNode;
    }
    //Changes element in middle of list
    else if (position > 0  && position < lengthOfLinkedList(list)) {
        Node* tmp = list->head;

        for (int i=0; i<position-1; i++) {
            tmp = tmp->next;
        }
        newNode->next = tmp->next->next;
        tmp->next = newNode;
    }
    //Prints error if element to change out of range
    else{
        printf("Error invalid position\n");
    }
}

/** copyElement()
 * @brief  - helper function, returns a copy of a node
 * @param  nodeToClone - a ptr to the Node to be copied
 * @returns another Node with the exact same data and type; pointer set to NULL
 */
Node* copyElement(Node* nodeToClone) {
    Node* newNode = NULL;
    //Copies a REAL_NUMBER (double) Node
    if (nodeToClone->type == REAL_NUMBER){
        newNode = createNumberNode(*(double*)nodeToClone->data);
    }
    //Copies a MATH_OPERATOR (char) Node
    else if (nodeToClone->type == MATH_OPERATOR){
        newNode = createOperatorNode(*(char*)nodeToClone->data);
    }
    return newNode;
}
