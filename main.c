#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pcb.h"
#include "list/list.h"
#include "commands/create.h"


#define MAX_INPUT_LENGTH 100


// Forward declarations of functions
void initializeSimulation();
void handleCommand(char* command);
void cleanupSimulation();

int main() {
    char input[MAX_INPUT_LENGTH];
    initializeSimulation();

    printf("Process Scheduling Simulation\n");
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

    // ready_queue_0 = list_create(); // <- highest priority
    // ready_queue_1 = list_create();
    // ready_queue_2 = list_create();

    next_avail_pid = 0;

    for (int i = 0; i < 3; i++) {
        ready_queue[i] = List_create();
    }

    waiting_receive_queue = List_create();
    waiting_reply_queue = List_create();

    

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
            char params[2];
            printf("Priority (0 = high ; 1 = normal ; 2 = low): ");

            // size of 2 since 1 integer is expected plus null termination
            if (fgets(params, 2, stdin) == NULL) {
            // Handle error or end-of-file
                break;
            }

            create_process(command, params);           
            break;
        // case 'F':
            // Handle 'Fork' command
            // fork_process();
            // break;
        // Add cases for other commands
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
