#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define LIMIT 20

sem_t odd_semaphore;   // Semaphore to control odd numbers
sem_t even_semaphore;  // Semaphore to control even numbers

void* print_odd(void* arg) {
    for (int i = 1; i <= LIMIT; i += 2) {
        sem_wait(&odd_semaphore);  // Wait until it's the odd thread's turn
        printf("Thread A: %d\n", i);
        sem_post(&even_semaphore); // Signal the even thread
    }
    return NULL;
}

void* print_even(void* arg) {
    for (int i = 2; i <= LIMIT; i += 2) {
        sem_wait(&even_semaphore);  // Wait until it's the even thread's turn
        printf("Thread B: %d\n", i);
        sem_post(&odd_semaphore);  // Signal the odd thread
    }
    return NULL;
}

int main() {
    pthread_t thread_a, thread_b;

    // Initialize semaphores
    sem_init(&odd_semaphore, 0, 1);  // Start with the odd thread
    sem_init(&even_semaphore, 0, 0); // Even thread starts waiting

    // Create threads
    pthread_create(&thread_a, NULL, print_odd, NULL);
    pthread_create(&thread_b, NULL, print_even, NULL);

    // Wait for threads to complete
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);

    // Destroy semaphores
    sem_destroy(&odd_semaphore);
    sem_destroy(&even_semaphore);

    return 0;
}
