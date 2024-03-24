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

    // do checks for the init process

    int semID = atoi(semaphore_id);

    if (semID > 4){
        printf("Semaphore number %d is not between values 0-4. Please try again.\n", semID);
    } else if (semaphores[semID].sem == UNUSED_SEMAPHORE) {
        printf("Semaphore %d is not initialized yet. Please initialize it first with N command.\n", semID);
    } else {
        semaphores[semID].sem--;

        if (semaphores[semID].sem < 0) {

            current_process->state = BLOCKED;
            if (List_append(semaphores[semID].waited_processes, current_process) == -1) {
                printf("Failed to append process to semaphore wait list\n");
                return;
            }
            printf("Process %d blocked on semaphore %d\n", current_process->pid, semID);
            current_process = find_next_process();
        } else {
            printf("Process %d successfully completed P operation on semaphore %d\n", current_process->pid, semID);
        }
    }
}

// execute the semaphore V operation on behalf of the running process. You can
// assume sempahores IDs numbered 0 through 4.
// action taken (whether/which process was readied) as well as
// success or failure.
void semaphore_v_command(char* semaphore_id) {

    // do checks for the init process

    
    int semID = atoi(semaphore_id);

    if (semID > 4){
        printf("Semaphore number %d is not between values 0-4. Please try again.\n", semID);
    } else if (semaphores[semID].sem == UNUSED_SEMAPHORE) {
        printf("Semaphore %d is not initialized yet. Please initialize it first with N command.\n", semID);
    } else {
        semaphores[semID].sem++;

        if (semaphores[semID].sem <= 0) {
            List_first(semaphores[semID].waited_processes);
            PCB* unblocked_process = List_remove(semaphores[semID].waited_processes);
            if (unblocked_process == NULL) {
                printf("Failed to remove process from semaphore wait list\n");
                return;
            }
            unblocked_process->state = READY;
            printf("Process %d unblocked from semaphore %d\n", unblocked_process->pid, semID);
        } else {
            printf("Process %d successfully completed V operation on semaphore %d\n", current_process->pid, semID);
        }
    }
}
