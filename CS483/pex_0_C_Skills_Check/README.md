# PEX0 - C Proficiency

## Project Overview
This project is a basic C program designed to test proficiency in using C language constructs such as arrays, pointers, linked lists, and dynamic memory allocation. The program demonstrates handling of command-line arguments, loops, function usage, and basic linked list operations.

## Features
- **Command-Line Argument Handling**: The program accepts command-line arguments and prints the first argument passed.
- **Looping and Conditions**: It prints numbers from 1 to 20 that are divisible by 3.
- **Function Call**: The program defines a function (`func1`) that accepts an integer array and returns the first element multiplied by 2.
- **Linked List Implementation**: A basic linked list with statically and dynamically allocated nodes.
- **Dynamic Memory Allocation**: Demonstrates memory allocation for a node using `malloc`.

## Code Explanation

### func1
This function accepts an integer array as a parameter and returns the first element multiplied by 2.
```c
int func1(int array[]) {
    return (array[0] * 2);
}

```
### main
The main() function performs several tasks, including handling command-line arguments, looping, manipulating arrays, and performing basic linked list operations.
```c
int main(int argc, char* argv[]){
    // Collect and print the first command-line argument
    char first[100];
    strcpy(first, argv[1]);
    printf("%s\n", first);

    // Print numbers from 1 to 20 that are divisible by 3
    for(int i = 1; i < 21; i++){
        if (i % 3 == 0){
            printf("%d ", i);
        }
    }
    printf("\n");

    // Integer array with first element as 5 to be passed to func1
    int array[10];
    array[0] = 5;
    printf("%d\n", func1(array));

    // Linked list with two nodes
    NodeType node1;
    strncpy(node1.name, "Node 1", 64);

    NodeType node2;
    strncpy(node2.name, "Node 2", 64);

    // Set node1.next to point to node2, and node2.next to NULL
    node1.next = &node2;
    node2.next = NULL;

    // Print out the names of the nodes
    printf("%s\n", node1.name);
    printf("%s\n", node1.next->name);

    // Dynamic memory allocation for another node
    NodeType* nodePtr;
    NodeType* dynamicNode = (NodeType*) malloc(sizeof(NodeType));

    nodePtr = dynamicNode;
    strncpy(nodePtr->name, "Node 3", 64);
    nodePtr->next = NULL;

    // Print the dynamically allocated node's name
    printf("%s\n", nodePtr->name);

    // Print the time taken to complete the assignment
    printf("Took 60 minutes to complete assignment\n");

    return 0;
}
```
