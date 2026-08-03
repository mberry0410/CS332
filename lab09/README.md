## Lab 9 README
# 

## Description
- This program is a modified version of forkexecvp.c for lab 9.
- The parent process installs signal handlers and forwards signals to the child
process
- Ctrl + C (SIGINT) is forwarded to the child process.
- Ctrl + Z (SIGTSTP) is forwarded to the child process. 
- The parent process continues waiting for signals.
- Ctrl + Z (SIGQUIT) terminates the parent process and ends the program.
- The program reports when the child either exits, is terminated by a signal, or is stopped.

## To Compile
- gcc -Wall forkexecvp.c -o forkexecvp

# To Run
- ./forkexecvp <command> [arguments]

- ./forkexecvp sleep 30
