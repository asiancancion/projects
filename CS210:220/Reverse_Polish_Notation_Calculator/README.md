# RPN Calculator

## Name: Caleb Song  
**Section**: M3 De Freitas  
**Project**: PEX 3 - Reverse Polish Notation (RPN) Calculator  
**Purpose**:  
This project implements a Reverse Polish Notation (RPN) calculator. The program takes a mathematical expression in RPN format as input, processes it using stacks and queues, and outputs the result. The RPN calculator handles basic arithmetic operations and checks for valid input.

## Overview of Reverse Polish Notation (RPN)
In Reverse Polish Notation, operators follow their operands. This eliminates the need for parentheses to define operation precedence. For example, the expression `3 + 4` in traditional notation is written as `3 4 +` in RPN.

### Features:
- Supports basic arithmetic operators: `+`, `-`, `*`, `/`, and `^` (exponentiation).
- Handles both positive and negative numbers.
- Detects and reports invalid input.
- Uses linked-list implementations for both the stack and queue data structures.

## Code Explanation

### Includes
The following files are included to handle utility functions and unit testing:
```c
#include "rpnUtils.h"
#include "unitTest.h"
#include <stdio.h>

```

### Main Function
The main() function processes user input in an infinite loop, parsing the input expression, converting it into tokens, and evaluating the RPN expression.

```c
int main() {
    char str[100];         // Stores the RPN expression input by the user
    char delimiter[2] = " ";  // Delimiter for tokenizing the input expression
    char* token;           // Pointer to the current token
    bool valid = true;      // Flag to control the input loop

    // Loop until valid input is no longer provided
    while (valid == true) {
        printf("RPN Expression: ");
        fgets(str, 100, stdin);

        token = strtok(str, delimiter);

        QueueAsLinkedList* queue = queueInit();
        Node* newNode = NULL;

        // Exit the loop if the user provides an empty input
        if (*token == '\n') {
            exit(0);
        }

        // Process the user input string, token by token
        while (token != NULL) {
            if (atof(token) < 0) {
                newNode = createNumberNode(atof(token)); // Negative number
                queueEnqueue(queue, newNode);
            } else if (*token == '+' || *token == '-' || *token == '*' || *token == '/' || *token == '^') {
                newNode = createOperatorNode(*token); // Operator
                queueEnqueue(queue, newNode);
            } else if (*token == '0') {
                newNode = createNumberNode(atof(token)); // Handle number 0
                queueEnqueue(queue, newNode);
            } else if (atof(token) == 0) {
                printf("INVALID INPUT\n");  // Handle invalid input
                exit(1);
            } else {
                newNode = createNumberNode(atof(token));  // Positive number
                queueEnqueue(queue, newNode);
            }
            token = strtok(NULL, delimiter);  // Move to the next token
        }

        // Print the tokenized queue
        printf("\nTokenized Queue: ");
        queuePrint(queue);

        // Initialize the stack
        StackAsLinkedList* stack = stackInit();
        Node* operator;

        // Process the RPN expression from the queue
        while (queueIsEmpty(queue) != true) {
            if (queueSize(queue) == 1 && stackSize(stack) == 0) {
                if (queue->head->type == REAL_NUMBER) {
                    stackPush(stack, queueDequeue(queue));
                } else {
                    printf("EXPRESSION INVALID\n");
                    exit(1);
                }
            } else if (queueSize(queue) == 2 && stackSize(stack) == 0) {
                printf("EXPRESSION INVALID\n");
                exit(1);
            } else {
                operator = createOperatorNode(*(char*)queueToStack(queue, stack)->data);  // Extract operator
                printf(" Operator: \'%c\' | Stack Before Operation: ", *(char*)operator->data);
                stackPrint(stack);  // Print the stack before performing the operation
                doOperator(operator, stack);  // Perform the operation
            }
        }

        // Validate the final stack size
        if (stackSize(stack) != 1) {
            printf("EXPRESSION INVALID\n");
            exit(1);
        }

        // Print the final answer
        printf("Final Answer: %.3lf\n\n", *(double*)stack->head->data);
    }
}

```

### Key Functions
Tokenization:
The input string is split into tokens using strtok(), and each token is processed to determine whether it's a number or an operator.

Queue Operations:
The tokens are enqueued into a queue, which is implemented using a linked list.

Stack Operations:
The program uses a stack to handle the operators and numbers, following the RPN logic. When an operator is encountered, it pops the necessary operands from the stack, performs the operation, and pushes the result back onto the stack.

Error Handling:

The program detects invalid input such as incorrect operators or an incorrect RPN format.
It handles edge cases like an empty input or operators without sufficient operands.


### `queueToStack(QueueAsLinkedList* queue, StackAsLinkedList* stack)`
This function dequeues values from the queue and pushes them onto the stack until a mathematical operator is reached. It returns the operator once found.

```c
Node* queueToStack(QueueAsLinkedList* queue, StackAsLinkedList* stack) {
    // Push numbers from queue to stack until a math operator is encountered
    while (queue->tail->type != MATH_OPERATOR) {
        stackPush(stack, queueDequeue(queue));
    }
    // Dequeue the math operator and return it
    Node* operator = queueDequeue(queue);
    return operator;
}

```
### `doOperator(Node* operator, StackAsLinkedList* stack)`
This function performs the specified arithmetic operation based on the operator provided. It pops two numbers from the stack, applies the operation, and pushes the result back onto the stack. Supported operations include addition, subtraction, multiplication, division, and exponentiation.

```c
void doOperator(Node* operator, StackAsLinkedList* stack) {
    char opCheck = *(char*)operator->data;  // Get the operator symbol
    double num1 = 0.0;
    double num2 = 0.0;
    double result = 0.0;
    Node* opNode;
    Node* newNode;

    // Pop two numbers from the stack for the operation
    if (stack->head == NULL) {
        printf("EXPRESSION INVALID\n");
        exit(1);
    }
    opNode = createNumberNode(*(double*)stackPop(stack)->data);
    num1 = *(double*)(opNode->data);

    if (stack->head == NULL) {
        printf("EXPRESSION INVALID\n");
        exit(1);
    }
    opNode = createNumberNode(*(double*)stackPop(stack)->data);
    num2 = *(double*)(opNode->data);

    // Perform the operation
    switch (opCheck) {
        case '+':
            result = num2 + num1;
            break;
        case '-':
            result = num2 - num1;
            break;
        case '*':
            result = num2 * num1;
            break;
        case '/':
            if (num1 == 0) {
                printf("DIVISION BY ZERO ERROR\n");
                exit(1);
            }
            result = num2 / num1;
            break;
        case '^':
            result = pow(num2, num1);
            break;
        default:
            printf("INVALID OPERATOR\n");
            exit(1);
    }

    // Push the result back onto the stack
    newNode = createNumberNode(result);
    stackPush(stack, newNode);
}

```

