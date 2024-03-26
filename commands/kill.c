#include <stdio.h>
#include "../list/list.h"
#include "../pcb.h"
#include "commands.h"
#include <stdlib.h>


// kill the named process and remove it from the system.
// reports action taken as well as success or failure
void kill_process(char* pid_c) {

    int pid = atoi(pid_c);

    // check if target is init process
    if (pid == init_process_pid) {
        // printf("Initial process pid entered.\n");
        // check if all queues are empty
        current_process = find_next_process();
        if (current_process == init_process){
            
            // checks to see if there are no processes at all in the simulation
            for (int i = 0; i < 5; i++) {
                if (semaphores[i].waited_processes != NULL &&
                            semaphores[i].waited_processes->count > 0) 
                {
                    printf("Semaphore %d has blocked processes. Cannot terminate simulation.\n", i);
                    return;
                }
            }

            if (waiting_receive_queue->count > 0 || waiting_reply_queue->count > 0) {
                printf("Queues have blocked processes. Cannot terminate simulation.\n");
                return;
            }

            printf("All ready queues are empty. Initial Process successfully killed. Simulation terminated.\n");

            terminate_simulation();
            exit(0);
        } else {
            printf("Ready queues not empty, cannot kill init process yet.\n");
            return;
        }

    }
    // target is not init process
    else {
        // queues current pointer should already be pointing at the target process
        List* target_queue = get_queue(pid);

        if (target_queue == NULL){
            printf("Process %d not found. Failed to kill process.\n", pid);
            return;
        }


        PCB* removed_proc = List_remove(target_queue);

        if (removed_proc == NULL) {
            printf("Process %d not found. Failed to kill process.\n", pid);
            return;
        }

        current_process = find_next_process();

        free_PCB(removed_proc);

        printf("Process %d has successfully been killed.\n", pid);

    }

    return;

}