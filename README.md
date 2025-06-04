# smallsh
smallsh implements a subset of features of well-known shells, such as bash.

## To Run
- Clone the repo: '''git clone git@github.com:dwgrossberg/smallsh.git'''
- Open project directory: '''cd smallsh'''
- Compile an executable file: '''gcc -o smallsh *.c'''
- Run the file: '''./smallsh'''

## Features
- Provides a prompt for running commands
- Handles blank lines and comments (any lines beginning with the # character)
- Executes 3 built-in commands: exit, cd, and status 
- Executes other commands by creating new processes using a function from the exec family of functions
- Supports input and output redirection
- Supports running commands in foreground and background processes
- Implements custom handlers for 2 signals, SIGINT and SIGTSTP
