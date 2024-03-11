#include "create.h"
#include <stdio.h>

#include "../pcb.h"


void create_process(char command){

    char params[2];

    printf("Priority (0 = high ; 1 = normal ; 2 = low): ");

    // size of 2 since 1 integer is expected plus null termination
    if (fgets(params, 2, stdin) == NULL) {
    // Handle error or end-of-file
    }

    int c;  
    while ((c = getchar()) != '\n' && c != EOF) { }

    if (strcmp(params, "0") == 0) {
        printf("Priority is high\n");
    } else if (strcmp(params, "1") == 0) {
        printf("Priority is norm\n");
    } else if (strcmp(params, "2") == 0) {
        printf("Priority is low\n");
    }

    PCB* new_pcb = create_PCB(params);

    // enqueue to the list

}