// Your implementation of the functions defined in historyList.h goes here
#include "historyList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* listInsertTail: create a new node at the end of the linked list
   Parameters
   - HistoryNodeType* head: a pointer to the head of a linked list
   - char* data: data to be stored in the new node
   Return: a pointer to the head of the linked list */
HistoryNodeType* listInsertTail(HistoryNodeType* head, char* data){
    HistoryNodeType* newTail = (HistoryNodeType*)malloc(sizeof(newTail));
    newTail->next = NULL;
    newTail->data = strdup(data); 
    //MAKE SURE TO FREE DATA
    HistoryNodeType* currentNode;
    
    //if list is empty
    if (head == NULL){
       return newTail;
    }
    else{
        currentNode = head;
        while(currentNode->next != NULL){
            currentNode = currentNode->next;
        }
        currentNode->next = newTail;
        return head;
    }
    
}

/* listInsertHead: create a new node and insert it at the head of the linked
    list
   Parameters
   - HistoryNodeType* head: a pointer to the head of a linked list
   - char* data: data to be stored in the new node
   Return: a pointer to the new head of the linked list */
HistoryNodeType* listInsertHead(HistoryNodeType* head, char* data){
    HistoryNodeType* newHead = (HistoryNodeType*)malloc(sizeof(newHead));
    newHead->next = head;
    newHead->data = strdup(data);
    return newHead;
}

/* listInsertN: create a new node and insert it at the <n>th position,
    where the head is at position 1
   Parameters
   - HistoryNodeType* head: a pointer to the head of a linked list
   - char* data: data to be stored in the new node
   - int position: the position in which to insert the new node
   Return: a pointer to the head of the linked list */
HistoryNodeType* listInsertN(HistoryNodeType* head, char* data, int position){
    HistoryNodeType* newNode = (HistoryNodeType*)malloc(sizeof(newNode));
    newNode->next = NULL;
    newNode->data = strdup(data);
    HistoryNodeType* nodeCounter = (HistoryNodeType*)malloc(sizeof(nodeCounter));
    nodeCounter = head;
    int counter = 0;
    position-=1;
    while(nodeCounter!=NULL){
        nodeCounter = nodeCounter->next;
        counter+=1;
    }
    if (position < 0){
        printf("Error invalid position\n");
    }
    else if (head == NULL) {
        // CASE 1:  Adding to an empty list
        return newNode;
    }
    else if (position == counter) {
        return listInsertTail(head,data);
    }
    else if (position > 0  && position < counter) {
        // CASE 4:  Adding in the middle
        HistoryNodeType* tmp = head;
        // Find the node just before the position we want to insert
        for (int i=0; i<position-1; i++) {
            tmp = tmp->next;
        }
        // Inserts the node in the middle
        newNode->next = tmp->next;
        tmp->next = newNode;
    }
    //prints error if position to insert is out of range
    else{
        printf("Error invalid position\n");
    }
}

/* listRemove: remove the node containing specific data; if multiple nodes
    contain the data, remove the node nearest to the head
   Parameters
   - HistoryNodeType*: a pointer to the head of a linked list
   - char*: data that, if found in one of the nodes in the list, indicates
      the node to remove (in the case of multiple nodes containing the data,
	  remove the node nearest to the head)
   - int*: pointer to integer that tracks how many elements are in linked list
   Return: a pointer to the head of the linked list */
HistoryNodeType* listRemove(HistoryNodeType* head, char* data, int* counter){
    HistoryNodeType* node = head;
    HistoryNodeType* prev = NULL;

    if(head == NULL){
        return head;
    }
    else{
        while(node != NULL){
            if(strcmp(node->data,data) == 0){
                if (prev == NULL){
                    head = node->next;
                }
                else{
                    prev->next = node->next;
                }
                
                free(node);
                *counter-=1;
                break;
            }
            prev = node;
            node = node->next;
        }
        return head;
    }

}

/* listRemoveN: remove the <n>th node in the list
   Parameters
   - HistoryNodeType*: a pointer to the head of a linked list
   - int: the position of the node to remove, where the head is at position 1
   Return: a pointer to the head of the linked list */
HistoryNodeType* listRemoveN(HistoryNodeType* head, int position){
    HistoryNodeType* node;
    HistoryNodeType* nodeCounter;
    HistoryNodeType* prev;
    nodeCounter = head;
    int counter = 0;
    position-=1;
    while(nodeCounter!=NULL){
        prev = nodeCounter;
        nodeCounter = nodeCounter->next;
        counter+=1;
    }
    if (position < 0){
        printf("Error invalid position\n");
    }
    else if (head == NULL) {
        // CASE 1:  Removing from an empty list
        printf("Error head is NULL\n");
    }
    else if (position == counter) {
        prev->next = NULL;
        free(nodeCounter);
        return head;
    }
    else if (position > 0  && position < counter) {
        // CASE 4:  Adding in the middle
        HistoryNodeType* tmp = head;
        // Find the node just before the position we want to insert
        for (int i=0; i<position-1; i++) {
            tmp = tmp->next;
        }
        node = tmp->next;
        tmp->next = tmp->next->next;
        // Inserts the node in the middle
        free(node);
        return head;

    }
    //prints error if position to insert is out of range
    else{
        printf("Error invalid position\n");
    }
}

/* listPrint: print the data contained in each node in the linked list,
    starting with the head, where each node's data is printed on a separate
    line
   Parameter: node*: a pointer to the head of a linked list */
void listPrint(HistoryNodeType* head){
    HistoryNodeType* node;
    node = head;
    int counter = 1;
    while(node != NULL){
        printf("%d %s\n",counter, node->data);
        node = node->next;
        counter+=1;
    }
}

/* listprintN: print the data contained in the <n>th node of the list
   Parameters:
   - HistoryNodeType*: a pointer to the head of a linked list
   - int: the position of the node with the data to print, where the head is
       at position 1 */
void listPrintN(HistoryNodeType* head, int position){
    for (int i = 1; i<position; i++){
        if (head == NULL){
            perror("Out of Range");
        }
        head = head->next;
    }
    printf("%s\n", head->data);

}

/* listGet: retrieve the data stored in the <n>th node in the list
   Parameters:
   - HistoryNodeType*: a pointer to the head of a linked list
   - int: the position of the node with the data to retrieve, where the head is
       at position 1
   Return: the data */
char* listGet(HistoryNodeType* head, int position){
    HistoryNodeType* node = head;
    position -=1;
    for (int i = 0; i<position; i++){
        node = node->next;
    }
    return node->data;
}

/* listDestroy: free all malloc'd memory used in the linked list,
    including char*'s and HistoryNodeType*'s
   Parameter: HistoryNodeType*: a pointer to the head of a linked list */
void listDestroy(HistoryNodeType* head){
    HistoryNodeType* node = head;
    HistoryNodeType* tmp;
    while (node != NULL){
        tmp = node->next;
        free(node);
        node = tmp;
    }
}
