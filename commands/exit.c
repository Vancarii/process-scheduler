#include <stdio.h>
#include "../list/list.h"
#include "../pcb.h"
#include "commands.h"
#include <stdlib.h>
#include <string.h>


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

    // // check if there are any incoming messages
    // if (current_process->proc_messages[0] != '\0'){
    //     char y_n[2];
    //     printf("\033[0;33m");
    //     printf("PROCESS HAS INCOMING MESSAGES. ARE YOU SURE YOU WANT TO EXIT? (Y/N): ");
    //     printf("\033[0;0m");

    //     // size of 2 since 1 integer is expected plus null termination
    //     if (fgets(y_n, 2, stdin) == NULL) {
    //         puts("invalid input\n");
    //     }

    //     if (strcmp(y_n, "N") == 0){
    //         return;
    //     }

    // }

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

            printf("Process %d has been successfully exited.\n", removed_proc->pid);
            free_PCB(removed_proc);

            current_process = find_next_process();

        }

    }
}