#include "commands.h"
#include <stdio.h>
#include "../pcb.h"
#include <stdlib.h>
#include <string.h>

// current decision is to not allow any process to send more than one message
// processes can send messages to themselves, they do not get blocked 

// target process that gets message continues executing

// if the send command targets a process in the waiting recieve queue, 
// the waiting process will get unblocked and enqueued to the right queue
// but does not recieve the message until it gets the cpu and starts running with R
// the sender gets blocked on the waiting reply queue

void send_command(char* pid_c, char* msg) {

    // null check
    if (msg == NULL || msg[0] == '\0') {
        printf("Message is empty\n");
        return;
    }

    // Remove newline character if present
    msg[strcspn(msg, "\n")] = 0;

 
    // pid of the process to find and send message to
    int pid = atoi(pid_c);

    // sending to self
    if (current_process->pid == pid){
        strncpy(current_process->proc_messages, msg, PROC_MESSAGES_SIZE - 1);
        current_process->proc_messages[PROC_MESSAGES_SIZE - 1] = '\0';
        printf("Message sent to current process with message: %s\n", current_process->proc_messages);
        return;
    }   

    // else if there are other processes do the rest
    if (current_process == init_process){
        // check if target is the init process
        if (pid == init_process_pid){
            strncpy(init_process->proc_messages, msg, PROC_MESSAGES_SIZE - 1);
            init_process->proc_messages[PROC_MESSAGES_SIZE - 1] = '\0';
            printf("Message sent to init process with message: %s\n", init_process->proc_messages);
            return;
        } 

    } 

    PCB* found_process = NULL;

    // find the queue that the target process is in
    // the curr should already be pointing to the target process
    List* target_queue = get_queue(pid);

    // Here theres no processes in the ready queues
    // meaning the init process is target process
    if (target_queue == NULL){
        found_process = init_process;
    } 
    
    else if (target_queue == waiting_receive_queue){
        printf("Process with PID %d is in the waiting receive queue\n", pid);
        // unblock the process from waiting queue
        if ((found_process = List_remove(waiting_receive_queue)) == NULL) {
            printf("Process with PID %d not found in waiting receive queue\n", pid);

            // int queue_num = enqueue_process(found_process);
            // printf("Process with PID %d unblocked from waiting receive queue and enqueued in ready queue %d\n", pid, queue_num);
        }
    } else {
        found_process = List_curr(target_queue);
    }

    if (found_process == NULL) {
            printf("Process with PID %d not found\n", pid);
            return;
    }
 

    // current decision is to not allow any process to send more than one message
    if (found_process->proc_messages[0] != '\0') {
        printf("Message already exists for process with PID %d\n", pid);
        return;
    }

    msg[strcspn(msg, "\n")] = 0;
    // if the process is found, set the message
    strncpy(found_process->proc_messages, msg, PROC_MESSAGES_SIZE - 1);
    found_process->proc_messages[PROC_MESSAGES_SIZE - 1] = '\0';
    printf("Message sent to process with PID %d with message: %s\n", pid, found_process->proc_messages);


    if (current_process != init_process){

        // block until reply
        current_process->state = BLOCKED;
        printf("Process %d blocked on reply queue\n", current_process->pid);

        // remove from ready queue
        List_first(ready_queue[current_process->priority]);
        List_remove(ready_queue[current_process->priority]);
        if (List_append(waiting_reply_queue, current_process) == -1) {
            printf("Error: could not append to waiting reply queue\n");
            return;
        }
        
        // current_process = find_next_process();

    }

    if (target_queue == waiting_receive_queue){
        printf("Process with PID %d unblocked from waiting receive queue.\n", pid);
        enqueue_process(found_process);
    }

    current_process = find_next_process();


}

// no parameters
// action: receive a message - block until one arrives
//  Receive (R) checks if there is a message waiting for the currently executing process, if there is it
// receives it, otherwise it gets blocked 
// reports: scheduling information and (once msg is received) the message text and source of message
void recieve_command() {

    if (current_process == init_process){
         if (current_process->proc_messages[0] == '\0') {
            printf("No messages to recieve. Cannot block init process.\n");
            return;
         }
    }

    // check if there is a message waiting for the currently executing process
    if (current_process->proc_messages[0] != '\0') {
        printf("Message successfully received: %s\n", current_process->proc_messages);
        printf("Process continues execution.\n");
        current_process->proc_messages[0] = '\0';
    } else {
        // block until message arrives
        current_process->state = BLOCKED;

        // remove from ready queue
        List_first(ready_queue[current_process->priority]);
        List_remove(ready_queue[current_process->priority]);

        // block and put into waiting queue
        List_append(waiting_receive_queue, current_process);

        printf("Process with pid %d has no incoming messages. Blocked on Waiting Recieve Queue.\n", current_process->pid);
        
        current_process = find_next_process();

        printf("Next process with pid %d now gets CPU.\n", current_process->pid);
    }

}

// parameters
// pid (pid of process to send message to), 
// char *msg (nullterminated message string, 40 char max)
// action: unblocks sender and delivers reply
// reports success or failure
void reply_command(char* pid_c, char* msg) {

    // null check
    if (msg == NULL || msg[0] == '\0') {
        printf("Message is empty\n");
        return;
    }


    // pid of the process to find and send message to
    int pid = atoi(pid_c);

    // Remove newline character if present
    msg[strcspn(msg, "\n")] = 0;

    PCB* found_process = NULL;

    // sender should be blocked in waiting for reply queue
    List* target_queue = get_queue(pid);

    // if cannot find pid then the target is the init process
    if (target_queue == NULL){
        // printf("Process with PID %d not found\n", pid);

        found_process = init_process;

        strncpy(found_process->proc_messages, msg, PROC_MESSAGES_SIZE - 1);
        found_process->proc_messages[PROC_MESSAGES_SIZE - 1] = '\0';
        printf("Reply sent to init process with message: %s\n", found_process->proc_messages);
        printf("Previous process continues execution.\n");

        return;

    } else if (target_queue == waiting_reply_queue){
        printf("Process with PID %d is in the waiting reply queue\n", pid);
        // unblock the process from waiting reply queue
        if ((found_process = List_remove(waiting_reply_queue)) == NULL) {
            printf("Process with PID %d not found in waiting reply queue\n", pid);
        } 
        else {
            // unblocks and puts onto the ready queue
            int queue_num = enqueue_process(found_process);
            printf("Process with PID %d unblocked from waiting reply queue and enqueued in ready queue %d\n", pid, queue_num);

            strncpy(found_process->proc_messages, msg, PROC_MESSAGES_SIZE - 1);
            found_process->proc_messages[PROC_MESSAGES_SIZE - 1] = '\0';
            printf("Reply sent to sender process with PID %d with message: %s\n", pid, found_process->proc_messages);
            printf("Process unblocked and placed into ready queue. Previous process continues execution unless it was init process.\n");
        }

    } 
    // else if (target_queue == waiting_receive_queue){
    //     printf("Process with PID %d is in the waiting receive queue\n", pid);
    // }


}