#include "commands.h"
#include <stdio.h>
#include "../pcb.h"
#include <stdlib.h>
#include <string.h>

//  - Semaphore P or V operations: execute P or V operation on the named semaphore (just like in the
// course notes): may block or unblock a process

// Initialize the named semaphore with the value given. ID's can take a value
// from 0 to 4. This can only be done once for a semaphore -
// subsequent attempts result in error.
//  action taken as well as success or failure.
void new_semaphore_command(char* semaphore_id, char* initial_value) {

}

// execute the semaphore P operation on behalf of the running process. You can
// assume sempahores IDs numbered 0 through 4.
// action taken (blocked or not) as well as success or failure.
void semaphore_p_command(char* semaphore_id) {

}

// execute the semaphore V operation on behalf of the running process. You can
// assume sempahores IDs numbered 0 through 4.
// action taken (whether/which process was readied) as well as
// success or failure.
void semaphore_v_command(char* semaphore_id) {

}
