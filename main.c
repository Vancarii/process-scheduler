#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pcb.h"
#include "list/list.h"
#include "commands/commands.h"


#define MAX_INPUT_LENGTH 100


void initializeSimulation();
void handleCommand(char* command);
void cleanupSimulation();

// When a process is created, it is placed in the ready queue 
// if the process created is placed in a higher queue than the current running process
// it does not stop the current process from running
// only if the current process is kicked using Q (quantum), then the higher priority process
// will run


int main() {
    char input[MAX_INPUT_LENGTH];

    printf("\nPROCESS SCHEDULING SIMULATION\n");
    
    initializeSimulation();

    printf("_____________________________________\n");
    
    printf(
        "|  \n"
        "|  Commands: \n"
        "|  \n"
        "|  'C' for Create\n"
        "|  'F' for Fork\n"
        "|  'K' for Kill\n"
        "|  'E' for Exit\n"
        "|  'Q' for Quantum\n"
        "|  'S' for Send\n"
        "|  'R' for Recieve\n"
        "|  'Y' for Reply\n"
        "|  'N' for New Semaphore\n"
        "|  'P' for Semaphore P\n"
        "|  'V' for Semaphore V\n"
        "|  'I' for ProcInfo\n"
        "|  'T' for TotalInfo\n"
        "|_____________________________________\n"
    );


    while (1) {
        //Set the text to the color green
        printf("\033[0;34m"); 
        printf("\ncommand > ");
        printf("\033[0m"); 
        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            break;
        }

        // Remove newline character if present
        input[strcspn(input, "\n")] = 0;

        handleCommand(input);
    }

    cleanupSimulation();
    printf("Simulation terminated.\n");

    return 0;
}

void initializeSimulation() {

    pcb_init_process();

}

void handleCommand(char* command) {
    // char params[2];

    // Check if the command string is exactly 1 character long
    if (strlen(command) != 1) {
        printf("\033[0;31m");
        printf("Invalid command. Please enter a single character command.\n");
        printf("\033[0;0m");
        return;
    }

    // TODO: Based on the command character, call the appropriate function to handle it.
    // This will involve parsing the params as needed for each command.
    switch (*command) {
        case 'C':
         // Handle 'Create' command
            puts("Creating a new process...");
            char pri[2];
            printf("\033[0;34m"); 
            printf("Enter the priority (0 = high ; 1 = normal ; 2 = low) > ");
            printf("\033[0;0m"); 

            // size of 2 since 1 integer is expected plus null termination
            if (fgets(pri, 2, stdin) == NULL) {
                break;
            }

            create_process(pri);           
            break;
        case 'F':
            puts("Forking the current process...");
            // Handle 'Fork' command
            fork_process();
            break;
        case 'K':
            puts("Killing a process...");
            char pid[5];
            printf("\033[0;34m"); 
            printf("Enter the PID of the process to kill > ");
            printf("\033[0;0m"); 

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
            puts("sending a message...");
            char pid_send[5];
            
            printf("\033[0;34m"); 
            printf("Enter the PID of the process to send a message to > ");
            printf("\033[0;0m"); 

            if (fgets(pid_send, 5, stdin) == NULL) {
                break;
            }

            char send_msg[41];
            printf("\033[0;34m"); 
            printf("Enter your message (max. 40 characters) > ");
            printf("\033[0;0m"); 

            if (fgets(send_msg, 41, stdin) == NULL) {
                break;
            }

            send_command(pid_send, send_msg);
        
            break;
        case 'R':
            puts("Checking for incoming messages...");

            recieve_command();
        
            break;
        case 'Y':
            puts("replying to a process...");
            char pid_reply[5];
            printf("\033[0;34m"); 
            printf("Enter the PID of the process to reply to > ");
            printf("\033[0;0m"); 

            if (fgets(pid_reply, 5, stdin) == NULL) {
                break;
            }

            char reply_msg[41];
            printf("\033[0;34m"); 
            printf("Enter your message (max. 40 characters) > ");
            printf("\033[0;0m"); 

            if (fgets(reply_msg, 41, stdin) == NULL) {
                break;
            }

            reply_command(pid_reply, reply_msg);
        
            break;
        case 'N':

            char sem_id[2];
            printf("\033[0;34m"); 
            printf("Enter the semaphore id (0 to 4) > ");
            printf("\033[0;0m"); 

            if (fgets(sem_id, 2, stdin) == NULL) {
                break;
            }

            int ch_n;
            while ((ch_n = getchar()) != '\n' && ch_n != EOF);

            char sem_val[10];
            printf("\033[0;34m"); 
            printf("Enter your semaphore initial value (0 or higher) > ");
            printf("\033[0;0m"); 

            if (fgets(sem_val, 10, stdin) == NULL) {
                break;
            }

            new_semaphore_command(sem_id, sem_val);
        
            break; 
        case 'P':

            char sem_p_id[2];
            printf("\033[0;34m");
            printf("Enter the semaphore id (0 to 4) > ");
            printf("\033[0;0m");

            if (fgets(sem_p_id, 2, stdin) == NULL) {
                break;
            }

            int ch_p;
            while ((ch_p = getchar()) != '\n' && ch_p != EOF);

            semaphore_p_command(sem_p_id);
        
            break;
        case 'V':

            char sem_v_id[2];
            printf("\033[0;34m");
            printf("Enter the semaphore id (0 to 4) > ");
            printf("\033[0;0m");

            if (fgets(sem_v_id, 2, stdin) == NULL) {
                break;
            }

            int ch_v;
            while ((ch_v = getchar()) != '\n' && ch_v != EOF);

            semaphore_v_command(sem_v_id);
        
            break;
        case 'I':
            puts("Retrieving process info...");
            char pid_i[2];
            printf("\033[0;34m");
            printf("enter the process pid: ");
            printf("\033[0;0m");

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
            printf("\033[0;31m");
            printf("command not found. Please enter command from the list above.\n");
            printf("\033[0;0m");
    }
}

void cleanupSimulation() {

    terminate_simulation();

}
