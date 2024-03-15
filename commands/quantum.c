#include <stdio.h>
#include "../list/list.h"
#include "../pcb.h"
#include "commands.h"
#include <stdlib.h>

// time quantum of currently running process expires.
// action taken (eg. process scheduling information)
// im guessing we dequeue the process and enqueue it back to the ready queue
//  Quantum (Q) is the ONLY way to signal that the time quantum for round robin scheduling has expired
// - when this occurs we must choose the next process to execute from the appropriate ready queue
// (or just the init process if no processes are ready)
// - when a new process becomes ready of a higher priority than the currently executing process, you
// do NOT need to pre-empt the currently executing process; just wait until quantum expires
void quantum_command() {

        // print_all_queues();

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
        // print_all_queues();
        if (removed_proc == NULL) {
            printf("Failed to remove process %d from its queue. Failed to execute quantum command.\n", current_process->pid);
            return;
        } else {
            current_process = List_curr(ready_queue[removed_proc->priority]);
            if (current_process == NULL) {
                current_process = find_next_process();
            }
            removed_proc->state = READY;
            if (List_append(ready_queue[removed_proc->priority], removed_proc) == -1) {
                printf("Failed to append process %d to ready queue with priority %d\n", removed_proc->pid, removed_proc->priority);
                return;
            } else {
                printf("Process %d has been successfully enqueued to ready queue with priority %d\n", removed_proc->pid, removed_proc->priority);
            }
        }
    } else {
        printf("Process %d is not in any queue. Failed to execute quantum command.\n", current_process->pid);
    }

    // have the current process point to the next process in the queue
    // current_process = List_first(ready_queue[0]);
    // if (current_process == NULL) {
    //     current_process = List_first(ready_queue[1]);
    // }
    // if (current_process == NULL) {
    //     current_process = List_first(ready_queue[2]);
    // }
    // print_all_queues();


}