#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define LIMIT 20

sem_t odd_semaphore;   
sem_t even_semaphore;  

void* print_odd(void* arg) {
    for (int i = 1; i <= LIMIT; i += 2) {
        sem_wait(&odd_semaphore);  
        printf("Thread A: %d\n", i);
        sem_post(&even_semaphore); 
    }
    return NULL;
}

void* print_even(void* arg) {
    for (int i = 2; i <= LIMIT; i += 2) {
        sem_wait(&even_semaphore);  
        printf("Thread B: %d\n", i);
        sem_post(&odd_semaphore); 
    }
    return NULL;
}

int main() {
    pthread_t thread_a, thread_b;

    
    sem_init(&odd_semaphore, 0, 1);  
    sem_init(&even_semaphore, 0, 0);

    
    pthread_create(&thread_a, NULL, print_odd, NULL);
    pthread_create(&thread_b, NULL, print_even, NULL);

    
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);

    
    sem_destroy(&odd_semaphore);
    sem_destroy(&even_semaphore);

    return 0;
}
