#include <stdio.h>
#include "../list/list.h"
#include "../pcb.h"
#include "commands.h"
#include <stdlib.h>

// time quantum of currently running process expires.
// action taken (eg. process scheduling information)
// im guessing we dequeue the process and enqueue it back to the ready queue
void quantum_command() {

        print_all_queues();

    // if there is no currently running process, print an error message and return
    if (current_process == NULL) {
        printf("No process is currently running. Cannot execute quantum command.\n");
        return;
    }

    // get the queue of the currently running process
    List* target_queue = get_queue(current_process->pid);

    // dequeue the process and enqueue it back to the ready queue
    if (target_queue != NULL) {
        PCB* removed_proc = List_remove(target_queue);
        print_all_queues();
        if (List_append(ready_queue[removed_proc->priority], removed_proc) == -1) {
            printf("Failed to append process %d to ready queue with priority %d\n", removed_proc->pid, removed_proc->priority);
            return;
        }
    } else {
        printf("Process %d is not in any queue. Failed to execute quantum command.\n", current_process->pid);
    }

    // have the current process point to the next process in the queue
    current_process = List_first(ready_queue[0]);
    if (current_process == NULL) {
        current_process = List_first(ready_queue[1]);
    }
    if (current_process == NULL) {
        current_process = List_first(ready_queue[2]);
    }
    print_all_queues();




}