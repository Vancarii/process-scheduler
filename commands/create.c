#include "commands.h"
#include <stdio.h>

#include "../pcb.h"

#include <stdlib.h>

// we will be adding processes to the front of the list and 
// removing processes from the end of the list
// this way we can use List_prepend with List_last and List_trim easily
// and the List_curr pointer will point to the last item, being the current running process
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
        current_process = find_next_process();
        printf("Process created with PID [%d] and priority %d\n", new_pcb->pid, new_pcb->priority);
    }

    printf("ready queue [%d] count: %d\n", new_pcb->priority, ready_queue[priority]->count);

}