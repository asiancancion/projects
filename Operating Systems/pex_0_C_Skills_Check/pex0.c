/** PEX0.c
 * =============================================================
 * Name: Caleb Song
 * Section: M6
 * Project: PEX0 - C Proficiency
 * Documentation Statement: Used provided website for commmand line arguments, looked up on tutorialspoint
 * how to dynamically allocate memory.
 * =============================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pex0.h"

//func1 - accpets integer array as parameter
int func1(int array[]){
    //returns first element of integer array multiplied by 2
    return (array[0]*2);
}

//Main - collects command line argument
int main(int argc, char* argv[]){
    //collect and print first command line argument
    char first[100];
    strcpy(first, argv[1]);
    printf("%s\n",first);
    //print numbers 1->20 that are divisible by 3
    for(int i = 1; i< 21; i++){
        if (i%3 == 0){
            printf("%d ",i);
        }
    }
    printf("\n");
    //integer array with first element as 5 to be passed to func1
    int array[10];
    array[0] = 5;
    printf("%d\n", func1(array));

    //Node with Node 1 copied into it
    NodeType node1;
    strncpy(node1.name, "Node 1",64);
    
    //Node with Node 2 copied into it
    NodeType node2;
    strncpy(node2.name, "Node 2",64);

    //set node1.next to point to node2
    node1.next = &node2;
    //set node2.next to point to NULL
    node2.next = NULL;

    //print out name of node1
    printf("%s\n", node1.name);
    //print out name of node2 via the next pointer from node1
    printf("%s\n", node1.next->name);

    //created a pointer to a Node
    NodeType* nodePtr;

    //dynamically allocate memory
    NodeType *dynamicNode = (NodeType*)malloc(sizeof(NodeType));

    nodePtr = dynamicNode;
    //Copy string "Node 3" into the nodePtr name
    strncpy(nodePtr->name,"Node 3",64);
    //set next of node3 to NULL
    nodePtr->next = NULL;
    //print out node3
    printf("%s\n",nodePtr->name);
    //print out how long it took to complete assignment
    printf("Took 60 minutes to complete assignment\n");
  
}