#include "pcb.h"
#include "commands/commands.h"
#include <stdio.h>
#include <stdlib.h>


int next_avail_pid;
int init_process_pid;
PCB* current_process;

// initialize queues
List* ready_queue[3];
List* waiting_reply_queue;
List* waiting_receive_queue;

void print_all_queues() {
    List* q_print;
    PCB* pcb;
    for (int i = 0; i < 3; i++) {
        q_print = ready_queue[i];
        printf("Ready Queue %d\n", i);
        List_first(q_print);
        while ((pcb = List_curr(q_print)) != NULL) {
            printf("PID: %d, Priority: %d\n", pcb->pid, pcb->priority);
            List_next(q_print);
        }
    }
    printf("Waiting Reply Queue\n");
    q_print = waiting_reply_queue;
    List_first(q_print);
    // PCB* pcb;
    while ((pcb = List_curr(q_print)) != NULL) {
        printf("PID: %d, Priority: %d\n", pcb->pid, pcb->priority);
        List_next(q_print);
    }

    printf("Waiting Recieve Queue\n");
    q_print = waiting_receive_queue;
    List_first(q_print);
    // PCB* pcb;
    while ((pcb = List_curr(q_print)) != NULL) {
        printf("PID: %d, Priority: %d\n", pcb->pid, pcb->priority);
        List_next(q_print);
    }
}


PCB *create_PCB(int priority) {
    PCB *newPCB = (PCB *)malloc(sizeof(PCB));
    if (newPCB == NULL) {
        fprintf(stderr, "Failed to allocate memory for PCB\n");
        exit(1);
    }

    newPCB->pid = next_avail_pid++;
    newPCB->state = READY;
    newPCB->priority = priority;
    newPCB->proc_messages = ((char*) calloc(256, sizeof(char)));

    return newPCB;
}

void free_PCB(PCB* pcb) {
    free(pcb->proc_messages);
    free(pcb);
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

    next_avail_pid = 2;

    init_process_pid = 1;

    current_process = NULL;

    for (int i = 0; i < 3; i++) {
        ready_queue[i] = List_create();
    }

    waiting_receive_queue = List_create();
    waiting_reply_queue = List_create();

    PCB *initProcess = create_PCB(0); // Priority 0 for highest priority

    initProcess->pid = init_process_pid;
    initProcess->state = RUNNING;  // The 'init' process starts as running
    // initProcess->priority = 0;  // Highest priority

    // Store the init process into a queue
    
    if (List_append(ready_queue[initProcess->priority], initProcess) == -1) {
        printf("Failed to append initial process to highest ready queue\n");
        return;
    } else {
        printf("Init process created with PID %d and priority %d\n", initProcess->pid, initProcess->priority);
    }


    // set the current running process to the initial process
    current_process = initProcess;

    // Output the creation of the 'init' process

}
