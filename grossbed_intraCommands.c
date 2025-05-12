#include "grossbed_assignment4.h"
#define _PATH_MAX 1024

/*
    Function: exit: closes all ongoing terminal processes, including the shell itself
    Params: pointer to PID_llist struct - head of LL with all children PIDs
    Returns: none
*/
void exit_shell(struct PID_llist *children) {
    // kill all children processes and free from mem
    while (children) {
        struct PID_llist *temp = children;
        kill(children->pid, 0);
        children = children->next;
        free(temp);
    }
    // system call to exit terminal
    exit(0);
}

/*
    Function: change_dir: changes the current working directory of the shell
    Params: path: pointer to char array = argv[1]
    Returns: int: 1 for error, 0 for success
*/
int change_dir(char *path) {
    char *cwd;
    char buf[_PATH_MAX];
    if (path != NULL) {
        if (!chdir(path)) {
            return 0;
        } else {
            return 1;
        }
    }
}

/*
    Function: status: provides the exit_status or termination status of the previous foreground process
    Params: none
    Returns: int: 1 for error, 0 for success
*/
int status(int exit_status) {
    printf("exit value %d\n", exit_status);
}