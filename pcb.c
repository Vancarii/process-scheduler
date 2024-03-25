#include "pcb.h"
#include "commands/commands.h"
#include <stdio.h>
#include <stdlib.h>


int next_avail_pid;
int init_process_pid;
PCB* current_process;

PCB* init_process;

// initialize queues
List* ready_queue[3];
List* waiting_reply_queue;
List* waiting_receive_queue;

sem semaphores[5];

// find the next process to run
// if there are no processes in any of the ready queues, make init
// process the current process
PCB* find_next_process() {
    PCB* next_process = NULL;
    for (int i = 0; i < 3; i++) {
        if (ready_queue[i]->count > 0) {
            next_process = List_first(ready_queue[i]);
            break;
        }
    }
    if (next_process == NULL){
        printf("No other processes in any of the ready queues. Running init process...\n");
        current_process = init_process;
        current_process->state = RUNNING;

        return init_process;
    } else {
        next_process->state = RUNNING;
        init_process->state = READY;
    }
    return next_process;
}

void print_process_info(PCB* pcb){
    printf("--------------------------------------------------------------------\n");
    printf("PID: %d | ", pcb->pid);
    printf("Priority: %d | ", pcb->priority);

    if (pcb->state == 0){
        printf("State: Running | ");
    } else if (pcb->state == 1){
        printf("State: Ready | ");
    } else if (pcb->state == 2){
        printf("State: Blocked | ");
    } 

    printf("Incoming Message: %s\n", pcb->proc_messages);
    printf("--------------------------------------------------------------------\n");
}

void print_all_processes() {

    printf("\ninit process:\n");
    print_process_info(init_process);

    printf("\n[current running process pid: %d]\n", current_process->pid);


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

    printf("\nWaiting Reply Queue\n");
    q_print = waiting_reply_queue;
    List_first(q_print);
    // PCB* pcb;
    while ((pcb = List_curr(q_print)) != NULL) {
        print_process_info(pcb);
        List_next(q_print);
    }

    printf("\nWaiting Recieve Queue\n");
    q_print = waiting_receive_queue;
    List_first(q_print);
    // PCB* pcb;
    while ((pcb = List_curr(q_print)) != NULL) {
        print_process_info(pcb);
        List_next(q_print);
    }

    // print all semaphore waiting lists
    for (int i = 0; i < 5; i++) {
        
        if (semaphores[i].waited_processes == NULL){
            printf("Semaphore %d has not been created.\n", i);
        } else {
            printf("\nSemaphore %d\n", i);
            q_print = semaphores[i].waited_processes;
            List_first(q_print);
            // PCB* pcb;
            while ((pcb = List_curr(q_print)) != NULL) {
                print_process_info(pcb);
                List_next(q_print);
            }

            List_first(q_print);
        }
    }

    List_first(ready_queue[0]);
    List_first(ready_queue[1]);
    List_first(ready_queue[2]);
    List_first(waiting_reply_queue);
    List_first(waiting_receive_queue);

}

// finds a queue to place process
// used when processes are unblocked, and are put back onto the ready queues
// the only difference than List_append is that we dont know which queue the process
// is going in, so we try all 3 from the highest priority until it can go in
// returns the queue it was placed in

// we have to also check if the queues are all empty, meaning the init process is running
// if so, make the process that is enqueued to start running
int enqueue_process(PCB* process) {

    // if all queues are empty, make the process the current process
    if (current_process == init_process) {
        current_process = process;
        if (List_append(ready_queue[0], process) == 0) {
            printf("Process %d is now running\n", process->pid);
            process->state = RUNNING;
            process->priority = 0;
        }

        init_process->state = READY;

        return 0;
    }

    // look for the first available queue to place the process
    for (int i = 0; i < 3; i++) {
        if (List_append(ready_queue[i], process) == 0) {
            // printf("Process %d enqueued in ready queue %d\n", process->pid, i);
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

    // initialize semaphores all to unused
    for (int i = 0; i < 5; i++){
        semaphores[i].sem = UNUSED_SEMAPHORE;
    }

    next_avail_pid = 1;

    init_process_pid = 1;

    current_process = NULL;

    for (int i = 0; i < 3; i++) {
        ready_queue[i] = List_create();
    }

    waiting_receive_queue = List_create();
    waiting_reply_queue = List_create();

    // create the initial process and save the pid
    init_process = create_PCB(0);
    init_process->pid = init_process_pid;

    current_process = init_process;
    current_process->state = RUNNING;
    // set the current running process to the initial process
    // current_process = initProcess;

    // Output the creation of the 'init' process

}
