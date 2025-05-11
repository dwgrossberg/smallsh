#include "grossbed_assignment4.h"
#define MAX_ARGS 512

/*
    Function: parse_input: parses the user input to the command line
    Params: none
    Returns: pointer to a command line struct saved (calloced) in memory
    *Citation: based on the sample parsing program given with assignment 4.
*/
pid_t createProcess(int argc, char **argv, struct PID_llist *head) {
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
        char path[strlen(argv[0]) + 5];
        strcpy(path, "/bin/");
        strcat(path, argv[0]);
        new_argv[0] = path;
        int i = 1;
        for (i; i<argc; i++) {
            new_argv[i] = argv[i];
        }
        new_argv[i] = NULL;
        // Execute outside command
        execv(new_argv[0], new_argv);
        perror("execv");
        exit(0);
    }
    fflush(stdout);
}