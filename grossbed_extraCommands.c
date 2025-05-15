#include "grossbed_assignment4.h"

/*
    Function: createProcess - creates a new process to handle outside commands
    Params: int argc - length of input array, char **argv - intial argument array passed by user, pointer to head of PID_llist
    Returns: int: 1 for error, 0 for success
*/
int createProcess(int argc, char **argv, char *input_file, char *output_file, bool is_bg, struct PID_llist *head) {
    pid_t child = 5;
    int status;

    // Set up signal handler for SIGCHLD
    struct sigaction sa;
    sa.sa_handler = handleSigchld;
    // Catch all signals
    sigemptyset(&sa.sa_mask);
    // Prevent handler from being called when child is stopped && restart interrupted children 
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    if (sigaction(SIGCHLD, &sa, 0) == -1) {
        perror("sigaction");
        return 1;
    }

    // Fork the current process
    child = fork();

    if (child < 0) {
        perror("fork() failed!");
        return 1;
    } else if (child == 0) {
        pid_t child_pid = getpid();

        // Handle commands with stdin or stdout redirection
        if (redirectStdIO(input_file, output_file, is_bg)) {
            return 1;
        } 

        // Add child pid to LL
        add_node(head, child_pid);

        // Create new args array for execv command
        char *new_argv[argc + 1];
        int i = 0;
        for (i; i<argc; i++) {
            new_argv[i] = argv[i];
        }
        new_argv[i] = NULL;

        // Execute outside command
        if (execvp(new_argv[0], new_argv) != 0) {
            perror("execvp");
            return 1;
        }
        fflush(stdout);
    } else {
        // Parent process
        if (is_bg) {
            // Handle child process in the background
            printf("background pid is %d\n", child);
            waitpid(child, &status, WNOHANG);
        } else {
            // Wait for child to complete process
            waitpid(child, &status, 0);   
        }
    }
}

/*
    Function: redirectStd - redirects stdin or stdout depending on the users arguments
    Params: struct command_line * : pointer to command_line struct returned from stdin, struct PID_llist *head
    Returns: int: 1 for error, 0 for success
    Citation: function based on examples of redirecting stdin/stdout from the course modules
*/
int redirectStdIO(char *input_file, char *output_file, bool is_bg) {
    int result;
    if (input_file != NULL) {
        // Open source file
        int source_FD = open(input_file, O_RDONLY);
        if (source_FD == -1) { 
            perror("source open()"); 
            return 1; 
        }
        // Redirect stdin to source file
        result = dup2(source_FD, 0);
        if (result == -1) { 
            perror("source dup2()"); 
            return 1; 
        }
        fcntl(source_FD, F_SETFD, FD_CLOEXEC);
    } else if (is_bg) {
        // Open default bg stdin file
        int source_FD = open("/dev/null", O_RDONLY);
        if (source_FD == -1) { 
            perror("source open()"); 
            return 1; 
        }
        // Redirect stdin to source file
        result = dup2(source_FD, 0);
        if (result == -1) { 
            perror("source dup2()"); 
            return 1; 
        }
        fcntl(source_FD, F_SETFD, FD_CLOEXEC);
    }

    if (output_file != NULL) {
        // Open target file
        int target_FD = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (target_FD == -1) { 
            perror("target open()"); 
            return 1; 
        }
        // Redirect stdout to target file
        result = dup2(target_FD, 1);
        if (result == -1) { 
            perror("target dup2()"); 
            return 1; 
        }
        fcntl(target_FD, F_SETFD, FD_CLOEXEC);
    } else if (is_bg) {
        // Open default bg stdout file
        int target_FD = open("/dev/null", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (target_FD == -1) { 
            perror("target open()"); 
            return 1; 
        }
        // Redirect stdout to target file
        result = dup2(target_FD, 1);
        if (result == -1) { 
            perror("target dup2()"); 
            return 1; 
        }
        fcntl(target_FD, F_SETFD, FD_CLOEXEC);
    }
    return 0;
}

/*
    Function: handleSigchild - handler function to catch child process termination signal
    Params: int sig 
    Returns: none
    Citation: function adapted from module on Signal Handling API
*/
void handleSigchld(int sig) {
    int status;
    pid_t pid;

    // Catch all terminated child processes
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) {
            printf("\nbackground pid %d is done: exit value %d\n", pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("\nbackground pid %d is done: terminated by signal %d\n", pid, WTERMSIG(status));
        }
    }
}