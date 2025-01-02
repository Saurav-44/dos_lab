#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore_A; // Semaphore for Thread A
sem_t semaphore_B; // Semaphore for Thread B

void* countdown(void* arg) {
    for (int i = 10; i >= 1; i--) {
        sem_wait(&semaphore_A); // Wait for Thread A's turn
        printf("Thread A: %d\n", i);
        sem_post(&semaphore_B); // Signal Thread B to proceed
    }
    return NULL;
}

void* countup(void* arg) {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&semaphore_B); // Wait for Thread B's turn
        printf("Thread B: %d\n", i);
        sem_post(&semaphore_A); // Signal Thread A to proceed
    }
    return NULL;
}

int main() {
    pthread_t thread_A, thread_B;

    // Initialize semaphores
    sem_init(&semaphore_A, 0, 1); // Start with Thread A
    sem_init(&semaphore_B, 0, 0); // Thread B starts waiting

    // Create threads
    pthread_create(&thread_A, NULL, countdown, NULL);
    pthread_create(&thread_B, NULL, countup, NULL);

    // Wait for threads to complete
    pthread_join(thread_A, NULL);
    pthread_join(thread_B, NULL);

    // Destroy semaphores
    sem_destroy(&semaphore_A);
    sem_destroy(&semaphore_B);

    return 0;
}
