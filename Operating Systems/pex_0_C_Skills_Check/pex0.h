/** PEX0.h
 * =============================================================
 * Name: Caleb Song
 * Section: M6
 * Project: PEX0 - C Proficiency
 * Documentation Statement:Used provided website for commmand line arguments, looked up on tutorialspoint
 * how to dynamically allocate memory.
 * =============================================================
 */
//NodeType struct
typedef struct node{
    //name
    char name[64];
    //pointer to next node struct
    struct node* next;
}NodeType;