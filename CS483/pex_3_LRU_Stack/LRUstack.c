#include "LRUstack.h"
#include <stdlib.h>


//initiailize LRU stack
void intialize(lrustack* lrus, unsigned int maxSize){
    lrus->maxSize = maxSize;
    lrus->head= NULL;
    lrus->tail= NULL;
}
/* use pagenum when creating a new node, which will be pushed onto
   the LRU stack; make sure to keep track of the LRU stack's size
   and free and reset the tial as necessary to limit to max size
*/
void push (lrustack* lrus, unsigned long pagenum){
    node* newNode = (node*) malloc(sizeof(node));
    newNode->pagenum = pagenum;
    newNode->prev=NULL;
    newNode->next=lrus->head;


    //if head is null
    if (lrus->head == NULL){
        lrus->head = newNode;
        lrus->tail = newNode;
    }
    else{
        lrus->head->prev = newNode;
        lrus->head = newNode;
    }
    lrus->size +=1;

    //if we exceed max size then we remove the least recently used node
    if (lrus->size > lrus->maxSize){
        node* tail = lrus->tail;
        lrus->tail = lrus->tail->prev;
        lrus->tail->next = NULL;
        free (tail);
        lrus->size--;
    }

}
/* seek pagenum in lrus and remove it if found; return the depth
   at which pagenum was found or -1 if not
*/
int seek_and_remove(lrustack* lrus, unsigned long pagenum){
    node* current = lrus->head;
    int depth = 0;
    //list empty
    if (lrus->head == NULL){
        return -1;
    }
    //remove head
    if (lrus->head->pagenum == pagenum){
        lrus->head = lrus->head->next;
        if (lrus->head != NULL){
            lrus->head->prev = NULL;
        }
        else{
            lrus->tail = NULL;
        }
        free(current);
        lrus->size--;
        return depth;
    }


    while (current!=NULL){
        if (current->pagenum == pagenum){
            if (current->next != NULL){
                current->next->prev = current->prev;
            }
            else{
                lrus->tail = current->prev;
            }
            if (current->prev != NULL){
                current->prev->next = current->next;
            }
            free(current);
            lrus->size--;
            return depth;
        }
        else{
            current = current->next;
            depth++;
        }


    }
    return -1;
}