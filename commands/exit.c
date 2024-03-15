#include <stdio.h>
#include "../list/list.h"
#include "../pcb.h"
#include "commands.h"
#include <stdlib.h>


void exit_process(){

    bool is_init_process = false;

    printf("currently running process: %d\n", current_process->pid);

    // search for the queue that it is in
    List* target_queue = get_queue(current_process->pid);

    if (target_queue != NULL){
        PCB* removed_proc = List_remove(target_queue);
        if (removed_proc->pid == init_process_pid){
            is_init_process = true;
        }
        printf("Process %d has been successfully exited.\n", removed_proc->pid);
        free_PCB(current_process);
        current_process = NULL;
    } else {
        printf("Process %d is not in any queue. Failed to exit process.\n", current_process->pid);
    }

    // print_all_queues();

    // if all queues are empty, exit the program
    if (is_init_process){
        printf("Init process has been exited. Exiting the program.\n");
        // call cleanup
        // exit(0);
    }
}