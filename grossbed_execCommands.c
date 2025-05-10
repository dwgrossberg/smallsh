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
    for (int i=0; i<argc;i++) {
        printf("%s\n", argv[i]);
    }
    // Implement outside commands
    // Fork the current process
    child = fork();
    if (child < 0) {
        perror("fork() failed!");
        exit(1);
    } else if (child > 0) {
        int status;
        waitpid(child, &status, 0);
        printf("I am the parent!\n");

    } else {
        // Add child pid to LL
        pid_t child_pid = getpid();
        add_node(head, child_pid);
        printLinkedList(head);
        printf("I am the child!\n");
        exit(0);
    }
    fflush(stdout);
}