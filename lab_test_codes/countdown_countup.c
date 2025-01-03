#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore_A; 
sem_t semaphore_B; 

void* countdown(void* arg) {
    for (int i = 10; i >= 1; i--) {
        sem_wait(&semaphore_A); 
        printf("Thread A: %d\n", i);
        sem_post(&semaphore_B);
    }
    return NULL;
}

void* countup(void* arg) {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&semaphore_B); 
        printf("Thread B: %d\n", i);
        sem_post(&semaphore_A); 
    }
    return NULL;
}

int main() {
    pthread_t thread_A, thread_B;

    
    sem_init(&semaphore_A, 0, 1); 
    sem_init(&semaphore_B, 0, 0); 

    
    pthread_create(&thread_A, NULL, countdown, NULL);
    pthread_create(&thread_B, NULL, countup, NULL);

    
    pthread_join(thread_A, NULL);
    pthread_join(thread_B, NULL);

    
    sem_destroy(&semaphore_A);
    sem_destroy(&semaphore_B);

    return 0;
}
