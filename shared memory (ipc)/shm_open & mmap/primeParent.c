#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>

int main(int argc, char *argv[]){
    int m, n, shm_fd;
    pid_t pid;
    const int SIZE = 4096;
    void *ptr;

    if(argc == 3){
        sscanf(argv[1], "%d", &m);
        sscanf(argv[2], "%d", &n);
        if(m < 1 || n < 1 || m > n){
            printf("Error: Invalid range. M and N should be positive and M <= N\n");
            printf("M = %d, N = %d\n", m, n);
            return 0;
        }
    }else{
        printf("Error: Please pass M and N as command line arguments\n");
        printf("Usage: %s <M> <N>\n", argv[0]);
        exit(0);
    }

    // Create shared memory object
    shm_fd = shm_open("/prime_numbers_shm", O_CREAT | O_RDWR, 0666);
    if(shm_fd == -1){
        perror("shm_open failed");
        exit(1);
    }
    
    // Set size of shared memory
    ftruncate(shm_fd, SIZE);
    
    pid = fork();
    if(pid == 0){
        // Child process - execute the prime number generator
        execlp("./prime", "prime", argv[1], argv[2], NULL);
    }else if(pid > 0){
        // Parent process
        wait(NULL);
        printf("\nPARENT: Child completed\n");
        
        // Open shared memory for reading
        shm_fd = shm_open("/prime_numbers_shm", O_RDONLY, 0666);
        
        // Map shared memory
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
        
        printf("Parent printing prime numbers between %d and %d:\n", m, n);
        printf("%s\n", (char*)ptr);
        
        // Cleanup
        munmap(ptr, SIZE);
        close(shm_fd);
        shm_unlink("/prime_numbers_shm");
    }


    return 0;
}
