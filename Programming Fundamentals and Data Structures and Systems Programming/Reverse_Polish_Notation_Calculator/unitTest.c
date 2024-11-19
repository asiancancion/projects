
// /** unitTest.c
//  * ===========================================================
//  * Name: Caleb Song
//  * Section: M3 De Freitas
//  * Project: PEX3 - RPN Calculator
//  * Purpose: unitTests
//  * ===========================================================
//  */
// #include <math.h>
// #include "unitTest.h"
// #include <stdio.h>

// /** unitTest1()
//  * @brief  - Test appendElementLinkedList()
//  */
// void unitTest1() {
//     // Create a linked list (not tested in this example)
//     LinkedList* list;
//     list = linkedListInit();

//     //  Here is a quick example of how to test append
//     //  to an empty list

//     // allocate node to insert and append it to list
//     Node* nodePtr = (Node*)malloc(sizeof(Node));
//     nodePtr->next = NULL;

//     // allocate an nodePtr's data
//     nodePtr->data = malloc(sizeof(double));  // data must be allocated
//                                              // dynamically (w/malloc())
//     *((double*)nodePtr->data) = 7.0;         // set value

//     // set the data type using an enumeration (REAL_NUMBER or MATH_OPERATOR, see listAsLinkedList.h)
//     nodePtr->type = REAL_NUMBER;

//     appendElementLinkedList(list, nodePtr);  // append new node

//     // get Node at postion 0
//     Node* itemReturned = getElementLinkedList(list, 0);

//     // The item return type is correct?
//     assert(itemReturned->type == REAL_NUMBER);

//     // Does the node contain the item appended?
//     assert(*((double*)itemReturned->data) == 7.0);

//     // A safer way to do ==
//     #define EPSILON 0.0005
//     assert(fabs((*(double*)itemReturned->data) - 7.0) <= EPSILON);

//     // Are there 1 items in the list?
//     assert(list->numberOfItems == 1);

//     // Create more tests with asserts to test other aspects of the append
//     // and get element


//     //append number to end of list with data in it
//     //create Node
//     Node* newNode = createNumberNode(5.0);

//     //append newNode to list of size 1
//     assert(list->numberOfItems == 1);
//     appendElementLinkedList(list,newNode);

//     //get Node at position 1 (last element of list)
//     Node* returnNode = getElementLinkedList(list,1);

//     // The item return type is correct?
//     assert(returnNode->type == REAL_NUMBER);

//     // Does the node contain the item appended?
//     assert(*((double*)returnNode->data) == 5.0);

//     // Are there 2 items in the list?
//     assert(list->numberOfItems == 2);


//     //Append operator to empty list
//     LinkedList* list2;
//     list2 = linkedListInit();
//     Node* newNodeOp = createOperatorNode('+');

//     //append newNodeOp to list of size 0
//     assert(list2->numberOfItems == 0);
//     appendElementLinkedList(list2,newNodeOp);

//     //get Node at position 0
//     returnNode = getElementLinkedList(list2,0);

//     // The item return type is correct?
//     assert(returnNode->type == MATH_OPERATOR);

//     // Does the node contain the item appended?
//     assert(*((char*)returnNode->data) == '+');

//     // Are there 1 items in the list?
//     assert(list2->numberOfItems == 1);

//     //Append operator to end of list with data in it
//     newNodeOp = createOperatorNode('*');
//     //append newNodeOp to list of size 1
//     assert(list2->numberOfItems == 1);
//     appendElementLinkedList(list2,newNodeOp);

//     //get Node at position 1
//     returnNode = getElementLinkedList(list2,1);

//     // The item return type is correct?
//     assert(returnNode->type == MATH_OPERATOR);

//     // Does the node contain the item appended?
//     assert(*((char*)returnNode->data) == '*');

//     // Are there 2 items in the list?
//     assert(list2->numberOfItems == 2);
// }

// /** unitTest2()
//  * @brief  - Test createNumberNode() and createOperatorNode()
//  */
// void unitTest2() {
//     //createNumberNode
//     Node* nodePtr = (Node*)malloc(sizeof(Node));
//     nodePtr->next = NULL;

//     // allocate an nodePtr's data
//     nodePtr->data = malloc(sizeof(double));  // data must be allocated
//                                              // dynamically (w/malloc())
//     *((double*)nodePtr->data) = 7.0;         // set value

//     // set the data type using an enumeration (REAL_NUMBER or MATH_OPERATOR, see listAsLinkedList.h)
//     nodePtr->type = REAL_NUMBER;

//     //Test createNumberNode
//     Node* testNode = createNumberNode(7.0);

//     //test value
//     assert(*((double*)testNode->data) == *((double*)nodePtr->data));

//     //test type
//     assert(testNode->type == nodePtr->type);


//     //Test createOperatorNode
//     Node* nodePtr2 = (Node*)malloc(sizeof(Node));
//     nodePtr2->next = NULL;

//     // allocate an nodePtr's data
//     nodePtr2->data = malloc(sizeof(char));  // data must be allocated
//                                              // dynamically (w/malloc())
//     *((char*)nodePtr2->data) = '+';         // set value

//     // set the data type using an enumeration (REAL_NUMBER or MATH_OPERATOR, see listAsLinkedList.h)
//     nodePtr2->type = MATH_OPERATOR;

//     Node* testNode2 = createOperatorNode('+');

//     //test value
//     assert(*((char*)testNode2->data) == *((char*)nodePtr2->data));

//     //test type
//     assert(testNode2->type == nodePtr2->type);
// }

// /** unitTest3()
//  * @brief  - Test linkedListInit()
//  */
// void unitTest3(){

//     LinkedList* testList = linkedListInit();

//     //test head points to NULL
//     assert(testList->head == NULL);

//     //test tail points to NULL
//     assert(testList->tail == NULL);

//     //test number of elements is 0
//     assert(testList->numberOfItems == 0);

// }

// /** unitTest4()
//  * @brief  - Test lengthOfLinkedList()
//  */
// void unitTest4(){
//     LinkedList* testList = linkedListInit();

//     //Append list of size 3 and test lengthOfLinkedList() at each append
//     assert(lengthOfLinkedList(testList) == 0);

//     Node* newNode = createNumberNode(0.0);
//     appendElementLinkedList(testList,newNode);
//     assert(lengthOfLinkedList(testList) == 1);

//     newNode = createOperatorNode('+');
//     appendElementLinkedList(testList,newNode);
//     assert(lengthOfLinkedList(testList) == 2);

//     newNode = createNumberNode(2.0);
//     appendElementLinkedList(testList,newNode);
//     assert(lengthOfLinkedList(testList) == 3);

// }

// /** unitTest5()
//  * @brief  - Test printLinkedList()
//  */
// void unitTest5(){
//     LinkedList* testList = linkedListInit();

//     //Append list of size 3 and print at each stage

//     //Nothing in List
//     printf("Print should state: NULL\n");
//     printLinkedList(testList);

//     //0.0 in list
//     Node* newNode = createNumberNode(0.0);
//     appendElementLinkedList(testList,newNode);
//     printf("Print should state: 0.000 -> NULL\n");
//     printLinkedList(testList);

//     //0.0 and + in list
//     newNode = createOperatorNode('+');
//     appendElementLinkedList(testList,newNode);
//     printf("Print should state: 0.000 -> + -> NULL\n");
//     printLinkedList(testList);

//     //0.0 + and 2.00 in list
//     newNode = createNumberNode(2.0);
//     appendElementLinkedList(testList,newNode);
//     printf("Print should state: 0.000 -> + -> 2.000 -> NULL\n");
//     printLinkedList(testList);
// }

// /** unitTest6()
//  * @brief  - Test getElementLinkedList()
//  */
// void unitTest6(){
//     LinkedList* testList = linkedListInit();

//     //Append list of size 3
//     Node* newNode = createNumberNode(0.0);
//     appendElementLinkedList(testList,newNode);
//     newNode = createOperatorNode('+');
//     appendElementLinkedList(testList,newNode);
//     newNode = createNumberNode(2.0);
//     appendElementLinkedList(testList,newNode);

//     // get numberNode at postion 0
//     Node* itemReturned = getElementLinkedList(testList, 0);

//     // The item return type is correct?
//     assert(itemReturned->type == REAL_NUMBER);

//     //Correct value?
//     assert(*((double*)itemReturned->data) == 0.0);


//     // get operatorNode at postion 1
//     itemReturned = getElementLinkedList(testList, 1);

//     // The item return type is correct?
//     assert(itemReturned->type == MATH_OPERATOR);

//     //Correct value?
//     assert(*((char*)itemReturned->data) == '+');


//     // get numberNode at postion 2
//     itemReturned = getElementLinkedList(testList, 2);

//     // The item return type is correct?
//     assert(itemReturned->type == REAL_NUMBER);

//     //Correct value?
//     assert(*((double*)itemReturned->data) == 2.0);

//     // get Node at position 5, -1, and -10 (node out of bounds) should return NULL
//     assert(getElementLinkedList(testList,5) == NULL);
//     assert(getElementLinkedList(testList,-1) == NULL);
//     assert(getElementLinkedList(testList,-10) == NULL);
    
// }

// /** unitTest7()
//  * @brief  - Test insertElementLinkedList()
//  */
// void unitTest7(){
//     LinkedList* testList = linkedListInit();
//     LinkedList* testList2 = linkedListInit();

//     //insert number to empty list at position 0
//     Node* newNode = createNumberNode(0.0);
//     insertElementLinkedList(testList, 0, newNode);
//     Node* itemReturned = getElementLinkedList(testList, 0);
//     // The item return type is correct?
//     assert(itemReturned->type == REAL_NUMBER);
//     //Correct value?
//     assert(*((double*)itemReturned->data) == 0.0);

//     //insert operator to empty list at position 0
//     newNode = createOperatorNode('+');
//     insertElementLinkedList(testList2, 0, newNode);
//     itemReturned = getElementLinkedList(testList2, 0);
//     // The item return type is correct?
//     assert(itemReturned->type == MATH_OPERATOR);
//     //Correct value?
//     assert(*((char*)itemReturned->data) == '+');

    
//     //insert operator at end of list position 1
//     newNode = createOperatorNode('+');
//     insertElementLinkedList(testList, 1, newNode);
//     itemReturned = getElementLinkedList(testList, 1);
//     // The item return type is correct?
//     assert(itemReturned->type == MATH_OPERATOR);
//     //Correct value?
//     assert(*((char*)itemReturned->data) == '+');

//     //insert number at end of list position 1
//     newNode = createNumberNode(1.0);
//     insertElementLinkedList(testList2, 1, newNode);
//     itemReturned = getElementLinkedList(testList2, 1);
//     // The item return type is correct?
//     assert(itemReturned->type == REAL_NUMBER);
//     //Correct value?
//     assert(*((double*)itemReturned->data) == 1.0);


//     //insert number at middle of list position 1
//     newNode = createNumberNode(2.0);
//     insertElementLinkedList(testList, 1, newNode);
//     itemReturned = getElementLinkedList(testList, 1);
//     // The item return type is correct?
//     assert(itemReturned->type == REAL_NUMBER);
//     //Correct value?
//     assert(*((double*)itemReturned->data) == 2.0);

//     //insert operator at middle of list position 1
//     newNode = createOperatorNode('+');
//     insertElementLinkedList(testList2, 1, newNode);
//     itemReturned = getElementLinkedList(testList2, 1);
//     // The item return type is correct?
//     assert(itemReturned->type == MATH_OPERATOR);
//     //Correct value?
//     assert(*((char*)itemReturned->data) == '+');

//     //Testing out of range error message
//     printf("\n");
//     printf("Inserting at position out of range should print: Error invalid position\n");
//     insertElementLinkedList(testList, 10, newNode);
    
// }

// /** unitTest8()
//  * @brief  - Test changeElementLinkedList()
//  */
// void unitTest8(){
//     LinkedList* testList = linkedListInit();

//     //Append list of size 3
//     Node* newNode = createNumberNode(0.0);
//     appendElementLinkedList(testList,newNode);
//     newNode = createOperatorNode('+');
//     appendElementLinkedList(testList,newNode);
//     newNode = createNumberNode(2.0);
//     appendElementLinkedList(testList,newNode);

//     //Change operator at position 0
//     //test list at position 0 before
//     Node* itemReturned = getElementLinkedList(testList, 0);
//     assert(*((double*)itemReturned->data) == 0.0);
//     assert(itemReturned->type == REAL_NUMBER);
//     newNode = createOperatorNode('-');
//     changeElementLinkedList(testList,0,newNode);
//     //test list at position 0 after changing
//     itemReturned = getElementLinkedList(testList, 0);
//     assert(*((char*)itemReturned->data) == '-');
//     assert(itemReturned->type == MATH_OPERATOR);

//     //Change number at position 0
//     //test list at position 0 before
//     itemReturned = getElementLinkedList(testList, 0);
//     assert(*((char*)itemReturned->data) == '-');
//     assert(itemReturned->type == MATH_OPERATOR);
//     newNode = createNumberNode(2.0);
//     changeElementLinkedList(testList,0,newNode);
//     //test list at position 0 after changing
//     itemReturned = getElementLinkedList(testList, 0);
//     assert(*((double*)itemReturned->data) == 2.0);
//     assert(itemReturned->type == REAL_NUMBER);

//     //Change operator at position 1 to test changing element in middle of list
//     //test list at position 1 before
//     itemReturned = getElementLinkedList(testList, 1);
//     assert(*((char*)itemReturned->data) == '+');
//     assert(itemReturned->type == MATH_OPERATOR);
//     newNode = createOperatorNode('*');
//     changeElementLinkedList(testList,1,newNode);
//     //test list at position 0 after changing
//     itemReturned = getElementLinkedList(testList, 1);
//     assert(*((char*)itemReturned->data) == '*');
//     assert(itemReturned->type == MATH_OPERATOR);

//     //Change number at position 1 to test changing element in middle of list
//     //test list at position 1 before
//     itemReturned = getElementLinkedList(testList, 1);
//     assert(*((char*)itemReturned->data) == '*');
//     assert(itemReturned->type == MATH_OPERATOR);
//     newNode = createNumberNode(5.0);
//     changeElementLinkedList(testList,1,newNode);
//     //test list at position 0 after changing
//     itemReturned = getElementLinkedList(testList, 1);
//     assert(*((double*)itemReturned->data) == 5.0);
//     assert(itemReturned->type == REAL_NUMBER);

//     //Change number at position 2 to test changing element at end of list
//     //test list at position 2 before
//     itemReturned = getElementLinkedList(testList, 2);
//     assert(*((double*)itemReturned->data) == 2.0);
//     assert(itemReturned->type == REAL_NUMBER);
//     newNode = createNumberNode(5.0);
//     changeElementLinkedList(testList,2,newNode);
//     //test list at position 2 after changing
//     itemReturned = getElementLinkedList(testList, 2);
//     assert(*((double*)itemReturned->data) == 5.0);
//     assert(itemReturned->type == REAL_NUMBER);

//     //Change operator at position 2 to test changing element at end of list
//     //test list at position 2 before
//     itemReturned = getElementLinkedList(testList, 2);
//     assert(*((double*)itemReturned->data) == 5.0);
//     assert(itemReturned->type == REAL_NUMBER);
//     newNode = createOperatorNode('/');
//     changeElementLinkedList(testList,2,newNode);
//     //test list at position 2 after changing
//     itemReturned = getElementLinkedList(testList, 2);
//     assert(*((char*)itemReturned->data) == '/');
//     assert(itemReturned->type == MATH_OPERATOR);

//     //Testing out of range error message
//     printf("\n");
//     printf("Changing at position out of range should print: Error invalid position\n");
//     changeElementLinkedList(testList, 10, newNode);

// }

// /** unitTest9()
//  * @brief  - Test copyElement()
//  */
// void unitTest9(){

//     //Copy numberNode
//     Node* newNode = createNumberNode(0.0);
//     Node* itemReturned = copyElement(newNode);
//     assert(*((double*)itemReturned->data) == 0.0);
//     assert(itemReturned->type == REAL_NUMBER);

//     //copy operatorNode
//     newNode = createOperatorNode('+');
//     itemReturned = copyElement(newNode);
//     assert(*((char*)itemReturned->data) == '+');
//     assert(itemReturned->type == MATH_OPERATOR);
// }
// /** runAllTests
//  * @brief  - Runs all tests
//  * @return - returns 0
//  */
// int runAllTests() {
//     unitTest1();
//     unitTest2();
//     unitTest3();
//     unitTest4();
//     unitTest5();
//     unitTest6();
//     unitTest7();
//     unitTest8();
//     unitTest9();

//     return 0;
// }


/** unitTest.c
 * ===========================================================
 * Name: Lt Col Adrian de Freitas
 * Section: CS220
 * Project: PEX3 Part 1 - RPN Calculator Test Cases
 * ===========================================================
 */

#include <stdio.h>
#include <string.h>
#include "unitTest.h"

// Helper function that creates a Node containing a double
Node* createARealNumberNode(double number) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    newNode->type = REAL_NUMBER;
    newNode->next = NULL;

    // Creates the Pointer to Hold the New Node
    newNode->data = (double*)malloc(sizeof(double));

    *((double*)newNode->data) = number;
    
    return newNode;
}

// Helper function that creates a Node containing a character (i.e. math operator)
Node* createAnOperatorNode(char operator) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    newNode->type = MATH_OPERATOR;
    newNode->next = NULL;

    // Creates the Pointer to Hold the New Node
    newNode->data = (char*)malloc(sizeof(char));

    *((char*)newNode->data) = operator;
    
    return newNode;
}

// Helper function that prints a linked list 
void printList(LinkedList* list) {
    Node* currentNode = list->head;

    // Adds some whitespace to make it line up with the tests
    printf("      LIST (size: %d): ", list->numberOfItems);

    while (currentNode != NULL) {
        if (currentNode->type == REAL_NUMBER) {
            double number = *((double*)currentNode->data);
            printf("%.3lf -> ", number);
        }
        else {
            char c = *((char*)currentNode->data);
            printf("%c -> ", c);
        }

        currentNode = currentNode->next;
    }

    printf("NULL\n");
}

// Helper function that inserts an element to a linked list
void addElementLinkedList(LinkedList* list, int position, Node* newNode) {
    if (position == 0 && list->numberOfItems == 0) {
        list->head = newNode;
        list->tail = newNode;
        list->numberOfItems++;
    }
    else if (position == 0) {
        newNode->next = list->head;
        list->head = newNode;
        list->numberOfItems++;
    }
    else if (position == list->numberOfItems) {
        list->tail->next = newNode;
        list->tail = newNode;
        list->numberOfItems++;
    }
    else if (position > 0 && position < list->numberOfItems) {
        Node* tmp = getElementLinkedList(list, position-1);
        newNode->next = tmp->next;
        tmp->next = newNode;
        list->numberOfItems++;
    }
}

// Helper function that creates a list containing numElements elements
LinkedList* createDummyLinkedList(int numElements) {
    LinkedList* list = malloc(sizeof(LinkedList));
    list->numberOfItems = 0;
    list->head = NULL;
    list->tail = NULL;

    for (int i=0; i<numElements; i++) {
        Node* newNode = createARealNumberNode(i);
        addElementLinkedList(list, i, newNode);
    }

    return list;
}

// Helper function that deletes/frees a linked list
void freeLinkedList(LinkedList* list) {
    Node* tmp = list->head;

    // Free each node in the list
    while (tmp != NULL) {
        Node* nodeToDelete = tmp;
        tmp = tmp->next;
        free(nodeToDelete->data);
        free(nodeToDelete);
    }

    // When all the nodes have been freed, then free the list
    free(list);
}

void unitTest1() {
    // Keeps track of penalties
    double pointsPossible = 0.75;
    double penalty = 0.0;

    printf("--------------------------------------------------------\n");
    printf("TEST 1:  linkedListInit (3 tests total - %.2f pts)\n", pointsPossible);
    printf("--------------------------------------------------------\n"); 

    LinkedList* list = linkedListInit();

    // Verifying that something was retuned
    if (list != NULL) {
        // Verifying that the number of items is correct
        if (list->numberOfItems == 0) {
            printf("    + (0.25) Successfully initialized List->numberOfItems to 0\n");
        }
        else {
            printf("    - (0.25) Incorrectly initialize List->numberOfItems to %d\n", list->numberOfItems);
            penalty += 0.25;
        } 

        // Verifying that the head is NULL
        if (list->head == NULL) {
            printf("    + (0.25) Successfully set List->head to NULL\n");
        }
        else {
            printf("    - (0.25) Incorrectly set List Head to a non-NULL value\n");
            penalty += 0.25;
        }

        // Verifying that the tail is NULL
        if (list->tail == NULL) {
            printf("    + (0.25) Successfully set List->tail to NULL\n");
        }
        else {
            printf("    - (0.25) Incorrectly set List Tail to a non-NULL value\n");
            penalty += 0.25;
        }
    }
    else {
        printf(" - Function returns a NULL pointer");
        penalty = pointsPossible;
    }
    
    printf("    SCORE: %0.2lf out of %0.2lf possible\n\n", (pointsPossible-penalty), pointsPossible);

    // Frees the Final Linked List
    freeLinkedList(list);
}

void unitTest2() {
    // Keeps track of penalties
    double pointsPossible = 1.5;
    double penalty = 0.0;

    printf("--------------------------------------------------------\n");
    printf("TEST 2:  insertElementLinkedList (6 tests total - %.2f pts)\n", pointsPossible);
    printf("--------------------------------------------------------\n");

    LinkedList* list = createDummyLinkedList(0);
    
    // Adding the first node to a list
    Node* newNode = createARealNumberNode(1.0);
    insertElementLinkedList(list, 0, newNode);
    if (list->numberOfItems == 1 && list->head == newNode && list->tail == newNode) {
        printf("    + (0.25) Successfully inserted the first node (position 0)\n");
    }
    else {
        printf("    - (0.25) First node was not added successfully (position 0)\n");    
        penalty += 0.25;    
    }

    // Inserting to the Beginning
    freeLinkedList(list);
    list = createDummyLinkedList(1);
    newNode = createARealNumberNode(0.0);
    insertElementLinkedList(list, 0, newNode);

    if (list->numberOfItems == 2 && list->head == newNode && list->tail != newNode) {
        printf("    + (0.25) Successfully inserted a node to the beginning (position 0)\n");
    }
    else {
        printf("    - (0.25) Failed to insert a node in the beginning (position 0)\n");   
        printList(list);
        penalty += 0.25;     
    }

    // Inserting to the End
    freeLinkedList(list);
    list = createDummyLinkedList(2);
    newNode = createARealNumberNode(2.0);
    insertElementLinkedList(list, 2, newNode);

    if (list->numberOfItems == 3 && list->tail == newNode) {
        printf("    + (0.25) Successfully inserted a node to the end (position=length)\n");
    }
    else {
        printf("    - (0.25) Failed to insert a node in the end (position=length)\n");   
        printList(list);     
        penalty += 0.25;
    }

    // Inserting to the Middle
    freeLinkedList(list);
    list = createDummyLinkedList(3);
    newNode = createARealNumberNode(1.5);
    insertElementLinkedList(list, 1, newNode);

    if (list->numberOfItems == 4 && list->head->next == newNode) {
        printf("    + (0.25) Successfully inserted a node to the middle (position=1)\n");
    }
    else {
        printf("    - (0.25) Failed to insert a node to the middle (position=1)\n");   
        printList(list);     
        penalty += 0.25;
    }

    // Inserting at an invalid location (positive)
    list = createDummyLinkedList(5);
    newNode = createARealNumberNode(666.0);
    insertElementLinkedList(list, 10000, newNode);

    if (list->numberOfItems == 5) {
        printf("    + (0.25) Successfully refused to add a node with a really big index (position=10000)\n");
    }
    else {
        printf("    - (0.25) Failed to not add a node when the index is really big (position=10000)\n");   
        printList(list);  
        penalty += 0.25;   
    }

    // Inserting at an invalid location (negative)
    freeLinkedList(list);
    list = createDummyLinkedList(0);
    newNode = createARealNumberNode(-666.0);
    insertElementLinkedList(list, -10000, newNode);
    if (list->numberOfItems == 0) {
        printf("    + (0.25) Successfully refused to add a node with a really small index (position=-10000) TO AN EMPTY LIST\n");
    }
    else {
        printf("    - (0.25) Failed to not add a node when the index is really small (position=-10000) TO AN EMPTY LIST\n");   
        printList(list);    
        penalty += 0.25;  
    }

    printf("    SCORE: %0.2lf out of %0.2lf possible\n\n", (pointsPossible-penalty), pointsPossible);

    // Frees the Final Linked List
    freeLinkedList(list);
}

void unitTest3() {
    // Keeps track of penalties
    double pointsPossible = 0.75;
    double penalty = 0.0;

    printf("--------------------------------------------------------\n");
    printf("TEST 3:  appendElementLinkedList (2 tests total - %.2f pts)\n", pointsPossible);
    printf("--------------------------------------------------------\n");
    
    // Appending the first node to an empty list
    LinkedList* list = linkedListInit();
    Node* newNode = createARealNumberNode(1.0);
    appendElementLinkedList(list, newNode);

    if (list->numberOfItems == 1 && list->head == newNode && list->tail == newNode) {
        printf("    + (0.25) Successfully appended the first node\n");
    }
    else {
        printf("    - (0.25) First node was not appended successfully\n");   
        penalty += 0.25;     
    }

    // Appending a second node to a list
    freeLinkedList(list);
    list = createDummyLinkedList(1);
    newNode = createARealNumberNode(2.0);
    appendElementLinkedList(list, newNode);  

    if (list->numberOfItems == 2 && list->head != newNode && list->tail == newNode) {
        printf("    + (0.50) Successfully appended a second node\n");
    }
    else {
        printf("    - (0.50) Second node was not appended successfully\n");        
        penalty += 0.50;
    }

    printf("    SCORE: %0.2lf out of %0.2lf possible\n\n", (pointsPossible-penalty), pointsPossible);

    // Frees the Final Linked List
    freeLinkedList(list);
}

void unitTest4() {
    // Keeps track of penalties
    double pointsPossible = 0.5;
    double penalty = 0.0;

    printf("--------------------------------------------------------\n");
    printf("TEST 4:  lengthOfLinkedList (1 test total - %.2f pts)\n", pointsPossible);
    LinkedList* list = createDummyLinkedList(10);
    printList(list);
    printf("--------------------------------------------------------\n");

    // Verifies that the function and numberOfItems are both 10
    if (lengthOfLinkedList(list) == list->numberOfItems && lengthOfLinkedList(list) == 10) {
        printf("    + (0.50) function returns correct length (%d)\n", lengthOfLinkedList(list));
    }
    else {
        printf("    - (0.50) function returns incorrect length (%d)\n", lengthOfLinkedList(list));
        penalty += 0.50;
    }

    printf("    SCORE: %0.2lf out of %0.2lf possible\n\n", (pointsPossible-penalty), pointsPossible);
}

void unitTest5() {
    // Keeps track of penalties
    double pointsPossible = 1.5;
    double penalty = 0.0;

    printf("--------------------------------------------------------\n");
    printf("TEST 5:  getElementLinkedList (5 tests total - %.2f pts)\n", pointsPossible);
    
    LinkedList* list = createDummyLinkedList(5);

    printList(list);
    printf("--------------------------------------------------------\n");

    // Getting a node from the front of the list
    Node* node = getElementLinkedList(list, 0);
    if (node == list->head) {
        printf("    + (0.30) Successfully gets the head node (position 0)\n");
    }
    else if (node == NULL) {
        printf("    - (0.30) Returns NULL for position 0");
    }
    else {
        printf("    - (0.30) Returns incorrect element for position 0 (%lf instead of 0.0)\n", *((double*)node->data));
        printList(list);
        penalty += 0.30;
    }

    // Gettings a middle node (i.e., the second one)
    node = getElementLinkedList(list, 1);
    if (node == list->head->next) {
        printf("    + (0.30) Successfully gets a middle node (position 1)\n");
    }
    else if (node == NULL) {
        printf("    - (0.30) Returns NULL for a missle node (position 1)");
    }
    else {
        printf("    - (0.30) Returns incorrect element for position 1 (%lf instead of 1.0)\n", *((double*)node->data));
        printList(list);
        penalty += 0.30;
    }

    // Getting the last node
    node = getElementLinkedList(list, 4);
    if (node == list->tail) {
        printf("    + (0.30) Successfully gets the end node\n");
    }
    else if (node == NULL) {
        printf("    - (0.30) Returns NULL for the end node");
    }
    else {
        printf("    - (0.30) Returns incorrect element for position 4 (%lf instead of 4.0)\n", *((double*)node->data));
        printList(list);
        penalty += 0.30;
    }

    // Getting an invalid node (positive)
    node = getElementLinkedList(list, 10000);
    if (node == NULL) {
        printf("    + (0.30) Successfully returns NULL when given an invalid positive position\n");
    }
    else {
        printf("    - (0.30) Returns incorrect element for position 10000 (%lf instead of NULL)\n", *((double*)node->data));
        printList(list);
        penalty += 0.30;
    }

    // Getting an invalid node (negative)
    node = getElementLinkedList(list, -10000);
    if (node == NULL) {
        printf("    + (0.30) Successfully returns NULL when given an invalid negative position\n");
    }
    else {
        printf("    - (0.30) Returns incorrect element for position -10000 (%lf)\n", *((double*)node->data));
        printList(list);
        penalty += 0.30;
    }

    printf("    SCORE: %0.2lf out of %0.2lf possible\n\n", (pointsPossible-penalty), pointsPossible);

    // Frees the Final Linked List
    freeLinkedList(list);
}

void unitTest6() {
    // Keeps track of penalties
    double pointsPossible = 2.5;
    double penalty = 0.0;

    printf("--------------------------------------------------------\n");
    printf("TEST 6:  deleteElementLinkedList (5 tests total - %.2f pts)\n", pointsPossible);

    LinkedList* list = createDummyLinkedList(5);
    Node* initialHead = list->head;
    Node* initialTail = list->tail;

    printf("    LIST USED (RESETS AFTER EACH SUBTEST):  ");
    printList(list);
    printf("--------------------------------------------------------\n");

    // Deletes the first node
    deleteElementLinkedList(list, 0);
    if (list->numberOfItems == 4 && list->head != initialHead) {
        printf("    + (0.50) Successfully deleted the first node\n");
    }
    else {
        printf("    - (0.50) Incorrectly deleted the first node\n");
        printList(list);
        penalty += 0.5;
    }

    // Deletes the last node
    freeLinkedList(list);
    list = createDummyLinkedList(5);
    initialHead = list->head;
    initialTail = list->tail;

    deleteElementLinkedList(list, 4);
    if (list->numberOfItems == 4 && list->tail != initialTail && list->tail->next == NULL) {
        printf("    + (0.50) Successfully deleted the tail node\n");
    }
    else {
        printf("    - (0.50) Incorrectly deleted the tail node\n");
        printList(list);
        penalty += 0.5;
    }

    // Deletes a middle node
    freeLinkedList(list);
    list = createDummyLinkedList(5);
    initialHead = list->head;
    initialTail = list->tail;

    deleteElementLinkedList(list, 1);
    if (list->numberOfItems == 4) {
        printf("    + (0.50) Successfully deleted a middle node (position=1)\n");
    }
    else {
        printf("    - (0.50) Incorrectly deleted a middle node (position=1)\n");
        printList(list);
        penalty += 0.5;
    }

    // Tries to delete from invalid indices
    freeLinkedList(list);
    list = createDummyLinkedList(5);
    initialHead = list->head;
    initialTail = list->tail;

    deleteElementLinkedList(list, -10000);
    deleteElementLinkedList(list, 10000);
    if (list->numberOfItems == 5) {
        printf("    + (0.50) Successfully did nothing when given invalid indices (-10000 and 10000)\n");
    }
    else {
        printf("    - (0.50) Incorrectly deleted nodes when given invalid indices (-10000 and 10000)\n");
        printList(list);
        penalty += 0.50;
    }

    // Tries to delete the entire list
    freeLinkedList(list);
    list = createDummyLinkedList(5);
    initialHead = list->head;
    initialTail = list->tail;

    deleteElementLinkedList(list, 0);
    deleteElementLinkedList(list, 0);
    deleteElementLinkedList(list, 0);
    deleteElementLinkedList(list, 0);
    deleteElementLinkedList(list, 0);
    if (list->numberOfItems == 0 && list->head == NULL && list->tail == NULL) {
        printf("    + (0.50) Successfully deleted all nodes\n");
    }
    else {
        printf("    - (0.50) Incorrectly deleted all nodes (numItems either not equal to zero, or head/tail not pointing to null)\n");
        printList(list);
        penalty += 0.50;
    }

    printf("    SCORE: %0.2lf out of %0.2lf possible\n\n", (pointsPossible-penalty), pointsPossible);

    // Frees the Final Linked List
    freeLinkedList(list);
}

void unitTest7() {
    // Keeps track of penalties
    double pointsPossible = 2.5;
    double penalty = 0.0;

    printf("--------------------------------------------------------\n");
    printf("TEST 7:  changeElementLinkedList (5 tests total - %.2f pts)\n", pointsPossible);
    
    LinkedList* list = createDummyLinkedList(5);
    
    printf("    LIST USED (RESETS AFTER EACH SUBTEST):  ");
    printList(list);
    printf("--------------------------------------------------------\n");
    
    // Changes the first element
    Node* newNode = createAnOperatorNode('+');
    changeElementLinkedList(list, 0, newNode);

    if (list->numberOfItems == 5 && *((char*)list->head->data) == '+' && list->head->type == MATH_OPERATOR) {
        printf("    + (0.50) Successfully changed the first node to a math operator ('+')\n");
    }
    else {
        printf("    - (0.50) Incorrectly changed the first node from a REAL_NUMBER to a MATH_OPERATOR '+'\n");
        printList(list);
        penalty += 0.50;
    }

    // Changes the Last Element
    freeLinkedList(list);
    list = createDummyLinkedList(5);
    newNode = createAnOperatorNode('*');
    changeElementLinkedList(list, 4, newNode);

    if (list->numberOfItems == 5 && *((char*)list->tail->data) == '*' && list->tail->type == MATH_OPERATOR) {
        printf("    + (0.50) Successfully changed the last node to a math operator ('*')\n");
    }
    else {
        printf("    - (0.50) Incorrectly changed the last node from a REAL_NUMBER to a MATH_OPERATOR\n");
        printList(list);
        penalty += 0.50;
    }

    // Changes a middle node 
    freeLinkedList(list);
    list = createDummyLinkedList(5);
    newNode = createAnOperatorNode('%');
    changeElementLinkedList(list, 1, newNode);

    if (list->numberOfItems == 5 && *((char*)list->head->next->data) == '%' && list->head->next->type == MATH_OPERATOR) {
        printf("    + (0.50) Successfully changed the second (i.e., middle) node to a MATH_OPERATOR ('%c')\n", '%');
    }
    else {
        printf("    - (0.50) Incorrectly changed the second (i.e., middle) node from a REAL_NUMBER to a MATH_OPERATOR\n");
        printList(list);
        penalty += 0.50;
    }

    // Tries to change an invalid node (positive)
    freeLinkedList(list);
    list = createDummyLinkedList(5);
    newNode = createAnOperatorNode('/');
    changeElementLinkedList(list, 10000, newNode);

    if (list->numberOfItems == 5 && *((char*)list->tail->data) != '/') {
        printf("    + (0.50) Successfully ignored an attempt to change the tail node to a '/' with a big index\n");
    }
    else {
        printf("    - (0.50) Incorrectly ignored an attempt to change the tail node to a '/' with a big index\n");
        printList(list);
        penalty += 0.50;
    }

    // Tries to change an invalid node (negative)
    freeLinkedList(list);
    list = createDummyLinkedList(5);
    newNode = createAnOperatorNode('^');
    changeElementLinkedList(list, -10000, newNode);

    if (list->numberOfItems == 5 && *((char*)list->head->data) != '^') {
        printf("    + (0.50) Successfully ignored an attempt to change the head node to a '^' with a small index\n");
    }
    else {
        printf("    - (0.50) Incorrectly ignored an attempt to change the head node to a '^' with a small index\n");
        printList(list);
        penalty += 0.50;
    }

    printf("    SCORE: %0.2lf out of %0.2lf possible\n\n", (pointsPossible-penalty), pointsPossible);
}

void unitTest8() {
    // Keeps track of penalties
    double pointsPossible = 2.5;
    double pointsAwarded = 0.0;

    printf("--------------------------------------------------------\n");
    printf("TEST 8:  copyElement (5 tests total - %.2f pts)\n", pointsPossible);
    printf("NOTE:  Tests copying a REAL_NUMBER node with 25.0 stored in data\n");
    printf("--------------------------------------------------------\n");

    // The node we want to copy
    Node* nodeToCopy = createARealNumberNode(25.0);
    Node* copyNode = copyElement(nodeToCopy);

    if (copyNode != nodeToCopy) {
        printf("    + (0.50) Successfully created a new node\n");
        pointsAwarded += 0.50;

        if (copyNode->type == nodeToCopy->type) {
            printf("    + (0.50) Successfully set the copy node's type to match the original node\n");
            pointsAwarded += 0.50;

            if (copyNode->next == NULL) {
                printf("    + (0.50) Successfully set the copy node's next pointer to NULL\n");
                pointsAwarded += 0.50;

                if (copyNode->data != nodeToCopy->data) {
                    printf("    + (0.50) Successfully used malloc to set the copy node's data pointer\n");
                    pointsAwarded += 0.50;

                    if (*((double*)copyNode->data) == *((double*)nodeToCopy->data)) {
                        printf("    + (0.50) Successfully set the value in the copy node's data pointer to match the original node\n");
                        pointsAwarded += 0.50;
                    }
                    else {
                        printf("    - (0.50) Incorrectly set the value in the copy node's data pointer (original %lf; copy %lf)\n",
                        *((double*)copyNode->data), *((double*)nodeToCopy->data));
                    }
                }
                else if (copyNode->data == nodeToCopy->data) {
                    printf("    - (1.00) Incorrectly set the copy node's data pointer to point to the original node's data\n");
                }
                else {
                    printf("    - (1.00) Incorrectly did something with the copy node's data pointer\n");
                }
            }
            else {
                printf("    - (0.50) Incorrectly set the copy node's next pointer\n");
            }
        }
        else {
            printf("    - (0.50) Incorrectly set the copy node's type to match the original node\n");
        }
    }
    else if (copyNode == nodeToCopy) {
        printf("    - (0.50) Incorrectly returned a pointer to the node to copy (instead of making a new node)\n");
    }
    else {
        printf("    - (0.50) Incorrectly copied the node\n");
    }

    printf("    SCORE: %0.2lf out of %0.2lf possible\n\n", pointsAwarded, pointsPossible);

    // Free the mallocs!
    free(nodeToCopy);
    free(copyNode);
}

void unitTest9() {
    // Keeps track of penalties
    double pointsPossible = 1.50;

    printf("--------------------------------------------------------\n");
    printf("TEST 9:  deleteLinkedList (0 automatic tests - %.2f pts)\n", pointsPossible);
    printf("--------------------------------------------------------\n");
    printf("    - GRADED VIA VISUAL INSPECTION\n");
    printf("    - Verify that you are deleting the data, the node, and the list struct\n");
    
    printf("    SCORE: TBD; up to %0.2lf possible\n\n", pointsPossible);
}

void unitTest10() {
    // Keeps track of penalties
    double pointsPossible = 1.0;

    printf("--------------------------------------------------------\n");
    printf("TEST 10:  printLinkedList (1 test total - %.2f pts)\n", pointsPossible);
    printf("--------------------------------------------------------\n");
    printf("    - GRADED VIA VISUAL INSPECTION\n");

    // Create a List with Some Numbers and Math Operators
    LinkedList* list = createDummyLinkedList(0);
    addElementLinkedList(list, 0, createARealNumberNode(1.0));
    addElementLinkedList(list, 0, createARealNumberNode(2.0));
    addElementLinkedList(list, 0, createAnOperatorNode('+'));
    addElementLinkedList(list, 0, createARealNumberNode(3.0));
    addElementLinkedList(list, 0, createAnOperatorNode('*'));
    
    // This prints using our print function
    printf("    PRINTING CORRECT LIST CONTENTS\n");
    printList(list);
    printf("\n");

    // This prints using the student print function:
    printf("    PRINTING USING STUDENT PRINT FUNCTION\n");
    printf("    ");
    printLinkedList(list);

    printf("\n    SCORE: TBD; up to %0.2lf possible\n\n", pointsPossible);

    // Frees the Final Linked List
    freeLinkedList(list);
}

int runAllTests() {
    unitTest1();
    unitTest2();
    unitTest3();
    unitTest4();
    unitTest5();
    unitTest6();
    unitTest7();
    unitTest8();
    unitTest9();
    unitTest10();
    return 0;
}
