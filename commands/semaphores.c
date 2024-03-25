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

    // do checks to see if current is init

    int semID = atoi(semaphore_id);

    if (semID > 4){
        printf("Semaphore number %d is not between values 0-4. Please try again.\n", semID);
    } else if (semaphores[semID].sem == UNUSED_SEMAPHORE) {
        printf("Semaphore %d is not initialized yet. Please initialize it first with N command.\n", semID);
    } else {
        semaphores[semID].sem--;

        if (semaphores[semID].sem < 0) {

            // current_process->state = BLOCKED;
            List* target_queue = get_queue(current_process->pid);
            if (target_queue == NULL) {
                printf("Failed to get queue for process %d\n", current_process->pid);
                return;
            }
            List_first(target_queue);
            PCB* blocked_process = List_remove(target_queue);

            if (List_append(semaphores[semID].waited_processes, blocked_process) == -1) {
                printf("Failed to append process to semaphore wait list\n");
                return;
            }
            printf("Process %d blocked on semaphore %d\n", blocked_process->pid, semID);
            blocked_process->state = BLOCKED;

            printf("Successfully completed P operation on semaphore %d\n", semID);

            current_process = find_next_process();
        } else {
            printf("Successfully completed P operation on semaphore %d\n", semID);
        }

        
    }
}

// execute the semaphore V operation on behalf of the running process. You can
// assume sempahores IDs numbered 0 through 4.
// action taken (whether/which process was readied) as well as
// success or failure.
void semaphore_v_command(char* semaphore_id) {

    // do checks if current is init process

    
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

            printf("Successfully completed V operation on semaphore %d\n", semID);


            enqueue_process(unblocked_process);
        } else {
            printf("Successfully completed V operation on semaphore %d\n", semID);
        }
    }
}
