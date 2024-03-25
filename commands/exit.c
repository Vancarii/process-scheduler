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


//     // search for the queue that it is in
//     List* target_queue = get_queue(current_process->pid);

//     if (target_queue != NULL){

//         // if the current process if the initial process then there should already
//         // be no other processes in the system ideally

//         // remove the process from the queue, current should already be pointing to the process
//         PCB* removed_proc = List_remove(target_queue);

//         // find the next process to run
//         // returns null if there are no other processes
//         current_process = find_next_process();
//         if (current_process == NULL){
//             printf("No other processes in the ready queues. Running init process...\n");
//             current_process = init_process;
//         }
        

//         printf("Process %d has been successfully exited.\n", removed_proc->pid);
//         free_PCB(removed_proc);
//     } else {
//         printf("Process %d is not in any queue. Failed to exit process.\n", current_process->pid);
//     }

//     // // have the current process point to the next process in the queue
//     // current_process = List_first(ready_queue[0]);

//     // print_all_queues();

//     // list is empty
//     if (current_process == NULL && ready_queue[0]->count == 0) {
//         printf("current process is null");
//     }

//     // if all queues are empty, exit the program
//     // if (is_init_process){
//     //     printf("Init process has been exited. Exiting the program.\n");
//     //     // call cleanup
//     //     // exit(0);
//     // }
// }