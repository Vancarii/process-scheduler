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

        // Handle the command
        char command = input[0];

        handleCommand(&command);
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

    // TODO: Based on the command character, call the appropriate function to handle it.
    // This will involve parsing the params as needed for each command.
    switch (*command) {
        case 'C':
         // Handle 'Create' command
            char pri[2];
            printf("Enter the priority (0 = high ; 1 = normal ; 2 = low): ");

            // size of 2 since 1 integer is expected plus null termination
            if (fgets(pri, 2, stdin) == NULL) {
                break;
            }

            create_process(pri);           
            break;
        case 'F':
            // Handle 'Fork' command
            // fork_process();
            break;
        case 'K':

            char pid[5];
            printf("Enter the PID of the process to kill: ");

            if (fgets(pid, 5, stdin) == NULL) {
                break;
            }

            kill_process(pid);

            break;
        case 'E':
            exit_process();
            break;
        case 'Q':
            quantum_command();   
            break;
        case 'S':
        
            break;
        case 'R':
        
            break;
        case 'Y':
        
            break;
        case 'N':
        
            break; 
        case 'P':
        
            break;
        case 'V':
        
            break;
        case 'I':
        
            break;
        case 'T':
        
            break;    
        default:
            printf("\n");
    }
}

void cleanupSimulation() {
    // TODO: Implement cleanup code for the simulation, freeing any allocated resources.

    // cleanup ready queues
    // List_free(ready_queue_0, freefunction);
    // List_free(ready_queue_1, freefunction);
    // List_free(ready_queue_2, freefunction);
}
