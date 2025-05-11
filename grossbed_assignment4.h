#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#define INPUT_LENGTH 2048
#define MAX_ARGS 512

// *Citation: command_line struct based on the code provided with assignment 4.
struct command_line {
    char *argv[MAX_ARGS + 1];
    int argc;
    char *input_file;
    char *output_file;
    bool is_bg;
};

// Linked List to save child PIDs
struct PID_llist {
    pid_t pid;
    struct PID_llist *next;
};

// Function prototypes
struct command_line *parse_input();
void exit_shell(struct PID_llist *);
void add_node(struct PID_llist *head, pid_t PID);
struct PID_llist* del_node(struct PID_llist *head, pid_t PID);
void printLinkedList(struct PID_llist *head);
int change_dir(char *path);
int status(int exit_status);
int createProcess(int argc, char **argv, struct PID_llist *head);