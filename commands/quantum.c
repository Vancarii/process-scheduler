#include <stdio.h>
#include "../list/list.h"
#include "../pcb.h"
#include "commands.h"
#include <stdlib.h>

// Current design decision:
// We will dequeue the process and enqueue it back to the ready queue of original queue
// since we are enqueue back to original queue, if the next running process is lower in the queue,
// and the process that was pre-empted is enqueued back to the beginning of the higher priority 
// queue, then that process gets the cpu again since it is still higher priority

// time quantum of currently running process expires.
// action taken (eg. process scheduling information)
//  Quantum (Q) is the ONLY way to signal that the time quantum for round robin scheduling has expired
// - when this occurs we must choose the next process to execute from the appropriate ready queue
// (or just the init process if no processes are ready)
// - when a new process becomes ready of a higher priority than the currently executing process, you
// do NOT need to pre-empt the currently executing process; just wait until quantum expires
void quantum_command() {

    if (current_process == init_process) {
        printf("Init process is currently running. Failed to execute quantum command.\n");
        return;
    }

    // get the queue of the currently running process
    List* target_queue = get_queue(current_process->pid);

    // dequeue the process and enqueue it back to the ready queue
    if (target_queue != NULL) {
        List_first(target_queue);
        PCB* removed_proc = List_remove(target_queue);
        if (removed_proc == NULL) {
            printf("Failed to remove process %d from its queue. Failed to execute quantum command.\n", current_process->pid);
            return;
        } else {
            
            
            removed_proc->state = READY;
            if (List_append(ready_queue[removed_proc->priority], removed_proc) == -1) {
                printf("Failed to append process %d to ready queue with priority %d\n", removed_proc->pid, removed_proc->priority);
                return;
            }


            printf("Process %d has been successfully pre-empted and enqueued back to priority queue %d\n", removed_proc->pid, removed_proc->priority);

            current_process = find_next_process();
            printf("Process %d now has the CPU.\n", current_process->pid);
            
        }
    } else {
        printf("Process %d is not in any queue. Failed to execute quantum command.\n", current_process->pid);
    }

}