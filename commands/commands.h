#ifndef _COMMANDS_H_
#define _COMMANDS_H_

void create_process(char* params);

void kill_process(char* pid_c);

void exit_process();

void quantum_command();

void proc_info_command(char* pid_c);

void total_info_command();

// parameters
// pid (pid of process to send message to), 
// char *msg (nullterminated message string, 40 char max)
// action: send a message to another process - block until reply
// reports: success or failure, scheduling information, and reply source and text (once reply arrives)
void send_command(char* pid_c, char* msg);

// no parameters
// action: receive a message - block until one arrives
// reports: scheduling information and (once msg is received) the message text and source of message
void recieve_command();

// parameters
// pid (pid of process to send message to), 
// char *msg (nullterminated message string, 40 char max)
// action: unblocks sender and delivers reply
// reports success or failure
void reply_command();


#endif