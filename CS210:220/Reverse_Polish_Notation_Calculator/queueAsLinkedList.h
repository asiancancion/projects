/** queueAsLinkedList.h
 * ===========================================================
 * Name: 
 * Section: n/a
 * Project: Lesson14 - Queue ADT implemented using linked list
 * Purpose: Queue ADT library - FIFO
 * ===========================================================
 */

#ifndef QUEUEASLIST_H
#define QUEUEASLIST_H
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "listAsLinkedList.h"

typedef LinkedList QueueAsLinkedList;

/** queueInit()
 * @brief  - initializes the queue structure
 * @return - pointer to queue structure
 * @pre    - nothing
 * @post   - ptr to new empty queue returned
 */
QueueAsLinkedList* queueInit();

/** queueEnqueue()
 * @brief - places a node onto the end of the queue
 * @param queue - a ptr to the queue structure
 * @param node - ptr to the Node to add to the end of the queue
 * @pre   - 1. Node* pointing to dynamically allocated node where
 *              type and data have been set
 *          2. queue before node added
 * @post  - queue one node longer
 */
void queueEnqueue(QueueAsLinkedList* queue, Node* node);

/** queueDequeue()
 * @brief - removes an node from the front of the queue
 * @param queue - a ptr to the queue structure
 * @return - ptr to the node removed, NULL on failure
 * @pre   - queue before node removed from the front
 * @post  - queue one node shorter; ptr to node removed returned
 */
Node* queueDequeue(QueueAsLinkedList* queue);

/** queueIsEmpty()
 * @brief  - determines if the queue is empty
 * @param queue - a ptr to the queue structure
 * @return - true if the queue is empty or false if not
 * @pre    - queue unmodified
 * @post   - queue unmodified; and empty status returned (T or F)
 */
bool queueIsEmpty(QueueAsLinkedList* queue);

/** queueIsFull()
 * @brief - determines if the queue is full
 * @param queue - a ptr to the queue structure
 * @return - true if the queue is full or false if not
 * @pre    - queue unmodified
 * @post   - queue unmodified; returns false if not full
 */
bool queueIsFull(QueueAsLinkedList* queue);

/** deleteQueue()
 * @brief  - deletes queue, freeing all memory used
 * @param queue - a ptr to the queue structure
 * @pre    - unmodified queue
 * @post   - the queue is erased, and all nodes and data freed
 */
void deleteQueue(QueueAsLinkedList* queue);

/** queuePeek()
 * @brief  - returns the node at the front of the
 *           queue but doesn't remove it
 * @param queue - a ptr to the queue structure
 * @return - ptr to the Node at the front of the queue;
 *           NULL if queue is empty
 * @pre    - queue unmodified
 * @post   - queue unmodified; ptr to front Node returned
 */
Node* queuePeek(QueueAsLinkedList* queue);

/** queueSize()
 * @brief  - determines the size of the queue
 * @param queue - a ptr to the queue structure
 * @return - number of items in the queue
 * @pre    - queue unmodified
 * @post   - queue unmodified; size of queue returned
 */
int queueSize(QueueAsLinkedList* queue);

/** queuePrint()
 * @brief  - outputs the queue to the console
 * @param queue - the queue structure
 * @pre    - queue unmodified
 * @post   - queue unmodified; queue items printed
 */
void queuePrint(QueueAsLinkedList* queue);

#endif  // QUEUEASLIST_H
