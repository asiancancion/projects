/*=============================================================================
 |   Assignment:  PEX1
 |       Author: Caleb Song
 |      Section: M6
 |        Class:  CS483
 +-----------------------------------------------------------------------------
 |   Description:  Air Force Shell.. In-built and external command shell
 |
 |   Required Features Not Included:  None
 |
 |   Known Bugs:  None
 +-----------------------------------------------------------------------------
 |   Documentation Statement:  historyList.c had some portions taken from linkedList implementations from CS220 class. EI from 
                               Lt Col Hancok on 2/16. Used the code examples from lesson 5 to do the external commands. Used in class
                               notes and hints on course announcements/. Got this line to strip \n str[strcspn(str, "\n")] = 0 from geeks
                               for geeks.
 *===========================================================================*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "historyList.h"

int main() {
    //current working directory path stored here
    char cwd[256];
    //user inputted commands
    char str[100];
    //delimiter takes in spaces, tabs, new line
    char delimiter[5] = " \n \t";
    //stores token here
    char* token;
    //while user does not input exit valid stays true and loops
    bool valid = true;
    //Linkedlist for history command
    HistoryNodeType* head = NULL;
    //counter variable to count how many functions have been inserted
    int* counter;
    *counter = 0;
    //print out header AFshell
    printf("...Air Force Shell (afsh)...\n");

    //Loops infinetely until user inputs invalid input or null string
    while(valid == true){
        //prints the current working directory
        printf("@f$h%s>",getcwd(cwd,sizeof(cwd)));
        //get user input store in str
        fgets(str,100,stdin);
        ///strip the \\n from the variable
        str[strcspn(str, "\n")] = 0; 
        //remove if duplicate command and pass in pointer to counter which will decreas by 1 if command is duplicate
        head = listRemove(head,str, counter);
        //insert new command at tail of list
        head = listInsertTail(head,str);
        //increase counter by 1
        *counter+=1;
        //tokenize input
        token = strtok(str, delimiter);

        //Recall command: recalls command, prints to console and executes it
        if (strncmp(token, "recall", 6) == 0){
            token = strtok(NULL, delimiter);
            //if token is NULL then recall cannot be called
            if (token == NULL){
                perror("Not enough arguments");
                token = NULL;
            }
            else{
                //convert token to int
                int command = atoi(token);
                //if command requested is greater than commands in history then it is out of range
                if (command >= *counter){
                    perror("Out of range");
                    token = NULL;
                }
                //if command is in range then print the command and store the command as the next token
                else{
                    strcpy(str,listGet(head,command));
                    printf("%s\n", str);
                    token = strtok(str, delimiter);
                }
                
            }
            
        }
        
        //if token is NULL it is because user inputted wrong command 
        if (token == NULL){
            continue;
        }
        //Exit Command: User inputs exit, exits program
        else if(strncmp(token,"exit",4) == 0){
            //prints Goodbye! to user
            printf("Goodbye!\n");
            //frees linked list
            listDestroy(head);
            exit(0);
        }
        //cd Command: user inputs cd and directory, changes directory
        else if(strncmp(token, "cd", 2) == 0){
            token = strtok(NULL, delimiter);
            //if token is NULL did not put a valid directory
            if (token == NULL){
                perror("directory not found");
            }
            //if user entered ~ then go to home directory
            else if (strncmp(token,"~",1) == 0){
                chdir(getenv("HOME"));
            }
            //else go to directory user inputted after cd
            else{
                chdir(token);
            }
            
        }
        //History function, if user inputs a number after history prints a certain amount of commands, if user does not
        //input number prints history of all commands
        else if(strncmp(token,"history",7) == 0){
            token = strtok(NULL, delimiter);
            //if token is NULL print out whole history of commands
            if (token == NULL){
                listPrint(head);
            }
            else{
                //convert tokenized input to int
                int num = atoi(token);
                //if number is greater than the counter then it is an invalid range
                if (num > *counter){
                    perror("Out of Range");
                }
                //else print out the number of the commands inputted
                else{
                    for (int i = 1; i < num+1; i++){
                    printf("%d ", i);
                    listPrintN(head,i);
                    }
                }
                
            }
        }
        
        //Non-built in commands - uses child process to execute non-built in functions
        else{
            //fork
            pid_t pid = fork();

            if (pid == -1) {
                // Fork failed
                perror("fork");
                return 1;
            } else if (pid == 0) {
                // Replace the child process with the user inputted command program
                char *tokenArray[100];
                int counterTok = 1;
                fflush(stdout);
                //set first thing in tokenArray to token
                tokenArray[0] = token;

                while(token != NULL){
                    //get tokens and put them in token array
                    token = strtok(NULL, delimiter);
                    tokenArray[counterTok] = token;
                    //increase the counterTok by 1 to track number of commands in array
                    counterTok+=1;
                }
                //set last element in token array to NULL
                tokenArray[counterTok] = NULL;
                //execute command
                execvp(tokenArray[0], tokenArray);

                // execl only returns if there is an error
                perror("execvp");
                return 1;
            } else {
                // Wait for the child process to complete
                waitpid(pid, NULL, 0);
            }
        }    
    }
}