#include "grossbed_assignment4.h"
// Global is_foreground only var
bool is_fo = false;

/*  
    Program Name: grossbed_assignment4.c
    Author: Daniel Grossberg
    This program implements a subset of features of well-known shells, such as bash.
    *Citation: SIGINT and SIGTSTP handler process based on examples from the Signals Handling API module
*/

int main() {
    struct command_line *curr_command;
    // Save child process IDs
    struct PID_llist *children = (struct PID_llist *) malloc(sizeof(struct PID_llist));
    char *command;
    char *home = "HOME";
    int exit_status = 0;

    
    
    // Set up signal handler for SIGTSTP
    struct sigaction SIGTSTP_catch;
    // Register handle_SIGINT as a signal handler
    SIGTSTP_catch.sa_handler = handleSIGTSTP;
    // Block all catchable signals while SIGSIGTSTP_catchTERM_redirect is running
    sigemptyset(&SIGTSTP_catch.sa_mask);
    // No flags set
    SIGTSTP_catch.sa_flags = SA_RESTART;
    // Install signal handler
    sigaction(SIGTSTP, &SIGTSTP_catch, NULL);
    
    while (true) {
        curr_command = parse_input();
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
                if (createProcess(curr_command->argc, curr_command->argv, curr_command->input_file, curr_command->output_file, curr_command->is_bg, is_fo, children)) {
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

void handleSIGTSTP(int sig) {
    int status;
    pid_t pid;
    char buffer[256];
    
    if (is_fo) {
        char message[51] = "\nExiting foreground-only mode\n: ";
        write(STDOUT_FILENO, message, 51);
        is_fo = false;
    } else {
        is_fo = true;
        char message[57] = "\nEntering foreground-only mode (& is now ignored)\n: ";
        write(STDOUT_FILENO, message, 57);
    }

    // Clear stdin/stdout
    //fgets(buffer, sizeof(buffer), stdin);
    fflush(stdout);
}