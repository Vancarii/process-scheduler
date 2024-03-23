#ifndef _PCB_H_
#define _PCB_H_

#include <stdbool.h>
#include "list/list.h"

typedef enum {
    RUNNING,
    READY,
    BLOCKED
} ProcessState;

typedef struct {
    int pid;
    int priority;
    ProcessState state;
    // char messages[256];  // Adjust size as needed
    // This field can contain a message that will be printed out the next time the process is scheduled. For
    // example, when a sender is readied, you may want to put something like the following text 
    // in that field: reply received, text is: blah blah blah This field should be displayed and
    // cleared the next time the process runs. 
    char* proc_messages;
} PCB;

#define PROC_MESSAGES_SIZE 41

extern int next_avail_pid;

extern int init_process_pid;

extern PCB* current_process;

// initialize queues
// extern List* ready_queue_0; // <- highest priority
// extern List* ready_queue_1;
// extern List* ready_queue_2;

extern List* ready_queue[3];
extern List* waiting_reply_queue;
extern List* waiting_receive_queue;

// static void print_process_info(PCB* pcb);

void print_all_processes();

PCB* find_next_process();

List* get_queue(int pid);

PCB* create_PCB(int priority);

void pcb_init_process();

void free_PCB(PCB* pcb);

#endif