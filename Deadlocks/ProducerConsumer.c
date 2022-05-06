// Write a program to demonstrate Producer consumer problem with semaphore

#include <pthread.h>   // pthread library
#include <semaphore.h> // semaphore library
#include <stdio.h>     // standard input output library
#include <unistd.h>    // sleep()

// Define constants
#define MAX_BUFFER_SIZE 5

// Use a structure indicate a buffer
typedef struct buffer_t {
    int buffer[MAX_BUFFER_SIZE];
    int front;
    int rear;
    int count;
    sem_t mutex;
    sem_t empty;
    sem_t full;
} buffer_t;

// Create producer and consumer threads
void *producer(void *arg);
void *consumer(void *arg);

int main(int argc, char const *argv[]) {
    // Take input for number of producers and consumers
    int num_producers, num_consumers;
    printf("Enter number of producers: ");
    scanf("%d", &num_producers);
    printf("Enter number of consumers: ");
    scanf("%d", &num_consumers);

    // Create a buffer
    buffer_t buffer;

    // Initialize the buffer
    buffer.front = 0;
    buffer.rear = 0;
    buffer.count = 0;
    sem_init(&buffer.mutex, 0, 1);
    sem_init(&buffer.empty, 0, MAX_BUFFER_SIZE);
    sem_init(&buffer.full, 0, 0);

    // Create producer threads
    pthread_t producer_threads[num_producers];

    // Create consumer threads
    pthread_t consumer_threads[num_consumers];

    // Create producer threads
    for (int i = 0; i < num_producers; i++) {
        pthread_create(&producer_threads[i], NULL, producer, &buffer);
    }

    // Create consumer threads
    for (int i = 0; i < num_consumers; i++) {
        pthread_create(&consumer_threads[i], NULL, consumer, &buffer);
    }

    // Wait for all producer threads to complete
    for (int i = 0; i < num_producers; i++) {
        pthread_join(producer_threads[i], NULL);
    }

    // Wait for all consumer threads to complete
    for (int i = 0; i < num_consumers; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    // Destroy the semaphores
    sem_destroy(&buffer.mutex);
    sem_destroy(&buffer.empty);
    sem_destroy(&buffer.full);

    // Exit the program

    return 0;
}

// Producer thread, with printf statements
void *producer(void *arg) {
    // Cast the argument to buffer_t type
    buffer_t *buffer = (buffer_t *)arg;

    // Produce items
    for (int i = 0; i < 10; i++) {
        // Wait for empty slot
        sem_wait(&buffer->empty);

        // Wait for exclusive access
        sem_wait(&buffer->mutex);

        // Produce an item
        buffer->buffer[buffer->rear] = i;
        buffer->rear = (buffer->rear + 1) % MAX_BUFFER_SIZE;
        buffer->count++;

        // Release exclusive access
        sem_post(&buffer->mutex);

        // Release full slot
        sem_post(&buffer->full);

        // Explain who is producing
        printf("Producer %lu produced item %d\n", pthread_self(), i);

        // Sleep for a while
        sleep(1);
    }

    // Exit the thread
    pthread_exit(NULL);
}

// Consumer thread, with printf statements
void *consumer(void *arg) {
    // Cast the argument to buffer_t type
    buffer_t *buffer = (buffer_t *)arg;

    // Consume items
    for (int i = 0; i < 10; i++) {
        // Wait for full slot
        sem_wait(&buffer->full);

        // Wait for exclusive access
        sem_wait(&buffer->mutex);

        // Consume an item
        int item = buffer->buffer[buffer->front];
        buffer->front = (buffer->front + 1) % MAX_BUFFER_SIZE;
        buffer->count--;

        // Release exclusive access
        sem_post(&buffer->mutex);

        // Release empty slot
        sem_post(&buffer->empty);

        // Explain who is consuming
        printf("Consumer %lu consumed item %d\n", pthread_self(), item);

        // Sleep for a while
        sleep(1);
    }

    // Exit the thread
    pthread_exit(NULL);
}