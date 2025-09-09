#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t child_pid, my_pid, parent_pid;

    child_pid = fork();

    if (child_pid < 0) {
        printf("Fork failed. Exiting!\n");
        exit(1);
    }

    if (child_pid == 0) {
        // Child process
        printf("[CHILD] This is the child process.\n");
        my_pid = getpid();
        parent_pid = getppid();
        printf("[CHILD] My pid is %d\n", my_pid);
        printf("[CHILD] My parent's pid is %d\n", parent_pid);
        printf("[CHILD] Exiting.\n");
        exit(0);
    } else {
        // Parent process
        printf("[PARENT] This is the parent process.\n");
        my_pid = getpid();
        parent_pid = getppid();
        printf("[PARENT] My pid is %d\n", my_pid);
        printf("[PARENT] My parent's pid is %d\n", parent_pid);

        printf("Sleeping for 10 seconds...\n");
        sleep(10); 

        printf("[PARENT] After sleep...\n");
        printf("[PARENT] Child pid = %d has ended but it has it's entry in the process table\n[PARENT] It is a zombie process\n", child_pid);
    }

    return 0;
}
