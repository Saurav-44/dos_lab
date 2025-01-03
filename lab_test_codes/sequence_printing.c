#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define LIMIT 20

sem_t semaphore_A; 
sem_t semaphore_B; 
sem_t semaphore_C; 

void* print_A(void* arg) {
    for (int i = 1; i <= LIMIT; i += 3) {
        sem_wait(&semaphore_A); 
        printf("A%d\n", i);
        sem_post(&semaphore_B); 
    }
    return NULL;
}

void* print_B(void* arg) {
    for (int i = 2; i <= LIMIT; i += 3) {
        sem_wait(&semaphore_B); 
        printf("B%d\n", i);
        sem_post(&semaphore_C); 
    }
    return NULL;
}

void* print_C(void* arg) {
    for (int i = 3; i <= LIMIT; i += 3) {
        sem_wait(&semaphore_C); 
        printf("C%d\n", i);
        sem_post(&semaphore_A); 
    }
    return NULL;
}

int main() {
    pthread_t thread_A, thread_B, thread_C;

    
    sem_init(&semaphore_A, 0, 1); 
    sem_init(&semaphore_B, 0, 0); 
    sem_init(&semaphore_C, 0, 0); 

    
    pthread_create(&thread_A, NULL, print_A, NULL);
    pthread_create(&thread_B, NULL, print_B, NULL);
    pthread_create(&thread_C, NULL, print_C, NULL);

    
    pthread_join(thread_A, NULL);
    pthread_join(thread_B, NULL);
    pthread_join(thread_C, NULL);

    
    sem_destroy(&semaphore_A);
    sem_destroy(&semaphore_B);
    sem_destroy(&semaphore_C);

    return 0;
}
