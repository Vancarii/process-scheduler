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

// find the next process to run
// if there are no processes in any of the ready queues, return NULL
PCB* find_next_process() {
    PCB* next_process = NULL;
    for (int i = 0; i < 3; i++) {
        if (ready_queue[i]->count > 0) {
            next_process = List_first(ready_queue[i]);
            break;
        }
    }
    if (next_process == NULL){
        printf("No processes in any of the ready queues\n");
        return NULL;
    } else {
        next_process->state = RUNNING;
    }
    return next_process;
}

static void print_process_info(PCB* pcb){
    printf("________________________\n");
    printf("PID: %d\n", pcb->pid);
    printf("Priority: %d\n", pcb->priority);

    if (pcb->state == 0){
        printf("State: Running\n");
    } else if (pcb->state == 1){
        printf("State: Ready\n");
    } else if (pcb->state == 2){
        printf("State: Blocked\n");
    } else {
        printf("State: Unknown\n");
    }
    printf("Message: %s\n", pcb->proc_messages);
    printf("________________________\n\n");
}

void print_all_processes() {
    List* q_print;
    PCB* pcb;
    for (int i = 0; i < 3; i++) {
        q_print = ready_queue[i];
        printf("\nReady Queue %d\n", i);
        List_first(q_print);
        while ((pcb = List_curr(q_print)) != NULL) {
            // printf("PID: %d, Priority: %d\n", pcb->pid, pcb->priority);
            print_process_info(pcb);
            
            List_next(q_print);
        }
    }

    printf("Waiting Reply Queue\n");
    q_print = waiting_reply_queue;
    List_first(q_print);
    // PCB* pcb;
    while ((pcb = List_curr(q_print)) != NULL) {
        print_process_info(pcb);
        List_next(q_print);
    }

    printf("Waiting Recieve Queue\n");
    q_print = waiting_receive_queue;
    List_first(q_print);
    // PCB* pcb;
    while ((pcb = List_curr(q_print)) != NULL) {
        print_process_info(pcb);
        List_next(q_print);
    }

    List_first(ready_queue[0]);
    List_first(ready_queue[1]);
    List_first(ready_queue[2]);
    List_first(waiting_reply_queue);
    List_first(waiting_receive_queue);
}

int enqueue_process(PCB* process) {

    for (int i = 0; i < 3; i++) {
        if (List_append(ready_queue[i], process) == 0) {
            printf("Process %d enqueued in ready queue %d\n", process->pid, i);
            process->state = READY;
            process->priority = i;
            return i;
        }
    }

    printf("Failed to enqueue process %d in any ready queue\n", process->pid);

    return -1;

}

bool find_pid(void* curr_PCB, void* comparisonArg) {
    PCB* pcb = curr_PCB;
    int* pid = (int*)comparisonArg;
    // printf("Comparing %d to %d\n", pcb->pid, *pid);
    if (pcb->pid == *pid) {
        return 1;
    }
    return 0;
}

List* get_queue(int pid) {

    List* target_queue;

    // make list point to first element of the queue
    List_first(ready_queue[0]);
    List_first(ready_queue[1]);
    List_first(ready_queue[2]);
    List_first(waiting_reply_queue);
    List_first(waiting_receive_queue);


    // need to loop through all queues to find the process to kill
    // if the process is found, remove it from the queue and free the memory
    // if the process is not found, print an error message
    // use list_search

    // int pid = atoi(pid_c);

     // search through all ready queues to find the process
    PCB* found_process = NULL;

    int i = 0;
    while (found_process == NULL && i < 3){
        found_process = List_search(ready_queue[i], find_pid, &pid);
        target_queue = ready_queue[i];
        i++;
    }

    // if the process is not found in the ready queue, search through the waiting queues
    if (found_process == NULL){
        found_process = List_search(waiting_reply_queue, find_pid, &pid);
        target_queue = waiting_reply_queue;
    } 
    if (found_process == NULL){
        found_process = List_search(waiting_receive_queue, find_pid, &pid);
        target_queue = waiting_receive_queue;
    }

    if (found_process != NULL){
        return target_queue;
    }

    return NULL;

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
    newPCB->proc_messages = ((char*) malloc(41 * sizeof(char)));
    if (newPCB->proc_messages == NULL) {
        fprintf(stderr, "Failed to allocate memory for PCB messages\n");
        exit(1);
    }

    newPCB->proc_messages[0] = '\0';

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

    next_avail_pid = 1;

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
