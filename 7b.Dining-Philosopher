#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 // Number of philosophers

sem_t forks[N]; // One semaphore per fork

void* philosopher(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking\n", id);
        sleep(rand() % 3 + 1);

        // Hungry
        printf("Philosopher %d is hungry\n", id);

        // Pick up left fork
        sem_wait(&forks[left]);
        printf("Philosopher %d picked up left fork %d\n", id, left);

        // Pick up right fork
        sem_wait(&forks[right]);
        printf("Philosopher %d picked up right fork %d\n", id, right);

        // Eating
        printf("Philosopher %d is eating\n", id);
        sleep(rand() % 2 + 1);

        // Put down right fork
        sem_post(&forks[right]);
        printf("Philosopher %d put down right fork %d\n", id, right);

        // Put down left fork
        sem_post(&forks[left]);
        printf("Philosopher %d put down left fork %d\n", id, left);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    // Initialize semaphores
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
        ids[i] = i;
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join threads (infinite loop, so this won't return)
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Cleanup (not reached)
    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
