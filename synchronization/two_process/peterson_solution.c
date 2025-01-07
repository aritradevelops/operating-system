/*
  1. Mutual Exclusion: ✅
  2. Progress: ✅
 */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define PROCESS_ONE_ID 0
#define PROCESS_TWO_ID 1

volatile int turn = PROCESS_ONE_ID;
volatile bool flag[] = {false, false};

void *process_one(void *args) {
  while (true) {
    // initial section
    printf("P1: start executing\n");

    // express your desire to go into the critical section
    flag[PROCESS_ONE_ID] = true;
    // set the turn for the other process
    turn = PROCESS_TWO_ID;

    // wait until it's the other process's turn and the other process is interested
    while (flag[PROCESS_TWO_ID] && turn == PROCESS_TWO_ID) {
      printf("P1: waiting for P2 to complete\n");
    }

    // critical section
    printf("P1: entering into the critical section\n");
    sleep(1); // simulate task in critical section
    printf("P1: exiting from the critical section\n");

    // express unwillingness to continue into critical section
    flag[PROCESS_ONE_ID] = false;

    // remainder section
    break;
  }
  return NULL;
}

void *process_two(void *args) {
  while (true) {
    // initial section
    printf("P2: start executing\n");

    // express your desire to go into the critical section
    flag[PROCESS_TWO_ID] = true;
    // set the turn for the other process
    turn = PROCESS_ONE_ID;

    // wait until it's the other process's turn and the other process is interested
    while (flag[PROCESS_ONE_ID] && turn == PROCESS_ONE_ID) {
      printf("P2: waiting for P1 to complete\n");
    }

    // critical section
    printf("P2: entering into the critical section\n");
    sleep(1); // simulate task in critical section
    printf("P2: exiting from the critical section\n");

    // express unwillingness to continue into critical section
    flag[PROCESS_TWO_ID] = false;

    // remainder section
    break;
  }
  return NULL;
}
int main() {
  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, process_one, NULL);
  pthread_create(&thread2, NULL, process_two, NULL);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  return 0;
}