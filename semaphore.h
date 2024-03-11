#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include "list.h"

typedef struct {
    int semaphoreValue;
    List* waitingProcesses;
} Semaphore;


Semaphore semaphores[5];

#endif