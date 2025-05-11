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
                new_argv[i] = argv[i];
            }
            new_argv[i] = NULL;
            // Execute outside command
            if (execvp(new_argv[0], new_argv) != 0 ) {
                perror("execv");
                return 1;
            }
            return 0;
        } else {
            return 1;
        }
    }
    fflush(stdout);
}