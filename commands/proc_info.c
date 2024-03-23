#include "commands.h"
#include <stdio.h>
#include "../pcb.h"
#include <stdlib.h>


void proc_info_command(char* pid_c) {

    int pid = atoi(pid_c);

    PCB* found_process = NULL;

    List* target_queue = get_queue(pid);

    if (target_queue == NULL){
        printf("Process with PID %d not found\n", pid);
        return;
    } else if ((found_process = List_curr(target_queue)) == NULL){
        printf("Process with PID %d not found\n", pid);
    } else {
        printf("\nPID: %d\n", pid);
        printf("Priority: %d\n", found_process->priority);

        if (found_process->state == 0){
            printf("State: Running\n");
        } else if (found_process->state == 1){
            printf("State: Ready\n");
        } else if (found_process->state == 2){
            printf("State: Blocked\n");
        } else {
            printf("State: Unknown\n");
        }
    }

}