#include <stdio.h>
#include "../list/list.h"
#include "../pcb.h"
#include "commands.h"
#include <stdlib.h>



// kill the named process and remove it from the system.
// reports action taken as well as success or failure
void kill_process(char* pid_c) {

    // List* target_queue;
    // print_all_queues();

    // make list point to first element of the ready queue
    // List_first(ready_queue[0]);
    // List_first(ready_queue[1]);
    // List_first(ready_queue[2]);
    // List_first(waiting_reply_queue);
    // List_first(waiting_receive_queue);


    // need to loop through all queues to find the process to kill
    // if the process is found, remove it from the queue and free the memory
    // if the process is not found, print an error message
    // use list_search

    // int pid = atoi(pid_c);

    // // search through all ready queues to find the process to kill
    // PCB* found_process = NULL;

    // int i = 0;
    // while (found_process == NULL && i < 3){
    //     found_process = List_search(ready_queue[i], find_pid, &pid);
    //     target_queue = ready_queue[i];
    //     i++;
    // }

    // // if the process is not found in the ready queue, search through the waiting queues
    // if (found_process == NULL){
    //     found_process = List_search(waiting_reply_queue, find_pid, &pid);
    //     target_queue = waiting_reply_queue;
    // } 
    // if (found_process == NULL){
    //     found_process = List_search(waiting_receive_queue, find_pid, &pid);
    //     target_queue = waiting_receive_queue;
    // }

    int pid = atoi(pid_c);

    // queues current pointer should already be pointing at the target process
    List* target_queue = get_queue(pid);


    if (target_queue != NULL) {
        PCB* removed_proc = List_remove(target_queue);
        // sets the queues curr pointer to the start of the list
        current_process = find_next_process();
        free_PCB(removed_proc);

        // check for init
        if (pid == 1) {
            printf("Initial process pid entered.\n");
            //CHECK FOR IF ALL QUEUES ARE EMPTY
            if (current_process == NULL){
                printf("All ready queues are empty. Initial Process killed. Simulation terminated.\n");
                // cleanup
                exit(0);
            }
            return;
        }
        printf("Process %d has been successfully killed.\n", pid);
        // return;
    } else {
        printf("Process %d not found. Failed to kill process.\n", pid);
        // return;
    }

    // print_all_queues();

    return;

}