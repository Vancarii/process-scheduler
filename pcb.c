#include "pcb.h"
#include "commands/create.h"
#include <stdio.h>

PCB *create_PCB(int priority) {
    PCB *newPCB = (PCB *)malloc(sizeof(PCB));
    if (newPCB == NULL) {
        fprintf(stderr, "Failed to allocate memory for PCB\n");
        exit(1);
    }

    newPCB->pid = next_avail_pid++;
    newPCB->state = READY;
    newPCB->priority = priority;
    // Initialize other attributes as necessary

    return newPCB;
}

void pcb_init_process(){

    PCB *initProcess = createPCB(0); // Priority 0 for highest priority

    initProcess->pid = next_avail_pid++;
    initProcess->state = RUNNING;  // The 'init' process starts as running
    initProcess->priority = 0;  // Highest priority

    // Store the init process into a queue

    // Output the creation of the 'init' process
    printf("Init process created with PID %d and priority %d\n", initProcess->pid, initProcess->priority);

}
