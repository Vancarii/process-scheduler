#include <stdio.h>
#include "../list/list.h"
#include "../pcb.h"
#include "commands.h"

// #include <string.h>
#include <stdlib.h>

bool find_pid(void* curr_PCB, void* comparisonArg) {
    PCB* pcb = curr_PCB;
    int* pid = (int*)comparisonArg;
    // printf("Comparing %d to %d\n", pcb->pid, *pid);
    if (pcb->pid == *pid) {
        return 1;
    }
    return 0;
}


// kill the named process and remove it from the system.
// reports action taken as well as success or failure
void kill_process(char* pid_c) {

    List* target_queue;
    // print_all_queues();

    // make list point to first element of the ready queue
    List_first(ready_queue[0]);
    List_first(ready_queue[1]);
    List_first(ready_queue[2]);
    List_first(waiting_reply_queue);
    List_first(waiting_receive_queue);


    // need to loop through all queues to find the process to kill
    // if the process is found, remove it from the queue and free the memory
    // if the process is not found, print an error message
    // use list_search

    int pid = atoi(pid_c);

    // search through all ready queues to find the process to kill
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

    if (found_process != NULL) {
        PCB* removed_proc = List_remove(target_queue);
        free_PCB(removed_proc);
        printf("Process %d has been killed.\n", pid);
        // return;
    }

    else {
        printf("Process %d not found.\n", pid);
        // return;
    }

    // print_all_queues();

    return;

}