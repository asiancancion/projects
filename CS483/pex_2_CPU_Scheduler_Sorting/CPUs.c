#include <stdio.h>
#include "CPUs.h"
#include "processQueue.h"

void* FIFOcpu (void* param){
    //helper variables for casting param and accessing svars
    cpuParams* params = (cpuParams*) param;
    sharedVars* svars = params->svars;
    process* nextProcess = NULL;
    while(true){
        sem_wait(&(svars->cpuSems[params->threadNumber])); // wait to be signalled

        

        if (nextProcess == NULL){
            pthread_mutex_lock(&(svars->readyQLock)); //lock mutex
            
            nextProcess = Qremove(&(svars->readyQ), 0); // get next process
            if (nextProcess != NULL){//if nextProcess is NULL don't print scheduling PID
                printf("Scheduling PID %d\n", nextProcess->PID); //print process ID
            }
            
            
            pthread_mutex_unlock(&(svars->readyQLock)); //unlock mutex
            

        }
        if(nextProcess != NULL){
            nextProcess->burstRemaining -=1; // reduce burst by 1
            if(nextProcess->burstRemaining == 0){ //if burst is 0 then put in finished queue
                pthread_mutex_lock(&(svars->finishedQLock)); //lock finished mutex
                Qinsert(&(svars->finishedQ), nextProcess); //insert into finished queue
                pthread_mutex_unlock(&(svars->finishedQLock)); //unlock finished mutex
                nextProcess = NULL; //set nextProcess back to NULL
            }
        }

        sem_post(&(svars->mainSem));

    }
    

}

void* SJFcpu (void* param){
    //helper variables
	cpuParams* params = (cpuParams*) param;
    sharedVars* svars = params->svars;
    process* nextProcess = NULL;
    while(true){
        sem_wait(&(svars->cpuSems[params->threadNumber])); // wait to be signalled

        

        if (nextProcess == NULL){
            pthread_mutex_lock(&(svars->readyQLock)); //lock mutex
            
            nextProcess = QremoveShortest(&(svars->readyQ)); // get next process
            if(nextProcess!= NULL){//if nextProcess is NULL don't print scheduling PID
                printf("Scheduling PID %d\n", nextProcess->PID); //print process ID
            }
            
            
            pthread_mutex_unlock(&(svars->readyQLock)); //unlock mutex
            

        }
        if(nextProcess != NULL){
            nextProcess->burstRemaining -=1; // reduce burst by 1
            if(nextProcess->burstRemaining == 0){ //if burst is 0 then put in finished queue
                pthread_mutex_lock(&(svars->finishedQLock)); //lock finished mutex
                Qinsert(&(svars->finishedQ), nextProcess); //insert into finished queue
                pthread_mutex_unlock(&(svars->finishedQLock)); //unlock finished mutex
                nextProcess = NULL; //set nextProcess back to NULL
            }
        }

        sem_post(&(svars->mainSem));

    }

    
}

void* NPPcpu (void* param){
    //helper variables
	cpuParams* params = (cpuParams*) param;
    sharedVars* svars = params->svars;
    process* nextProcess = NULL;
    while(true){
        sem_wait(&(svars->cpuSems[params->threadNumber])); // wait to be signalled

        if (nextProcess == NULL){
            pthread_mutex_lock(&(svars->readyQLock)); //lock mutex
            
            nextProcess = QremovePriority(&(svars->readyQ)); // get next process
            if (nextProcess != NULL){//if nextProcess is NULL don't print scheduling PID
                printf("Scheduling PID %d\n", nextProcess->PID); //print process ID
            }
            
            pthread_mutex_unlock(&(svars->readyQLock)); //unlock mutex
            

        }
        if(nextProcess != NULL){
            nextProcess->burstRemaining -=1; // reduce burst by 1
            if(nextProcess->burstRemaining == 0){ //if burst is 0 then put in finished queue
                pthread_mutex_lock(&(svars->finishedQLock)); //lock finished mutex
                Qinsert(&(svars->finishedQ), nextProcess); //insert into finished queue
                pthread_mutex_unlock(&(svars->finishedQLock)); //unlock finished mutex
                nextProcess = NULL;
            }
        }

        sem_post(&(svars->mainSem));

    }
}

void* RRcpu (void* param){
    //helper variables
    cpuParams* params = (cpuParams*) param;
    sharedVars* svars = params->svars;
    process* nextProcess = NULL;
    int timeOnProcess = 0; //time on process to see if we surpass the quantum
    while(true){
        sem_wait(&(svars->cpuSems[params->threadNumber])); // wait to be signalled

        if (timeOnProcess == svars->quantum){//if we reach the quantum
            pthread_mutex_lock(&(svars->readyQLock)); //lock mutex
            nextProcess->requeued = true;//set requeued flag to true
            Qinsert(&(svars->readyQ), nextProcess); // insert expired process into readyQueue
            nextProcess=Qremove(&(svars->readyQ),0);//remove the next process
            if (nextProcess != NULL){//if nextProcess is NULL don't print scheduling PID
                printf("Scheduling PID %d\n", nextProcess->PID); //print process ID
            }
            pthread_mutex_unlock(&(svars->readyQLock)); //unlock mutex
            timeOnProcess = 0;//set timeOnProcess to 0 to reset it
        }

        if (nextProcess == NULL){
            pthread_mutex_lock(&(svars->readyQLock)); //lock mutex
            
            nextProcess = Qremove(&(svars->readyQ),0); // get next process
            if (nextProcess != NULL){//if nextProcess is NULL don't print scheduling PID
                printf("Scheduling PID %d\n", nextProcess->PID); //print process ID
            }
            
            pthread_mutex_unlock(&(svars->readyQLock)); //unlock mutex

        }       

        if(nextProcess != NULL){
            nextProcess->burstRemaining -= 1; // reduce burst by quantum
            timeOnProcess +=1; //increase timeOnProcess by 1
            if(nextProcess->burstRemaining <= 0){ //if burst is <0 then put in finished queue
                pthread_mutex_lock(&(svars->finishedQLock)); //lock finished mutex
                Qinsert(&(svars->finishedQ), nextProcess); //insert into finished queue
                pthread_mutex_unlock(&(svars->finishedQLock)); //unlock finished mutex
                nextProcess = NULL;
                timeOnProcess = 0; //set time on process to 0 if nextProcess is done
            }
        }

        sem_post(&(svars->mainSem));

    }
}



void* SRTFcpu (void* param){
    //helper variables
	cpuParams* params = (cpuParams*) param;
    sharedVars* svars = params->svars;
    process* nextProcess = NULL;
    node* lastProcess = NULL; //last process to see what is the last one on tail
    int compareTime; //compareTime to compare jobs to
    while(true){
        sem_wait(&(svars->cpuSems[params->threadNumber])); // wait to be signalled

        if (nextProcess == NULL){
            pthread_mutex_lock(&(svars->readyQLock)); //lock mutex
            
            nextProcess = QremoveShortest(&(svars->readyQ)); // get next process
            if (nextProcess != NULL){//if nextProcess is NULL don't print scheduling PID
                printf("Scheduling PID %d\n", nextProcess->PID); //print process ID
            }
            lastProcess = svars->readyQ.tail;//set lastProcess to the tail
            pthread_mutex_unlock(&(svars->readyQLock)); //unlock mutex
            

        }
        if (lastProcess != svars->readyQ.tail){//if a new process is enqueued it will make the tail different
            pthread_mutex_lock(&(svars->readyQLock)); //lock mutex
            compareTime = svars->readyQ.tail->data->burstRemaining;//find burstRemanining of new Enqueued process
            if (compareTime < nextProcess->burstRemaining){ //if burstRemaining is lower requeue current process and select that process
                nextProcess->requeued = true;//set requeued flag to true
                Qinsert(&(svars->readyQ), nextProcess);//insert old process back into readyQ
                nextProcess = QremoveShortest(&(svars->readyQ));//remove the next shortest queue which will be the new process
                if (nextProcess != NULL){//if nextProcess is NULL don't print scheduling PID
                printf("Scheduling PID %d\n", nextProcess->PID); //print process ID
            }
            }
            pthread_mutex_unlock(&(svars->readyQLock)); //unlock mutex

        }
        if(nextProcess != NULL){
            nextProcess->burstRemaining -=1; // reduce burst by 1
            if(nextProcess->burstRemaining == 0){ //if burst is 0 then put in finished queue
                pthread_mutex_lock(&(svars->finishedQLock)); //lock finished mutex
                Qinsert(&(svars->finishedQ), nextProcess); //insert into finished queue
                pthread_mutex_unlock(&(svars->finishedQLock)); //unlock finished mutex
                nextProcess = NULL;
            }
        }

        sem_post(&(svars->mainSem));

    }
}




void* PPcpu (void* param){
    //helper variables
	cpuParams* params = (cpuParams*) param;
    sharedVars* svars = params->svars;
    process* nextProcess = NULL;
    node* lastProcess = NULL;//last process to see what is the last one on tail
    int priority;//priority to compare to
    while(true){
        sem_wait(&(svars->cpuSems[params->threadNumber])); // wait to be signalled

        if (nextProcess == NULL){
            pthread_mutex_lock(&(svars->readyQLock)); //lock mutex
            
            nextProcess = QremovePriority(&(svars->readyQ)); // get next process
            if (nextProcess != NULL){
                printf("Scheduling PID %d\n", nextProcess->PID); //print process ID
            }
            lastProcess = svars->readyQ.tail;
            pthread_mutex_unlock(&(svars->readyQLock)); //unlock mutex
            

        }
        if (lastProcess != svars->readyQ.tail){//if a new process is enqueued
            pthread_mutex_lock(&(svars->readyQLock)); //lock mutex
            priority = svars->readyQ.tail->data->priority;//find priority of new Enqueued process
            if (priority < nextProcess->priority){ //if priority is lower requeue current process and select that process
                nextProcess->requeued = true;//if process is preempted set requeue flag to true
                Qinsert(&(svars->readyQ), nextProcess); //insert preempted process back into queue
                nextProcess = QremovePriority(&(svars->readyQ)); //Dequeue next process that has best priority
                if (nextProcess != NULL){
                    printf("Scheduling PID %d\n", nextProcess->PID); //print process ID
                }
            }
            pthread_mutex_unlock(&(svars->readyQLock)); //unlock mutex

        }
        if(nextProcess != NULL){
            nextProcess->burstRemaining -=1; // reduce burst by 1
            if(nextProcess->burstRemaining == 0){ //if burst is 0 then put in finished queue
                pthread_mutex_lock(&(svars->finishedQLock)); //lock finished mutex
                Qinsert(&(svars->finishedQ), nextProcess); //insert into finished queue
                pthread_mutex_unlock(&(svars->finishedQLock)); //unlock finished mutex
                nextProcess = NULL;//set nextProcess to NULL
            }
        }

        sem_post(&(svars->mainSem));

    }

    
}