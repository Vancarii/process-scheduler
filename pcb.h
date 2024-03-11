#ifndef _PCB_H_
#define _PCB_H_

#include <stdbool.h>

typedef enum {
    RUNNING,
    READY,
    BLOCKED
} ProcessState;

typedef struct {
    int pid;
    int priority;
    ProcessState state;
    char messages[256];  // Adjust size as needed
    // This field can contain a message that will be printed out the next time the process is scheduled. For
    // example, when a sender is readied, you may want to put something like the following text 
    // in that field: reply received, text is: blah blah blah This field should be displayed and
    // cleared the next time the process runs. 
    char proc_messages[256];
} PCB;

int next_avail_pid = 0;

PCB* create_PCB(int priority);

void pcb_init_process();

#endif