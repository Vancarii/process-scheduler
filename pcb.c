#include "pcb.h"
#include "commands/create.h"
#include <stdio.h>
#include <stdlib.h>


int next_avail_pid;

// initialize queues
List* ready_queue[3];
List* waiting_reply_queue;
List* waiting_receive_queue;


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


// There is also a special init process that exists as long as the simulation is running.
// - init process only runs when no other processes are ready to execute (i.e. all ready queues are
// empty)
// - init process can do anything other processes can do, but it never blocks (must deal with it as a
// special case for send/receive and semaphores)
// - init process cannot be killed or exited unless it is the last process in the system (i.e. no processes
// on any ready queue or any blocked queue)
// - once init process is killed/exited the simulation terminates
void pcb_init_process(){

    PCB *initProcess = create_PCB(0); // Priority 0 for highest priority

    initProcess->pid = next_avail_pid++;
    initProcess->state = RUNNING;  // The 'init' process starts as running
    initProcess->priority = 0;  // Highest priority

    // Store the init process into a queue
    List_append(ready_queue[initProcess->priority], initProcess);

    // Output the creation of the 'init' process
    printf("Init process created with PID %d and priority %d\n", initProcess->pid, initProcess->priority);

}
