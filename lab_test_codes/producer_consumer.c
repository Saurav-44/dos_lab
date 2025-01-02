#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10
#define ITERATIONS 20

int buffer[BUFFER_SIZE];
int in = 0, out = 0; // Indices for producer and consumer

sem_t empty;   // Semaphore to count empty slots in buffer
sem_t full;    // Semaphore to count full slots in buffer
pthread_mutex_t mutex; // Mutex to protect shared buffer

void* producer(void* arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        int item = rand() % 100 + 1; // Generate a random number (1 to 100)

        sem_wait(&empty); // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Lock the buffer

        buffer[in] = item; // Add item to buffer
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&full); // Signal that a full slot is available
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        sem_wait(&full); // Wait for a full slot
        pthread_mutex_lock(&mutex); // Lock the buffer

        int item = buffer[out]; // Remove item from buffer
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&empty); // Signal that an empty slot is available
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for both threads to complete
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
