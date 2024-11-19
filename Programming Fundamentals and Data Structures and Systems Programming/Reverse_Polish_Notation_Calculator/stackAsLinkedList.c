/** stackAsLinkedList.c
 * ===========================================================
 * Name: Caleb Song
 * Section: M3 - De Freitas
 * Project: PEX 3 - RPN Calculator
 * Purpose: Stack ADT library - LIFO
 * ===========================================================
 */
#include "stackAsLinkedList.h"
#include "listAsLinkedList.h"

/** stackInit()
 * @brief  - initializes the stack structure
 * @return - pointer to stack structure
 * @pre    - nothing
 * @post   - new empty stack returned
 */
StackAsLinkedList* stackInit() {
    StackAsLinkedList* newStack = linkedListInit();
    return newStack;
}

/** stackPush()
 * @brief - places an node onto the top of the stack
 * @param node - ptr to the Node to push onto the stack
 * @pre   - 1. Node* pointing to dynamically allocated Node where
 *              type and data have been set
 *          2. stack before node added
 * @post  - stack one node taller
 */
void stackPush(StackAsLinkedList* stack, Node* node) {
    insertElementLinkedList(stack, 0, node);
}

/** stackPop()
 * @brief  - pops a node off the stack
 * @param  stack - a ptr to the stack structure
 * @return - ptr to the top of the stack on success, NULL on failure
 * @pre    - stack before top node removed
 * @post   - stack one node shorter and ptr to Node returned
 */
Node* stackPop(StackAsLinkedList* stack) {
    Node* returnNode;
    if (stack->numberOfItems == 0){
        return NULL;
    }
    else{
        returnNode = createNumberNode(*(double*)stack->head->data);
        deleteElementLinkedList(stack,0);
        return returnNode;
    }
}

/** stackIsEmpty()
 * @brief  - determines if the stack is empty
 * @param stack - a ptr to the stack structure
 * @return - true if the stack is empty or false if not
 * @pre    - stack unmodified
 * @post   - stack unmodified and empty status returned
 */
bool stackIsEmpty(StackAsLinkedList* stack) {
    if (lengthOfLinkedList(stack)!=0){
        return false;
    }
    else{
        return true;
    }
}

/** stackIsFull()
 * @brief - determines if the stack is full
 * @param stack - a ptr to the stack structure
 * @return - true if the stack is full or false if not
 * @pre    - stack unmodified
 * @post   - stack unmodified; returns false if not full
 */
bool stackIsFull(StackAsLinkedList* stack) {
    return false;
}

/** deleteLinkedList(()
 * @brief  - deletes stack, freeing all memory used
 * @param stack - a ptr to the stack structure
 * @pre    - unmodified stack
 * @post   - the stack is erased; all nodes and data are freed
 */
void deleteStack(StackAsLinkedList* stack) {
    deleteLinkedList(stack);
}

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
Node* stackPeek(StackAsLinkedList* stack) {
    if (stack->numberOfItems == 0){
        return NULL;
    }
    else{
        return stack->head;
    }

}

/** stackSize()
 * @brief  - determines the size of the stack
 * @param stack - a ptr to the stack structure
 * @return - number of items in the stack
 * @pre    - stack unmodified
 * @post   - stack unmodified; size of stack returned
 */
int stackSize(StackAsLinkedList* stack) {
    return stack->numberOfItems;
}

/** stackPrint()
 * @brief  - outputs the stack to the console
 * @param stack - the stack structure
 * @pre    - stack unmodified
 * @post   - stack unmodified; stack items printed
 */
void stackPrint(StackAsLinkedList* stack) {
    printLinkedList(stack);
}