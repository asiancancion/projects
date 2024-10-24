/** rpnCalc.c
 * ===========================================================
 * Name: Caleb Song
 * Section: M3 De Freitas
 * Project: PEX 3 - RPN Calculator
 * Purpose: Calculate answer given input in
 *          reverse polish notation
 * Documentation: NONE, besides asking Lt Col De Freitas some questions
 * ===========================================================
 */

// what includes do we need here?

#include "rpnUtils.h"
#include "unitTest.h"
#include <stdio.h>

int main() {

    char str[100];
    char delimiter[2] = " ";
    char* token;
    bool valid = true;

    //Loops infinetely until user inputs invalid input or null string
    while(valid == true){
        printf("RPN Expression: ");
        fgets(str,100,stdin);

        token = strtok(str, delimiter);


        QueueAsLinkedList* queue = queueInit();
        Node* newNode = NULL;
        //User inputs null String exits program
        if(*token == '\n'){
            exit(0);
        }
        //Reads in string user inputted
        while (token != NULL){
            //If user inputs negative number creates Number Node and puts in queue
            if (atof(token) < 0){
                newNode = createNumberNode(atof(token));
                queueEnqueue(queue, newNode);
            }
            //else if user inputs one of the math operators creates Operator Node and puts in queue
            else if (*token == '+' || *token == '-' || *token == '*' || *token == '/' || *token == '^'){
                newNode = createOperatorNode(*token);
                queueEnqueue(queue, newNode);
            }
            //else if checks to see if user inputs the number 0, Creates number node of 0 and puts in queue
            else if (*token == '0'){
                newNode = createNumberNode(atof(token));
                queueEnqueue(queue, newNode);
            }
            /*If atof returns a 0 at this point then the user did not put 0 as we checked that already, so that means the user inputted something that is not a
            valid operator or number*/
            else if(atof(token) == 0){
                printf("INVALID INPUT\n");
                exit(1);
            }
            //Any other positive numbers are created into a number node and then put in queue
            else{
                newNode = createNumberNode(atof(token));
                queueEnqueue(queue, newNode);
            }
            token = strtok(NULL, delimiter);
        }

        //Prints tokenized queue
        printf("\n");
        printf("Tokenized Queue: ");
        queuePrint(queue);

        //Initalize Stack and Node
        StackAsLinkedList* stack = stackInit();
        Node* operator;

        //While the queue still has elements in it start to dequeue and put it in the stack and perform operations
        while(queueIsEmpty(queue)!=true){
            //If the queue is size 1 and stack is 0 then no operations are needed
            if (queueSize(queue) == 1 && stackSize(stack) == 0){
                //If its a number then just dequeue and push the number to the stack
                if (queue->head->type == REAL_NUMBER){
                    stackPush(stack, queueDequeue(queue));
                }
                //If its an operator then its invalid so print error message and exit
                else{
                    printf("EXPRESSION INVALID\n");
                    exit(1);
                }
                
            }
            //If the queue has 2 inputs and the stack is empty then no matter the inputs the RPN expression is invalid
            else if (queueSize(queue) == 2 && stackSize(stack) == 0){
                printf("EXPRESSION INVALID\n");
                exit(1);
            }

            //After checking do all other operations
            else{
                //Function queueToStack dequeues and pushes dequeued number to stack and stops once a math operator is reached - dequeues it and returns that math operator
                operator = createOperatorNode(*(char*)queueToStack(queue, stack)->data);
                //Printing intermediate steps
                printf(" Operator: \'%c\' | Stack Before Operation: ",*(char*)operator->data);
                stackPrint(stack);
                //Performs the operation
                doOperator(operator, stack);
            }
            
        }
        //If stack at the end has more than 1 element then something went wrong and expression is invalid
        if (stackSize(stack) != 1){
            printf("EXPRESSION INVALID\n");
            exit(1);
        }
        printf("Final Answer: %.3lf\n\n", *(double*)stack->head->data);

    }
}