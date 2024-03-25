#include "commands.h"
#include <stdio.h>
#include "../pcb.h"
#include <stdlib.h>


void proc_info_command(char* pid_c) {

    int pid = atoi(pid_c);

    if (pid == init_process_pid){
        printf("Process with PID %d is the init process\n", pid);
        print_process_info(init_process);
        return;
    }

    PCB* found_process = NULL;

    List* target_queue = get_queue(pid);

    if (target_queue == NULL){
        printf("Process with PID %d not found\n", pid);
        return;
    } else if ((found_process = List_curr(target_queue)) == NULL){
        printf("Process with PID %d not found\n", pid);
    } else {
        print_process_info(found_process);
    }

}