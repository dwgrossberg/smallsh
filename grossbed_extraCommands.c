#include "grossbed_assignment4.h"
#define _PATH_MAX 1024
#define MAX_ARGS 512

/*
    Function: createProcess - creates a new process to handle outside coammnds
    Params: int argc - length of input array, char **argv - intial argument array passed by user, pointer to head of PID_llist
    Returns: int: 1 for error, 0 for success
*/
int createProcess(int argc, char **argv, struct PID_llist *head) {
    pid_t child = 5;
    int status;
    // Fork the current process
    child = fork();
    if (child < 0) {
        perror("fork() failed!");
        exit(1);
    } else if (child > 0) {
        // Wait for child to complete process
        waitpid(child, &status, 0);
    } else {
        // Add child pid to LL
        pid_t child_pid = getpid();
        // Check child executed successfully
        if(WIFEXITED(status)) {
            add_node(head, child_pid);
            // Create new args array for execv command
            char *new_argv[argc + 1];
            int i = 0;
            for (i; i<argc; i++) {
                printf("%s\n", argv[i]);
                new_argv[i] = argv[i];
            }
            new_argv[i] = NULL;
            // Execute outside command
            if (execvp(new_argv[0], new_argv) != 0 ) {
                perror("execvp");
                return 1;
            }
            fflush(stdout);
            return 0;
        } else {
            return 1;
        }
    }
}

/*
    Function: redirectStd - redirects stdin or stdout depending on the users arguments
    Params: struct command_line * : pointer to command_line struct returned from stdin
    Returns: int: 1 for error, 0 for success
*/
int redirectStd(struct command_line *curr_command) {
    if (curr_command->input_file != NULL && curr_command->output_file == NULL) {
        printf("Input\n");
    } else if (curr_command->output_file != NULL && curr_command->input_file == NULL) {
        printf("Output\n");
    } else {
        printf("Input and Output\n");
    }
    return 0;
}