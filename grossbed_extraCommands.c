#include "grossbed_assignment4.h"

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
    Params: struct command_line * : pointer to command_line struct returned from stdin, struct PID_llist *head
    Returns: int: 1 for error, 0 for success
    Citation: function based on examples of redirecting stdin/stdout from the course modules
*/
int redirectStd(struct command_line *curr_command, struct PID_llist *head) {
    int result;
    printf("%s, %s, %s", curr_command->argv[0], curr_command->input_file, curr_command->output_file);
    if (curr_command->input_file != NULL) {
        // Open source file
        int source_FD = open(curr_command->input_file, O_RDONLY);
        if (source_FD == -1) { 
            perror("source open()"); 
            exit(1); 
        }
        // Redirect stdin to source file
        result = dup2(source_FD, 0);
        if (result == -1) { 
            perror("source dup2()"); 
            exit(2); 
        }
        fcntl(source_FD, F_SETFD, FD_CLOEXEC);
    }

    if (curr_command->output_file != NULL) {
        // Open target file
        int target_FD = open(curr_command->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (target_FD == -1) { 
            perror("target open()"); 
            exit(1); 
        }
        // Redirect stdout to target file
        result = dup2(target_FD, 1);
        if (result == -1) { 
            perror("target dup2()"); 
            exit(2); 
        }
        fcntl(target_FD, F_SETFD, FD_CLOEXEC);
    }

    // Run the outside command
    if (createProcess(curr_command->argc, curr_command->argv, head)) {
        return 1;
    } else {
        return 0;
    }
}