/*
  Over simplified version of semaphores
  1. Mutual Exclusion: ✅
  2. Progress: ❌ - chances of DeadLock
 */

#include "custom_sem.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#define PROCESS_COUNT 5

volatile sem_t sem;

void *process(void *args) {
  int pid = *(int *)args;
  while (true) {
    // initial section
    printf("P%d: start execution \n", pid);

    // wait for other processes to complete
    sem_wait(&sem);

    // critical section
    printf("P%d: entering into critical section \n", pid);
    sleep(1); // simulate critical task
    printf("P%d: exiting from critical section \n", pid);

    // signal other processes that you are done
    sem_signal(&sem);
    // remainder section
    break;
  }
  return NULL;
}

int main() {
  sem_init(&sem, 1);
  pthread_t threads[PROCESS_COUNT];
  int thread_ids[PROCESS_COUNT];
  for (int i = 0; i < PROCESS_COUNT; ++i) {
    thread_ids[i] = i;
    pthread_create(&threads[i], NULL, process, &thread_ids[i]);
  }
  for (int i = 0; i < PROCESS_COUNT; ++i) {
    pthread_join(threads[i], NULL);
  }
}