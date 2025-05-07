#include "grossbed_assignment4.h"

/*  
    Program Name: grossbed_assignment4.c
    Author: Daniel Grossberg
    This program implements a subset of features of well-known shells, such as bash.
*/

int main() {
    struct command_line *curr_command;
    while(true)
    {
    curr_command = parse_input();
    }
    return EXIT_SUCCESS;
}

/*
    Citation: based on the sample parsing program given with assignment 4.
*/
struct command_line *parse_input() {
    char input[INPUT_LENGTH];
    struct command_line *curr_command = (struct command_line *) calloc(1, sizeof(struct command_line));

    // Get input
    printf(": ");
    fflush(stdout);
    fgets(input, INPUT_LENGTH, stdin);

    // Tokenize the input
    char *token = strtok(input, " \n");

    while (token) {
        if(!strcmp(token,"<")){
        curr_command->input_file = strdup(strtok(NULL," \n"));
        } else if(!strcmp(token,">")){
        curr_command->output_file = strdup(strtok(NULL," \n"));
        } else if(!strcmp(token,"&")){
        curr_command->is_bg = true;
        } else{
        curr_command->argv[curr_command->argc++] = strdup(token);
        }
        token=strtok(NULL," \n");
    }
    return curr_command;
}
