/** rpnUtils.c
 * ===========================================================
 * Name: Caleb Song
 * Section: M3 - De Freitas
 * Project: PEX 3 - RPN Calculator
 * Purpose: Reverse polish notation utilities library
 * ===========================================================
 */

#include "rpnUtils.h"
#include <stdio.h>
#include <math.h>


// Place helper functions for RPN calculator here!!!


Node* queueToStack(QueueAsLinkedList* queue, StackAsLinkedList* stack){
    //Pushes dequeued number from queue into stack until a math operator is reached
    while (queue->tail->type != MATH_OPERATOR){
        stackPush(stack, queueDequeue(queue));
    }
    //Dequeue the math operator and then return it
    Node* operator = queueDequeue(queue);
    return operator;
}

void doOperator(Node* operator, StackAsLinkedList* stack){
    char opCheck = *(char*)operator->data;
    double num1 = 0.0;
    double num2 = 0.0;
    double num = 0.0;
    Node* opNode;
    Node* newNode;    
    //Pop two numbers off of stack to perform operation on it
    //if the stack head is NULL then it is invalid
    if (stack->head == NULL){
        printf("EXPRESSION INVALID\n");
        exit(1);
    }
    opNode = createNumberNode(*(double*)stackPop(stack)->data);
    num1 = *(double*)(opNode->data);
    //if the stack head is NULL then it is invalid
    if (stack->head == NULL){
        printf("EXPRESSION INVALID\n");
        exit(1);
    }
    opNode = createNumberNode(*(double*)stackPop(stack)->data);
    num2 = *(double*)(opNode->data);
    //Addition
    if (opCheck == '+'){
        num=num2+num1;
        newNode = createNumberNode(num);
        stackPush(stack, newNode);
    }
    //Subtraction
    else if (opCheck == '-'){
        num = num2-num1;
        newNode = createNumberNode(num);
        stackPush(stack, newNode);
    }
    //Division
    else if (opCheck == '/'){
        num = num2/num1;
        newNode = createNumberNode(num);
        stackPush(stack,newNode);
    }
    //Multiplication
    else if (opCheck == '*'){
        num = num2*num1;
        newNode = createNumberNode(num);
        stackPush(stack,newNode);
    }
    //Power
    else if (opCheck == '^'){
        num = pow(num2,num1);
        newNode = createNumberNode(num);
        stackPush(stack,newNode);
    }

}