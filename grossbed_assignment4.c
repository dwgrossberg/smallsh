#include "grossbed_assignment4.h"

/*  
    Program Name: grossbed_assignment4.c
    Author: Daniel Grossberg
    This program implements a subset of features of well-known shells, such as bash.
*/

int main() {
    struct command_line *curr_command;
    // Save child process IDs
    struct PID_llist *children = (struct PID_llist *) malloc(sizeof(struct PID_llist));
    char *command;
    int exit_status = 0;
    
    while (true) {
        curr_command = parse_input();
        // Check for built-in command
        command = curr_command->argv[0];
        if (command != NULL) {
            if (!strcmp(command, "exit")) {
                exit_shell(children);
            } else if (!strcmp(command, "cd")) {
                if (!change_dir(curr_command->argv[1])) {
                    exit_status = 1;
                } else {
                    exit_status = 0;
                }
            } else if (!strcmp(command, "status")) {
                if (!status(exit_status)) {
                    exit_status = 1;
                } else {
                    exit_status = 0;
                }
            } else {
                // Execute other functions if not a comment
                
                
                    //Handle exec without stdin and or stdout redirection
                    if (createProcess(curr_command->argc, curr_command->argv, curr_command->input_file, curr_command->output_file, children)) {
                        exit_status = 1;
                    } else {
                        exit_status = 0;
                    }
                
            }       
        }
    }
    return EXIT_SUCCESS;
}

/*
    Function: parse_input: parses the user input to the command line
    Params: none
    Returns: pointer to a command line struct saved (calloced) in memory
    *Citation: based on the sample parsing program given with assignment 4.
*/
struct command_line *parse_input() {
    char input[INPUT_LENGTH];
    struct command_line *curr_command = (struct command_line *) calloc(1, sizeof(struct command_line));   

    // Get input
    printf(": ");
    fflush(stdout);
    fgets(input, INPUT_LENGTH, stdin);
    // Tokenize the input
    char *token = strtok(input, " \n");

    while (token && input[0] != '#' && input[0] != ' ') {
        // Skip comments
        if (!strcmp(token, "#")) {
            break;
        } else if (!strcmp(token, "<")) {
            curr_command->input_file = strdup(strtok(NULL," \n"));
        } else if (!strcmp(token, ">")) {
            curr_command->output_file = strdup(strtok(NULL," \n"));
        } else if (!strcmp(token,"&")) {
            curr_command->is_bg = true;
        } else{
            curr_command->argv[curr_command->argc++] = strdup(token);
        }
        token=strtok(NULL," \n");
    }
    return curr_command;
}
