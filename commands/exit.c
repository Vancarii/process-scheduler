#include <stdio.h>
#include "../list/list.h"
#include "../pcb.h"
#include "commands.h"
#include <stdlib.h>


// if only process is init process, then exit causes seg fault

void exit_process(){

    printf("currently running process pid: %d\n", current_process->pid);

    // search for the queue that it is in
    List* target_queue = get_queue(current_process->pid);

    if (target_queue != NULL){

        // if the current process if the initial process then there should already
        // be no other processes in the system ideally

        // remove the process from the queue, current should already be pointing to the process
        PCB* removed_proc = List_remove(target_queue);
        // List_first(target_queue);
        // current_process = List_curr(target_queue);
        // if (current_process == NULL) {
            // find the next process to run
            // returns null if there are no other processes
            current_process = find_next_process();
            if (current_process == NULL){
                printf("No other processes in the ready queues. Running init process...\n");
                current_process = init_process;
            }
        // }

        printf("Process %d has been successfully exited.\n", removed_proc->pid);
        free_PCB(removed_proc);
    } else {
        printf("Process %d is not in any queue. Failed to exit process.\n", current_process->pid);
    }

    // // have the current process point to the next process in the queue
    // current_process = List_first(ready_queue[0]);

    // print_all_queues();

    // list is empty
    if (current_process == NULL && ready_queue[0]->count == 0) {
        printf("current process is null");
    }

    // if all queues are empty, exit the program
    // if (is_init_process){
    //     printf("Init process has been exited. Exiting the program.\n");
    //     // call cleanup
    //     // exit(0);
    // }
}