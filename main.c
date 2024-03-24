#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pcb.h"
#include "list/list.h"
#include "commands/commands.h"


#define MAX_INPUT_LENGTH 100


// Forward declarations of functions
void initializeSimulation();
void handleCommand(char* command);
void cleanupSimulation();

int main() {
    char input[MAX_INPUT_LENGTH];

    printf("Process Scheduling Simulation\n");
    
    initializeSimulation();

    printf("_____________________________________\n");
    
    printf("Enter command: \n\n'C' for Create\n'F' for Fork\n'K' for Kill\n'E' for Exit\n'Q' for Quantum\n'S' for Send\n'R' for Recieve\n'Y' for Reply\n'N' for New Semaphore\n'P' for Semaphore P\n'V' for Semaphore V\n'I' for ProcInfo\n'T' for TotalInfo\n\nor 'exit' to quit:\n");

    while (1) {
        printf("\ncommand > ");  // Prompt for input
        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            // Handle error or end-of-file
            break;
        }

        // Remove newline character if present
        input[strcspn(input, "\n")] = 0;

        // Check for 'exit' command to break the loop
        if (strcmp(input, "exit") == 0) {
            break;
        }

        handleCommand(input);
    }

    cleanupSimulation();
    printf("Simulation ended.\n");

    return 0;
}

void initializeSimulation() {

    // TODO: Implement the initialization of the simulation
    pcb_init_process();

}

void handleCommand(char* command) {
    // char params[2];

    // Check if the command string is exactly 1 character long
    if (strlen(command) != 1) {
        printf("Invalid command. Please enter a single character command.\n");
        return;
    }

    // TODO: Based on the command character, call the appropriate function to handle it.
    // This will involve parsing the params as needed for each command.
    switch (*command) {
        case 'C':
         // Handle 'Create' command
            puts("Creating a new process...");
            char pri[2];
            printf("Enter the priority (0 = high ; 1 = normal ; 2 = low): ");

            // size of 2 since 1 integer is expected plus null termination
            if (fgets(pri, 2, stdin) == NULL) {
                break;
            }

            create_process(pri);           
            break;
        case 'F':
            puts("Forking the current process...");
            // Handle 'Fork' command
            // fork_process();
            break;
        case 'K':
            puts("Killing a process...");
            char pid[5];
            printf("Enter the PID of the process to kill: ");

            if (fgets(pid, 5, stdin) == NULL) {
                break;
            }

            kill_process(pid);

            break;
        case 'E':
            puts("Exiting the currently running process...");
            exit_process();
            break;
        case 'Q':
            puts("Time Quantum is over! Current process is being pre-empted...");
            quantum_command();   
            break;
        case 'S':
            // puts("sending a message...");
            char pid_send[5];
            printf("Enter the PID of the process to send a message to: ");

            if (fgets(pid_send, 5, stdin) == NULL) {
                break;
            }

            char send_msg[41];
            printf("Enter your message (max. 40 characters): ");

            if (fgets(send_msg, 41, stdin) == NULL) {
                break;
            }

            send_command(pid_send, send_msg);
        
            break;
        case 'R':

            recieve_command();
        
            break;
        case 'Y':

            // puts("sending a message...");
            char pid_reply[5];
            printf("Enter the PID of the process to send a message to: ");

            if (fgets(pid_reply, 5, stdin) == NULL) {
                break;
            }

            char reply_msg[41];
            printf("Enter your message (max. 40 characters): ");

            if (fgets(reply_msg, 41, stdin) == NULL) {
                break;
            }

            reply_command(pid_reply, reply_msg);
        
            break;
        case 'N':

            char sem_id[2];
            printf("Enter the semaphore id (0 to 4): ");

            if (fgets(sem_id, 2, stdin) == NULL) {
                break;
            }

            char sem_val[10];
            printf("Enter your semaphore initial value (0 or higher): ");

            if (fgets(sem_val, 10, stdin) == NULL) {
                break;
            }

            new_semaphore_command(sem_id, sem_val);
        
            break; 
        case 'P':

            char sem_p_id[2];
            printf("Enter the semaphore id (0 to 4): ");

            if (fgets(sem_p_id, 2, stdin) == NULL) {
                break;
            }

            semaphore_p_command(sem_p_id);
        
            break;
        case 'V':

            char sem_v_id[2];
            printf("Enter the semaphore id (0 to 4): ");

            if (fgets(sem_v_id, 2, stdin) == NULL) {
                break;
            }

            semaphore_v_command(sem_v_id);
        
            break;
        case 'I':
            puts("Retrieving process info...");
            char pid_i[2];
            printf("enter the process pid: ");

            // size of 2 since 1 integer is expected plus null termination
            if (fgets(pid_i, 2, stdin) == NULL) {
                break;
            }
            proc_info_command(pid_i);

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
        
            break;
        case 'T':
            puts("Retrieving total info...");
            total_info_command();
            break;    
        default:
            printf("command not found. Please enter command from the list above.\n");
    }
}

void cleanupSimulation() {
    // TODO: Implement cleanup code for the simulation, freeing any allocated resources.

    // cleanup ready queues
    // List_free(ready_queue_0, freefunction);
    // List_free(ready_queue_1, freefunction);
    // List_free(ready_queue_2, freefunction);
}
