#include "commands.h"
#include <stdio.h>
#include "../pcb.h"
#include <stdlib.h>
#include <string.h>

//  - Semaphore P or V operations: execute P or V operation on the named semaphore (just like in the
// course notes): may block or unblock a process

// Initialize the named semaphore with the value given. ID's can take a value
// from 0 to 4. This can only be done once for a semaphore -
// subsequent attempts result in error.
//  action taken as well as success or failure.
void new_semaphore_command(char* semaphore_id, char* initial_value) {

    // null check
    if (initial_value == NULL || initial_value[0] == '\0') {
        printf("Initial value is empty\n");
        return;
    }

    // convert string to int
    int initVal = atoi(initial_value);
    int semID = atoi(semaphore_id);

    if (semID > 4){
        printf("Semaphore number %d is not between values 0-4. Please try again.\n", semID);
    }
    else if (semaphores[semID].sem == UNUSED_SEMAPHORE) {
        semaphores[semID].sem = initVal;
        semaphores[semID].waited_processes = List_create();
        printf("Semaphore %d is successfully initialized to %d.\n", semID, initVal);
    } else
        printf("Semaphore %d is already in use.\n", semID);

}

// execute the semaphore P operation on behalf of the running process. You can
// assume sempahores IDs numbered 0 through 4.
// action taken (blocked or not) as well as success or failure.
void semaphore_p_command(char* semaphore_id) {

}

// execute the semaphore V operation on behalf of the running process. You can
// assume sempahores IDs numbered 0 through 4.
// action taken (whether/which process was readied) as well as
// success or failure.
void semaphore_v_command(char* semaphore_id) {

}
