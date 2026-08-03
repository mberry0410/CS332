/* Lab 9  forkexecvp.c 
 * To Compile: gcc -Wall forkexecvp.c -o forkexecvp
 * To Run: ./forkexecvp <command> [args] 
 *  Madison Byrd 
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static pid_t child_pid = 0;

/* Handles state changes in child process */
static void sig_child(int signo) {
    int status;
    signal(signo, sig_child);

    if (child_pid > 0) {
        pid_t result = waitpid(child_pid, &status, WNOHANG | WUNTRACED);
        if (result > 0) {
            if (WIFEXITED(status)) {
                printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                child_pid = 0;
            } else if (WIFSIGNALED(status)) {
                printf("Child process terminated by signal = %d\n", WTERMSIG(status));
                child_pid = 0;
            } else if (WIFSTOPPED(status)) {
                printf("Child process stopped by signal = %d\n", WSTOPSIG(status));
            }
        }
    }
}

/* Forwards interrupt and stop signals to the active child */
static void sig_forward(int signo) {
    signal(signo, sig_forward);

    if (child_pid > 0) {
        if (signo == SIGINT) {
            printf("\nReceived SIGINT, forwarding to child...\n");
            kill(child_pid, SIGINT);
        } else if (signo == SIGTSTP) {
            printf("\nReceived SIGTSTP, forwarding to child...\n");
            kill(child_pid, SIGTSTP);
        }
    } else {
        printf("\nNo child process running\n");
    }
}

/* Terminates parent and kills child if quit signal is received */
static void sig_quit(int signo) {
    printf("\nReceived SIGQUIT. Terminating parent process...\n");
    if (child_pid > 0) {
        kill(child_pid, SIGTERM);
    }
    exit(0);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <command> [args]\n", argv[0]);
        exit(-1);
    }

    if (signal(SIGINT, sig_forward) == SIG_ERR) {
        printf("Unable to catch SIGINT\n");
        exit(-1);
    }
    if (signal(SIGTSTP, sig_forward) == SIG_ERR) {
        printf("Unable to catch SIGTSTP\n");
        exit(-1);
    }
    if (signal(SIGQUIT, sig_quit) == SIG_ERR) {
        printf("Unable to catch SIGQUIT\n");
        exit(-1);
    }
    if (signal(SIGCHLD, sig_child) == SIG_ERR) {
        printf("Unable to catch SIGCHLD\n");
        exit(-1);
    }

    child_pid = fork();

    if (child_pid == 0) {
        /* Restore default signals in the child */
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        signal(SIGCHLD, SIG_DFL);

        execvp(argv[1], &argv[1]);
        perror("execvp");
        exit(-1);
    } else if (child_pid > 0) {
        printf("Waiting for child process (PID: %d)\n", child_pid);
        
        while (1) {
            pause();
        }
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}