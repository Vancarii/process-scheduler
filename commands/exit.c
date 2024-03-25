#include <stdio.h>
#include "../list/list.h"
#include "../pcb.h"
#include "commands.h"
#include <stdlib.h>


void exit_process(){

    printf("currently running process pid: %d\n", current_process->pid);

    // check if target is init process
    // if it is, then that means there are no other processes
    // check if there are any blocked processes
    // if not, cleanup and exit program

    // else if there are blocked processes ,
    // throw error that cannot exit yet

    //else if not init process
    // find the process and queue that current process is in
    // remove it from the queue
    // free the process

    if (current_process == init_process){
              
        // checks to see if there are no processes at all in the simulation
        for (int i = 0; i < 5; i++) {
            if (semaphores[i].waited_processes != NULL &&
                        semaphores[i].waited_processes->count > 0) 
            {
                printf("Semaphore %d has blocked processes. Cannot exit.\n", i);
                return;
            }
        }
        if (waiting_receive_queue->count > 0 || waiting_reply_queue->count > 0) {
            printf("Waiting receive queue has blocked processes. Cannot exit.\n");
            return;
        }


        // cleanup and exit
        free_PCB(init_process);
        printf("Init program successfully exited. Simulation now terminated.\n");
        exit(0);


    } else {

        // search for the queue that it is in
        List* target_queue = get_queue(current_process->pid);

        if (target_queue != NULL){

            PCB* removed_proc = List_remove(target_queue);

            if (removed_proc == NULL){
                printf("Could not find process. Failed to exit process.\n");
                return;
            }

            printf("Process %d has been successfully exited.\n", removed_proc->pid);
            free_PCB(removed_proc);

            current_process = find_next_process();

        }

    }
}