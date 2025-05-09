#include "grossbed_assignment4.h"

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
    Function: exit: closes all ongoing terminal processes, including the shell itself
    Params: pointer to PID_llist struct - head of LL with all children PIDs
    Returns: none
*/
void change_dir(struct PID_llist *children) {
}