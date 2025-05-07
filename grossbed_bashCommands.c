#include "grossbed_assignment4.h"

/*
    Function: exit: closes all ongoing terminal processes, including the shell itself
    Params: pointer to PID_llist struct - head of LL with all children PIDs
    Returns: none
*/
void exit_shell(struct PID_llist *children) {
    // kill all children processes
    
    // system call to exit terminal
    exit(0);
}