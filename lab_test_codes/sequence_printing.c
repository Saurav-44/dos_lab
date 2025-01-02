#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define LIMIT 20

sem_t semaphore_A; // Semaphore for Thread A
sem_t semaphore_B; // Semaphore for Thread B
sem_t semaphore_C; // Semaphore for Thread C

void* print_A(void* arg) {
    for (int i = 1; i <= LIMIT; i += 3) {
        sem_wait(&semaphore_A); // Wait for Thread A's turn
        printf("A%d\n", i);
        sem_post(&semaphore_B); // Signal Thread B to proceed
    }
    return NULL;
}

void* print_B(void* arg) {
    for (int i = 2; i <= LIMIT; i += 3) {
        sem_wait(&semaphore_B); // Wait for Thread B's turn
        printf("B%d\n", i);
        sem_post(&semaphore_C); // Signal Thread C to proceed
    }
    return NULL;
}

void* print_C(void* arg) {
    for (int i = 3; i <= LIMIT; i += 3) {
        sem_wait(&semaphore_C); // Wait for Thread C's turn
        printf("C%d\n", i);
        sem_post(&semaphore_A); // Signal Thread A to proceed
    }
    return NULL;
}

int main() {
    pthread_t thread_A, thread_B, thread_C;

    // Initialize semaphores
    sem_init(&semaphore_A, 0, 1); // Start with Thread A
    sem_init(&semaphore_B, 0, 0); // Thread B starts waiting
    sem_init(&semaphore_C, 0, 0); // Thread C starts waiting

    // Create threads
    pthread_create(&thread_A, NULL, print_A, NULL);
    pthread_create(&thread_B, NULL, print_B, NULL);
    pthread_create(&thread_C, NULL, print_C, NULL);

    // Wait for threads to complete
    pthread_join(thread_A, NULL);
    pthread_join(thread_B, NULL);
    pthread_join(thread_C, NULL);

    // Destroy semaphores
    sem_destroy(&semaphore_A);
    sem_destroy(&semaphore_B);
    sem_destroy(&semaphore_C);

    return 0;
}
