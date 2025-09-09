#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>

// Function to check if a number is prime
int isPrime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[]){
    int m, n, shm_fd;
    const int SIZE = 4096;
    void *ptr;
    char temp[20];
    
    if(argc != 3){
        printf("Usage: %s <start_range> <end_range>\n", argv[0]);
        exit(1);
    }
    
    m = atoi(argv[1]);
    n = atoi(argv[2]);
    
    if(m > n){
        printf("Error: Start range should be less than or equal to end range\n");
        exit(1);
    }
    
    printf("CHILD: Generating prime numbers between %d and %d\n", m, n);
    
    // Open existing shared memory object
    shm_fd = shm_open("/prime_numbers_shm", O_RDWR, 0666);
    if(shm_fd == -1){
        perror("shm_open failed in child");
        exit(1);
    }
    
    // Map shared memory
    ptr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(ptr == MAP_FAILED){
        perror("mmap failed in child");
        exit(1);
    }
    
    // Initialize shared memory
    strcpy((char*)ptr, "");
    
    // Generate prime numbers and write to shared memory
    int count = 0;
    for(int i = m; i <= n; i++){
        if(isPrime(i)){
            sprintf(temp, "%d ", i);
            strcat((char*)ptr, temp);
            printf("Generated prime: %d\n", i);
            count++;
        }
    }
    
    if(count == 0){
        strcpy((char*)ptr, "No prime numbers found in the given range");
    }
    
    printf("CHILD: Finished generating %d prime numbers\n", count);
    
    // Unmap shared memory
    munmap(ptr, SIZE);
    
    // Close shared memory descriptor
    close(shm_fd);
    
    return 0;
}
