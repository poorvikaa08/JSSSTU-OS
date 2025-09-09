#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<sys/shm.h>

int main(int argc, char *argv[]){
    int n, shmid;
    void *ptr;
    char temp[20];
    
    if(argc != 2){
        printf("Usage: %s <number_of_odd_numbers>\n", argv[0]);
        exit(1);
    }
    
    n = atoi(argv[1]);
    printf("CHILD: Generating %d odd numbers\n", n);
    
    // Connect to existing shared memory segment
    shmid = shmget((key_t)2024, 4096, 0666);  
    // Attach to shared memory
    ptr = shmat(shmid, NULL, 0666);
    
    
    // Initialize shared memory
    strcpy((char*)ptr, "");
    
    // Generate odd numbers and write to shared memory
    for(int i = 1; i <= n; i++){
        int odd_number = 2 * i - 1;  // Formula for nth odd number
        sprintf(temp, "%d ", odd_number);
        strcat((char*)ptr, temp);
        printf("Generated: %d\n", odd_number);
    }
    
    printf("CHILD: Finished generating odd numbers\n");
    
    // Detach from shared memory
    shmdt(ptr);
    
    return 0;
}
