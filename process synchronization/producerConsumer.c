#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define MAX 5
#define SIZE 5 

sem_t empty, full;
pthread_mutex_t mutex;
int in = 0, out = 0;
int buffer[SIZE];

void* producer(void *pno) {
    int item;

    for(int i = 0; i< MAX; i++){
        item = rand() % 100;

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;

        printf("Producer %d produced an item %d at %d\n", (*(int*)pno), item, in);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }   
}

void* consumer(void* cno ){
    for(int i =0; i<MAX; i++){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer %d consumed an item %d from %d\n", (*(int*)cno), item, out);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main() {
    pthread_t pro[5], con[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);

    int a[5] = {1, 2, 3, 4, 5}; //Just used for numbering the producer and consumer

    for(int i = 0; i < 5; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    for(int i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}


