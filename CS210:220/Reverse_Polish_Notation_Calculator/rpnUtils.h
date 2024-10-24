/** rpnUtils.c
 * ===========================================================
 * Name: Caleb Song
 * Section: M3 - De Freitas
 * Project: PEX 3 - RPN Calculator
 * Purpose: Reverse polish notation utilities library
 * ===========================================================
 */

#ifndef RPNUTILS_H
#define RPNUTILS_H

// What other includes do you need?
#include <string.h>

#include "listAsLinkedList.h"
#include "queueAsLinkedList.h"
#include "stackAsLinkedList.h"


// prototypes for RPN calculator helper functions go here!!!

/** queueToStack()
 * @brief  - Pushes dequeued values to stack
 * @return - Math operator
 * @pre    - queue to take elements from, stack to push elements to
 * @post   - queue decreased in size, stack increased in size
 */
Node* queueToStack(QueueAsLinkedList* queue, StackAsLinkedList* stack);
/** queueToStack()
 * @brief  - Does math operation on elements of stack then pushes value back into stack
 * @pre    - operator - math operator (+,-,*,/,^) to perform, stack that has elements in it
 * @post   - stack changes after operation
 */
void doOperator(Node* operator, StackAsLinkedList* stack);
#endif  // RPNUTILS_H
