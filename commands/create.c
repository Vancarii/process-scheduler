#include "create.h"
#include <stdio.h>

#include "../pcb.h"

#include <stdlib.h>

#include "../pcb.h"

void create_process(char* command, char* params){

    // char params[2];

    // printf("Priority (0 = high ; 1 = normal ; 2 = low): ");

    // // size of 2 since 1 integer is expected plus null termination
    // if (fgets(params, 2, stdin) == NULL) {
    // // Handle error or end-of-file
    // }

    int c;  
    while ((c = getchar()) != '\n' && c != EOF) { }
    
    int priority = atoi(params);

    if (priority < 0 || priority > 2) {
        printf("Invalid priority. Process creation failed.\n");
        return;
    }


    // if (priority == 0) {
    //     printf("Priority is high\n");
    // } else if (priority == 1) {
    //     printf("Priority is norm\n");
    // } else if (priority == 2) {
    //     printf("Priority is low\n");
    // }


    PCB* new_pcb = create_PCB(priority);

    // enqueue to the list

    if (List_append(ready_queue[priority], new_pcb) == -1) {
        printf("Failed to append process %d to ready queue with priority %d\n", new_pcb->pid, new_pcb->priority);
        return;
    } else {
        printf("Process created with PID %d and priority %d\n", new_pcb->pid, new_pcb->priority);
    }

    printf("ready queue [%d] count: %d\n", new_pcb->priority, ready_queue[priority]->count);

}