/*
  Problem Statement:
  ------------------
  Implement a producer-consumer problem using threads and semaphores to manage
  synchronization between the producer and consumer threads. The producer generates
  items and adds them to a bounded buffer, while the consumer removes items from
  the buffer. The buffer has a fixed size, and the producer must wait if the buffer
  is full, while the consumer must wait if the buffer is empty.

  Requirements:
  1. Use semaphores to ensure mutual exclusion and synchronization.
  2. Stop the program after producing and consuming a fixed number of items.
  3. Ensure no race conditions or deadlocks occur.
  4. Output logs for each production and consumption activity.

  Constants:
  - BUFFER_SIZE: Size of the shared buffer.
  - MAX_ITEMS: Total number of items to be produced and consumed.

  Solution:
  - Use three semaphores:
    1. `mutex`: Binary semaphore for mutual exclusion in critical sections.
    2. `empty`: Counting semaphore to track the number of empty slots in the buffer.
    3. `full`: Counting semaphore to track the number of filled slots in the buffer.
  - Use a circular buffer to manage the items produced and consumed.
  - Use pthreads to create producer and consumer threads.

  Implementation:
*/

#include "../semaphore/custom_sem.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5 // Size of the shared buffer
#define MAX_ITEMS 20  // Maximum number of items to produce/consume

// Shared buffer and state variables
int buffer[BUFFER_SIZE]; // Circular buffer
int in = 0;              // Index to place the next produced item
int out = 0;             // Index to remove the next consumed item
int produced_count = 0;  // Total items produced
int consumed_count = 0;  // Total items consumed

// Semaphores for synchronization
sem_t mutex; // Binary semaphore for mutual exclusion
sem_t full;  // Semaphore to count filled slots in the buffer
sem_t empty; // Semaphore to count empty slots in the buffer

/*
  Producer Function:
  ------------------
  Continuously produces items and adds them to the buffer. Waits if the buffer is
  full and stops after producing MAX_ITEMS.
*/
void *producer(void *arg) {
  int item = 1; // Initial item value

  while (1) {
    sem_wait(&empty); // Wait if the buffer is full
    sem_wait(&mutex); // Enter critical section

    // Produce an item if limit is not reached
    if (produced_count < MAX_ITEMS) {
      buffer[in] = item;              // Place item in the buffer
      printf("Produced: %d\n", item); // Log production
      item++;                         // Increment item value for the next production
      in = (in + 1) % BUFFER_SIZE;    // Update buffer index
      produced_count++;               // Increment produced count
    } else {
      sem_signal(&mutex);
      sem_signal(&full);
      break; // Exit loop after reaching MAX_ITEMS
    }

    sem_signal(&mutex); // Exit critical section
    sem_signal(&full);  // Signal that a buffer slot is filled
  }

  pthread_exit(NULL);
}

/*
  Consumer Function:
  ------------------
  Continuously consumes items from the buffer. Waits if the buffer is empty and
  stops after consuming MAX_ITEMS.
*/
void *consumer(void *arg) {
  while (1) {
    sem_wait(&full);  // Wait if the buffer is empty
    sem_wait(&mutex); // Enter critical section

    // Consume an item if limit is not reached
    if (consumed_count < MAX_ITEMS) {
      int item = buffer[out];         // Retrieve item from the buffer
      printf("Consumed: %d\n", item); // Log consumption
      out = (out + 1) % BUFFER_SIZE;  // Update buffer index
      consumed_count++;               // Increment consumed count
    } else {
      sem_signal(&mutex);
      sem_signal(&empty);
      break; // Exit loop after reaching MAX_ITEMS
    }

    sem_signal(&mutex); // Exit critical section
    sem_signal(&empty); // Signal that a buffer slot is empty
  }

  pthread_exit(NULL);
}

/*
  Main Function:
  --------------
  Initializes semaphores, creates producer and consumer threads, and waits for
  them to finish.
*/
int main() {
  pthread_t producer_t, consumer_t; // Thread identifiers

  // Initialize semaphores
  sem_init(&mutex, 1);           // Binary semaphore for mutual exclusion
  sem_init(&empty, BUFFER_SIZE); // Initially all buffer slots are empty
  sem_init(&full, 0);            // Initially no buffer slots are filled

  // Create producer and consumer threads
  pthread_create(&producer_t, NULL, producer, NULL);
  pthread_create(&consumer_t, NULL, consumer, NULL);

  // Wait for threads to complete
  pthread_join(producer_t, NULL);
  pthread_join(consumer_t, NULL);

  return 0;
}
