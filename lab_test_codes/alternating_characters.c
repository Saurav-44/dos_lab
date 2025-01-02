#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define LIMIT 20

sem_t semaphore_A; // Semaphore to control thread A
sem_t semaphore_B; // Semaphore to control thread B

void* print_A(void* arg) {
    for (int i = 0; i < LIMIT / 2; i++) {
        sem_wait(&semaphore_A); // Wait until it's thread A's turn
        printf("A");
        sem_post(&semaphore_B); // Signal thread B to proceed
    }
    return NULL;
}

void* print_B(void* arg) {
    for (int i = 0; i < LIMIT / 2; i++) {
        sem_wait(&semaphore_B); // Wait until it's thread B's turn
        printf("B");
        sem_post(&semaphore_A); // Signal thread A to proceed
    }
    return NULL;
}

int main() {
    pthread_t thread_A, thread_B;

    // Initialize semaphores
    sem_init(&semaphore_A, 0, 1); // Start with thread A
    sem_init(&semaphore_B, 0, 0); // Thread B starts waiting

    // Create threads
    pthread_create(&thread_A, NULL, print_A, NULL);
    pthread_create(&thread_B, NULL, print_B, NULL);

    // Wait for threads to complete
    pthread_join(thread_A, NULL);
    pthread_join(thread_B, NULL);

    // Destroy semaphores
    sem_destroy(&semaphore_A);
    sem_destroy(&semaphore_B);

    printf("\n"); // Print a newline at the end
    return 0;
}
