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
    Returns: none
*/
void change_dir(char *path) {
    char *cwd;
    char buf[_PATH_MAX];
    if (path != NULL) {
        cwd = getcwd(buf, _PATH_MAX);
        printf("%s\n", cwd);
        chdir(path);
        cwd = getcwd(buf, _PATH_MAX);
        printf("%s\n", cwd);
        fflush(stdout);
    }
}