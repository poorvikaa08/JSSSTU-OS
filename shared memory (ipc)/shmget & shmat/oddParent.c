#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/stat.h>

int main(int argc, char *argv[]){
    int i, shmid;
    pid_t pid;
    void *ptr;

    if(argc == 2){
        sscanf(argv[1], "%d", &i);
        if(i < 1){
            printf("Error input: %d\n", i);
            return 0;
        }
    }else{
        printf("Error: Not passing N in command line\n");
        exit(0);
    }

    // Create shared memory segment
    shmid = shmget((key_t)2024, 4096, 0666 | IPC_CREAT);
    ptr = shmat(shmid, NULL, 0666);
 
    pid = fork();
    if(pid == 0){
        // Child process - execute the odd number generator
        execlp("./odd", "odd", argv[1], NULL);
    }else if(pid > 0){
        // Parent process
        wait(NULL);
        printf("\nPARENT: Child completed\n");
        
        printf("Parent printing the first %d odd numbers:\n", i);
        printf("%s\n", (char*)ptr);
        
        // Detach from shared memory
        shmdt(ptr);
        
        // Remove shared memory segment
        shmctl(shmid, IPC_RMID, NULL);
    }


    return 0;
}
