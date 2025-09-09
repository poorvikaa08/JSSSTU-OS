#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

sem_t wrt;
pthread_mutex_t mutex;
int readCount = 0, cnt = 1;

void *writer(void *wno) {
    sem_wait(&wrt); // Writer waits for the semaphore
    cnt++;
    printf("Writer %d incremented the shared variable to %d\n", (*(int *)wno), cnt);
    sem_post(&wrt); // Writer releases the semaphore
}

void *reader(void *rno) {
    pthread_mutex_lock(&mutex);
    readCount++;

    if(readCount == 1) {
        sem_wait(&wrt); // First reader locks the writer
    }
    pthread_mutex_unlock(&mutex);

    printf("Reader %d read the shared variable as %d\n", (*(int *)rno), cnt);
    pthread_mutex_lock(&mutex);
    readCount--;

    if(readCount == 0) {
        sem_post(&wrt); // Last reader unlocks the writer
    }
    pthread_mutex_unlock(&mutex);
}


int main() {
    pthread_t reader[3], writer[3];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    int arr[3] = {1, 2, 3};

    for(int i=0; i<3; i++){
        pthread_create(&reader[i], NULL, (void *)reader, (void *)&arr[i]);
    }

    for(int i=0; i<3; i++){
        pthread_create(&writer[i], NULL, (void *)writer, (void *)&arr[i]);
    }

    for(int i=0; i<3; i++){
        pthread_join(reader[i], NULL);
    }

    for(int i=0; i<3; i++){
        pthread_join(writer[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;

}