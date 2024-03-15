#include "commands.h"
#include <stdio.h>
#include "../pcb.h"
#include <stdlib.h>



void proc_info_command(char* pid_c) {

    int pid = atoi(pid_c);

    PCB* found_process = NULL;

    List* target_queue = get_queue(pid);
    found_process = List_curr(target_queue);

    if (found_process == NULL){
        printf("Process with PID %d not found\n", pid);
    } else {
        printf("Process with PID %d found\n", pid);
        printf("Priority: %d\n", found_process->priority);
        printf("State: %d\n", found_process->state);
    }

}