#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int SUM = 0, PROD = 1;

void *sum(void *arg){
    int n;
    n = atoi(arg);

    printf("Inside sum thread\n");

    for(int i=1; i<=n; i++){
        SUM += i;
    }

    printf("\nSum thread completed!");
}

void *mul(void *arg){
    int n;
    n = atoi(arg);

    printf("Inside mul thread\n");

    for(int i=1; i<=n; i++){
        PROD *= i;
    }

    printf("\nMul thread complted!");
}

void main(int argc, char* argv[]){
    if(argc < 2){
        printf("Usage: %s <number>\n", argv[0]);
        return;
    }
    int n = atoi(argv[1]);

    pthread_t T1, T2;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_create(&T1, &attr, sum, argv[1]);
    pthread_create(&T2, &attr, mul, argv[1]);

    pthread_join(T1, NULL);
    pthread_join(T2, NULL); 
    
    printf("\nInside main thread\n"); 

    printf("Sum: %d\n", SUM);
    printf("Factorial: %d\n", PROD);

}