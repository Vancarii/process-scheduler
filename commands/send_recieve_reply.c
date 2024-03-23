#include "commands.h"
#include <stdio.h>
#include "../pcb.h"
#include <stdlib.h>
#include <string.h>

// parameters
// pid (pid of process to send message to), 
// char *msg (null terminated message string, 40 char max)
// action: send a message to another process - block until reply
// reports: success or failure, scheduling information, and reply source and text (once reply arrives)
void send_command(char* pid_c, char* msg) {

    // pid of the process to find and send message to
    int pid = atoi(pid_c);

    PCB* found_process = NULL;

    // find the queue that the target process is in
    // the curr should already be pointing to the target process
    List* target_queue = get_queue(pid);

    if (target_queue == NULL){
        printf("Process with PID %d not found\n", pid);
        return;
    } else if (target_queue == waiting_receive_queue){
        printf("Process with PID %d is in the waiting receive queue\n", pid);
        // unblock the process from waiting queue
        // if ((found_process = List_remove(waiting_receive_queue)) != NULL) {
        //     int queue_num = enqueue_process(found_process);
        //     printf("Process with PID %d unblocked from waiting receive queue and enqueued in ready queue %d\n", pid, queue_num);
        // }
    } 
    // else if (target_queue == waiting_reply_queue){
    //     printf("Process with PID %d is in the waiting reply queue\n", pid);
    // }

    found_process = List_curr(target_queue);

    if (found_process != NULL) {
        // if the process is found, set the message
        strncpy(found_process->proc_messages, msg, PROC_MESSAGES_SIZE - 1);
        found_process->proc_messages[PROC_MESSAGES_SIZE - 1] = '\0';
        printf("Message sent to process with PID %d with message: %s\n", pid, found_process->proc_messages);


        // block until reply
        current_process->state = BLOCKED;

        // remove from ready queue
        List_first(ready_queue[current_process->priority]);
        List_remove(ready_queue[current_process->priority]);
        List_append(waiting_reply_queue, current_process);
        
        current_process = find_next_process();
    }
    

}

// no parameters
// action: receive a message - block until one arrives
//  Receive (R) checks if there is a message waiting for the currently executing process, if there is it
// receives it, otherwise it gets blocked 
// reports: scheduling information and (once msg is received) the message text and source of message
void recieve_command() {

    // check if there is a message waiting for the currently executing process
    if (current_process->proc_messages[0] != '\0') {
        printf("Message received: %s\n", current_process->proc_messages);
        current_process->proc_messages[0] = '\0';
    } else {
        // block until message arrives
        current_process->state = BLOCKED;

        // remove from ready queue
        List_first(ready_queue[current_process->priority]);
        List_remove(ready_queue[current_process->priority]);

        // block and put into waiting queue
        List_append(waiting_receive_queue, current_process);
        
        current_process = find_next_process();
    }

}

// parameters
// pid (pid of process to send message to), 
// char *msg (nullterminated message string, 40 char max)
// action: unblocks sender and delivers reply
// reports success or failure
void reply_command(char* pid_c, char* msg) {

    // pid of the process to find and send message to
    int pid = atoi(pid_c);

    PCB* found_process = NULL;

    // sender should be blocked in waiting for reply queue
    List* target_queue = get_queue(pid);

    if (target_queue == NULL){
        printf("Process with PID %d not found\n", pid);
        return;
    } else if (target_queue == waiting_reply_queue){
        printf("Process with PID %d is in the waiting reply queue\n", pid);
        // unblock the process from waiting reply queue
        if ((found_process = List_remove(waiting_reply_queue)) == NULL) {
            printf("Process with PID %d not found in waiting reply queue\n", pid);
        } 
        else {
            int queue_num = enqueue_process(found_process);
            printf("Process with PID %d unblocked from waiting reply queue and enqueued in ready queue %d\n", pid, queue_num);

            strncpy(found_process->proc_messages, msg, PROC_MESSAGES_SIZE - 1);
            found_process->proc_messages[PROC_MESSAGES_SIZE - 1] = '\0';
            printf("Reply sent to sender process with PID %d with message: %s\n", pid, found_process->proc_messages);

        }

    } 
    // else if (target_queue == waiting_receive_queue){
    //     printf("Process with PID %d is in the waiting receive queue\n", pid);
    // }


}