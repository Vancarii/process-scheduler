#include "commands.h"
#include <stdio.h>
#include "../pcb.h"
#include <stdlib.h>


void create_process(char* params){

    int c;  
    while ((c = getchar()) != '\n' && c != EOF) { }
    
    int priority = atoi(params);

    if (priority < 0 || priority > 2) {
        printf("Invalid priority. Process creation failed.\n");
        return;
    }

    PCB* new_pcb = create_PCB(priority);

    // enqueue to the end of the list
    if (List_append(ready_queue[priority], new_pcb) == -1) {
        printf("Failed to append process %d to ready queue with priority %d\n", new_pcb->pid, new_pcb->priority);
        return;
    } else {
        // means theres no process in the queues, so make this new process run
        // else dont do anything and let current process run
        if (current_process == init_process){
            current_process = find_next_process();
        }
        printf("\nProcess successfully created with PID [%d]\n", new_pcb->pid);
        print_process_info(new_pcb);
    }

}