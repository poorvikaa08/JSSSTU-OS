#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
    pid_t my_pid, parent_pid, child_pid;
    child_pid = fork(); // Create a child process

    if(child_pid < 0){
        printf("\nFork failed. Exiting\n");
        exit(1);
    }

    if(child_pid == 0){
        printf("\n[CHILD] This is the child process.\n");
        my_pid = getpid();
        parent_pid = getppid();

        printf("[CHILD] My pid: %d, Parent pid: %d\n", my_pid, parent_pid);
        printf("[CHILD] Sleeping for 10 seconds...\n");
        sleep(10); // Child waits, parent will exit

        printf("[CHILD] After sleep, my parent process has ended, so I am now an orphan process.\n");
        printf("[CHILD] My new parent pid: %d\n", getppid());
        printf("[CHILD] I am adopted by init process\n");   
    } else {
        printf("\n[PARENT] This is the parent process.\n");
        my_pid = getpid();
        parent_pid = getppid();
        printf("[PARENT] My pid: %d, Parent pid: %d\n", my_pid, parent_pid);
        printf("[PARENT] Exiting quickly!\n");
        exit(0); // Parent exits quickly
    }

    return 0;
}