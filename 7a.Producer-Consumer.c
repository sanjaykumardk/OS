#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5 // size of the buffer

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty;     // Semaphore for empty slots
sem_t full;      // Semaphore for full slots
pthread_mutex_t mutex; // Mutex for critical section

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100; // produce an item

        sem_wait(&empty); // wait if buffer is full
        pthread_mutex_lock(&mutex); // enter critical section

        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex); // exit critical section
        sem_post(&full); // signal that item is produced

        sleep(1); // simulate time taken to produce
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full); // wait if buffer is empty
        pthread_mutex_lock(&mutex); // enter critical section

        item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex); // exit critical section
        sem_post(&empty); // signal that item is consumed

        sleep(2); // simulate time taken to consume
    }
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, SIZE); // initially buffer is empty
    sem_init(&full, 0, 0);     // initially buffer has 0 full slots
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
