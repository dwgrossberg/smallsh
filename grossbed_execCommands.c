#include "grossbed_assignment4.h"
#define _PATH_MAX 1024
#define MAX_ARGS 512

/*
    Function: createProcess - creates a new process to handle outside coammnds
    Params: int argc - length of input array, char **argv - intial argument array passed by user, pointer to head of PID_llist
    Returns: none
*/
void createProcess(int argc, char **argv, struct PID_llist *head) {
    pid_t child = 5;
    // Implement outside commands
    // Fork the current process
    child = fork();
    if (child < 0) {
        perror("fork() failed!");
        exit(1);
    } else if (child > 0) {
        int status;
        // Wait for child to complete process
        waitpid(child, &status, 0);
    } else {
        // Add child pid to LL
        pid_t child_pid = getpid();
        add_node(head, child_pid);

        // Create new args array for execv command
        char *new_argv[argc + 1];
        int i = 0;
        for (i; i<argc; i++) {
            new_argv[i] = argv[i];
        }
        new_argv[i] = NULL;
        // Execute outside command
        execvp(new_argv[0], new_argv);
        perror("execv");
        exit(0);
    }
    fflush(stdout);
}