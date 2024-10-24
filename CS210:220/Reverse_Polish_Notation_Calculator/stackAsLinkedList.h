/** stackAsLinkedList.h
 * ===========================================================
 * Name: 
 * Section: n/a
 * Project: Lesson13 - Stack ADT implemented using linked list
 * Purpose: Stack ADT library - LIFO
 * ===========================================================
 */

#ifndef STACKASLINKEDLIST_H
#define STACKASLINKEDLIST_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "listAsLinkedList.h"

typedef LinkedList StackAsLinkedList;  // define Stack datatype as LinkedList

/** stackInit()
 * @brief  - initializes the stack structure
 * @return - pointer to stack structure
 * @pre    - nothing
 * @post   - new empty stack returned
 */
StackAsLinkedList* stackInit();

/** stackPush()
 * @brief - places an node onto the top of the stack
 * @param node - ptr to the Node to push onto the stack
 * @pre   - 1. Node* pointing to dynamically allocated Node where
 *              type and data have been set
 *          2. stack before node added
 * @post  - stack one node taller
 */
void stackPush(StackAsLinkedList* stack, Node* node);

/** stackPop()
 * @brief  - pops a node off the stack
 * @param  stack - a ptr to the stack structure
 * @return - ptr to the top of the stack on success, NULL on failure
 * @pre    - stack before top node removed
 * @post   - stack one node shorter and ptr to Node returned
 */
Node* stackPop(StackAsLinkedList* stack);

/** stackIsEmpty()
 * @brief  - determines if the stack is empty
 * @param stack - a ptr to the stack structure
 * @return - true if the stack is empty or false if not
 * @pre    - stack unmodified
 * @post   - stack unmodified and empty status returned
 */
bool stackIsEmpty(StackAsLinkedList* stack);

/** stackIsFull()
 * @brief - determines if the stack is full
 * @param stack - a ptr to the stack structure
 * @return - true if the stack is full or false if not
 * @pre    - stack unmodified
 * @post   - stack unmodified; returns false if not full
 */
bool stackIsFull(StackAsLinkedList* stack);

/** deleteLinkedList(()
 * @brief  - deletes stack, freeing all memory used
 * @param stack - a ptr to the stack structure
 * @pre    - unmodified stack
 * @post   - the stack is erased; all nodes and data are freed
 */
void deleteStack(StackAsLinkedList* stack);

/** stackPeek()
 * @brief  - returns the item on the top of the
 *           stack but doesn't remove it
 * @param stack - a ptr to the stack structure
 * @param  type - ptr to the enumeration of the node
 * @return - ptr the Node on the top of the stack;
 *              NULL if stack is empty
 * @pre    - stack unmodified; type to be updated unchanged
 * @post   - stack unmodified; ptr to top Node returned
 */
Node* stackPeek(StackAsLinkedList* stack);

/** stackSize()
 * @brief  - determines the size of the stack
 * @param stack - a ptr to the stack structure
 * @return - number of items in the stack
 * @pre    - stack unmodified
 * @post   - stack unmodified; size of stack returned
 */
int stackSize(StackAsLinkedList* stack);

/** stackPrint()
 * @brief  - outputs the stack to the console
 * @param stack - the stack structure
 * @pre    - stack unmodified
 * @post   - stack unmodified; stack items printed
 */
void stackPrint(StackAsLinkedList* stack);

#endif  // STACKASLINKEDLIST_H
