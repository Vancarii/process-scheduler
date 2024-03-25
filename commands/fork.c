#include "commands.h"
#include <stdio.h>
#include "../pcb.h"
#include <stdlib.h>
#include <string.h>


// Copy the currently running process and put it on the ready Q corresponding to the
// original process' priority. Attempting to Fork the "init" process (see below) should
// fail. 
// reports: success or failure, the pid of the resulting (new) process on success.
void fork_process() {

    // pseudo code:
    // if current is init process, report failed and return

    // else, it means queue has some processes since not running init
    // create a new pcb process
    // copy current process to this new process
    // append the new process to the priority queue accordingly

    if (current_process == init_process){
        printf("Fork failed. Cannot fork init process.\n");
        return;
    }

    PCB* forked_process = create_PCB(current_process->priority);

    strcpy(forked_process->proc_messages, current_process->proc_messages);

    // enqueue to the end of the list
    if (List_append(ready_queue[forked_process->priority], forked_process) == -1) {
        printf("Failed to append process %d to ready queue with priority %d\n", forked_process->pid, forked_process->priority);
        return;
    } else {
        printf("Process created with PID [%d] and priority %d\n", forked_process->pid, forked_process->priority);
    }

}
