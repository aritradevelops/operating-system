/*
  1. Mutual Exclusion: ✅
  2. Progress: ❌ - it gives passes turn to the other process without it's will
 */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define PROCESS_ONE_TURN 1
#define PROCESS_TWO_TURN 0

volatile int turn = PROCESS_TWO_TURN;

void *process_one(void *args) {
  while (true) {
    // Initialization section
    printf("P1: Start Executing\n");

    // Wait until it's ProcessOne's turn
    while (turn != PROCESS_ONE_TURN) {
      printf("P1: Waiting for P2 to complete\n");
    }

    // Critical section
    printf("P1: Inside the critical section\n");
    sleep(1); // Simulate work in the critical section
    printf("P1: Exiting the critical section\n");

    // Give turn to ProcessTwo
    turn = PROCESS_TWO_TURN;

    // Remainder section
    break; // Exit loop for demonstration purposes
  }

  return NULL;
}

void *process_two(void *args) {
  while (true) {
    // Initialization section
    printf("P2: Start Executing\n");

    // Wait until it's ProcessTwo's turn
    while (turn != PROCESS_TWO_TURN) {
      printf("P2: Waiting for P1 to complete\n");
    }

    // Critical section
    printf("P2: Inside the critical section\n");
    sleep(1); // Simulate work in the critical section
    printf("P2: Exiting the critical section\n");

    // Give turn to ProcessOne
    turn = PROCESS_ONE_TURN;

    // Remainder section
    break; // Exit loop for demonstration purposes
  }

  return NULL;
}

int main() {
  // Threads for ProcessOne and ProcessTwo
  pthread_t thread1, thread2;

  // Create threads
  pthread_create(&thread1, NULL, process_one, NULL);
  pthread_create(&thread2, NULL, process_two, NULL);

  // Wait for both threads to finish
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  return 0;
}
