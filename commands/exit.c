#include <stdio.h>
#include "../list/list.h"
#include "../pcb.h"
#include "commands.h"
#include <stdlib.h>
#include <string.h>


void exit_process(){

    // printf("currently running process pid: %d\n", current_process->pid);

    if (current_process == init_process){
              
        // checks to see if there are no processes at all in the simulation
        // queues are for sure empty since current is init process
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


        printf("Init program successfully exited. Simulation now terminated.\n");

        terminate_simulation();
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

            printf("Process %d has successfully been exited.\n", removed_proc->pid);
            free_PCB(removed_proc);

            current_process = find_next_process();

            printf("Process %d now has the CPU.\n", current_process->pid);
        }

    }
}