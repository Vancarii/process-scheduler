#ifndef _COMMANDS_H_
#define _COMMANDS_H_

// create a process and put it on the appropriate ready Q. 
// reports success or failure, the pid of the created process on success.
void create_process(char* params);

// Copy the currently running process and put it on the ready Q corresponding to the
// original process' priority. Attempting to Fork the "init" process (see below) should
// fail. 
// reports: success or failure, the pid of the resulting (new) process on success.
void fork_process();

// kill the named process and remove it from the system.
// action taken as well as success or failure.
void kill_process(char* pid_c);

// kill the currently running process.
// process scheduling information (eg. which process now gets
// control of the CPU) 
void exit_process();

// time quantum of running process expires
// action taken (eg. process scheduling information)
void quantum_command();

// dump complete state information of process to
// screen (this includes process status and anything else you can think of)
void proc_info_command(char* pid_c);

// display all process queues and their contents
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
void reply_command(char* pid_c, char* msg);

// Initialize the named semaphore with the value given. ID's can take a value
// from 0 to 4. This can only be done once for a semaphore -
// subsequent attempts result in error.
//  action taken as well as success or failure.
void new_semaphore_command(char* semaphore_id, char* initial_value);

// execute the semaphore P operation on behalf of the running process. You can
// assume sempahores IDs numbered 0 through 4.
// action taken (blocked or not) as well as success or failure.
void semaphore_p_command(char* semaphore_id);

// execute the semaphore V operation on behalf of the running process. You can
// assume sempahores IDs numbered 0 through 4.
// action taken (whether/which process was readied) as well as
// success or failure.
void semaphore_v_command(char* semaphore_id);


#endif