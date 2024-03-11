#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pcb.h"

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
            create_process(command);           
            break;
        case 'F':
            // Handle 'Fork' command
            // fork_process();
            break;
        // Add cases for other commands
        default:
            printf("\n");
    }
}

void cleanupSimulation() {
    // TODO: Implement cleanup code for the simulation, freeing any allocated resources.
}
