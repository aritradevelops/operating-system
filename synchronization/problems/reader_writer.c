/*
  Problem Description:
  --------------------
  This program implements a solution to the "Readers-Writers Problem" using custom semaphores.
  - Readers can read data concurrently as long as no writer is writing.
  - Writers require exclusive access to the data, meaning no other readers or writers can operate simultaneously.

  The solution uses two semaphores (`mutex` and `read_mutex`) to ensure synchronization and prevent race conditions.
*/

#include "../semaphore/custom_sem.h" // Custom semaphore implementation
#include "pthread.h"                 // POSIX thread library for multithreading
#include "stdio.h"                   // Standard I/O library
#include "unistd.h"                  // For sleep() function

// Number of readers and writers
#define READER_COUNT 5
#define WRITER_COUNT 2

// Semaphores
sem_t mutex;      // Ensures mutual exclusion for writers and readers modifying shared resources
sem_t read_mutex; // Protects the `reader_count` variable

// Shared data
volatile int reader_count = 0; // Tracks the number of active readers

/*
  Reader Thread Function:
  ------------------------
  Each reader:
  1. Increments the `reader_count` in a thread-safe manner.
  2. The first reader locks the `mutex` semaphore to block writers.
  3. Reads the data (simulated with sleep).
  4. Decrements the `reader_count` in a thread-safe manner.
  5. The last reader unlocks the `mutex` semaphore to allow writers.
*/
void *reader(void *args) {
  int id = *(int *)args; // Reader's ID

  // Step 1: Request access to increment reader_count
  sem_wait(&read_mutex);
  reader_count++;
  if (reader_count == 1) {
    sem_wait(&mutex); // First reader blocks writers
  }
  sem_signal(&read_mutex); // Release access to reader_count

  // Step 2: Perform reading
  printf("Reader %d: Start Reading...\n", id);
  sleep(1); // Simulate reading operation
  printf("Reader %d: End Reading...\n", id);

  // Step 3: Request access to decrement reader_count
  sem_wait(&read_mutex);
  reader_count--;
  if (reader_count == 0) {
    sem_signal(&mutex); // Last reader unblocks writers
  }
  sem_signal(&read_mutex); // Release access to reader_count

  return NULL;
}

/*
  Writer Thread Function:
  ------------------------
  Each writer:
  1. Waits for exclusive access to the shared resource by locking the `mutex` semaphore.
  2. Writes data (simulated with sleep).
  3. Releases the `mutex` semaphore to allow other readers or writers to access the resource.
*/
void *writer(void *args) {
  int id = *(int *)args; // Writer's ID

  // Step 1: Request exclusive access
  sem_wait(&mutex);

  // Step 2: Perform writing
  printf("Writer %d: Start Writing...\n", id);
  sleep(1); // Simulate writing operation
  printf("Writer %d: End Writing...\n", id);

  // Step 3: Release exclusive access
  sem_signal(&mutex);

  return NULL;
}

/*
  Main Function:
  ---------------
  1. Initializes the semaphores.
  2. Creates writer and reader threads.
  3. Waits for all threads to complete (joins them).
*/
int main() {
  // Initialize semaphores
  sem_init(&mutex, 1);      // `mutex` starts with value 1 (unlocked)
  sem_init(&read_mutex, 1); // `read_mutex` starts with value 1 (unlocked)

  // Create arrays for thread IDs
  pthread_t writer_threads[WRITER_COUNT];
  pthread_t reader_threads[READER_COUNT];
  int writer_ids[WRITER_COUNT];
  int reader_ids[READER_COUNT];

  // Create writer threads
  for (int i = 0; i < WRITER_COUNT; i++) {
    writer_ids[i] = i; // Assign unique IDs to writers
    pthread_create(&writer_threads[i], NULL, writer, &writer_ids[i]);
  }

  // Create reader threads
  for (int i = 0; i < READER_COUNT; i++) {
    reader_ids[i] = i; // Assign unique IDs to readers
    pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
  }

  // Wait for all writer threads to complete
  for (int i = 0; i < WRITER_COUNT; i++) {
    pthread_join(writer_threads[i], NULL);
  }

  // Wait for all reader threads to complete
  for (int i = 0; i < READER_COUNT; i++) {
    pthread_join(reader_threads[i], NULL);
  }

  return 0; // Program ends successfully
}
