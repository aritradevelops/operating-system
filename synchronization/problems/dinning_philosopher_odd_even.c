#include "../semaphore/custom_sem.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define PHILOSOPHER_COUNT 5

sem_t spoons[PHILOSOPHER_COUNT];

/*
  Philosopher Function:
  ---------------------
  Alternates the order of picking up spoons based on the philosopher's ID.
  - Odd philosophers pick the left spoon first.
  - Even philosophers pick the right spoon first.
*/
void *think_and_eat(void *args) {
  int id = *(int *)args; // Philosopher ID
  printf("Philosopher %d: is thinking...\n", id);

  int left_spoon = id;
  int right_spoon = (id + 1) % PHILOSOPHER_COUNT;

  if (id % 2 == 0) {
    // Even philosophers pick the right spoon first
    sem_wait(&spoons[right_spoon]);
    sem_wait(&spoons[left_spoon]);
  } else {
    // Odd philosophers pick the left spoon first
    sem_wait(&spoons[left_spoon]);
    sem_wait(&spoons[right_spoon]);
  }

  // Eating
  printf("Philosopher %d: started eating. Using spoon (%d,%d)\n",
         id, left_spoon, right_spoon);
  sleep(1); // Simulate eating
  printf("Philosopher %d: finished eating. Released spoon (%d,%d)\n",
         id, left_spoon, right_spoon);

  // Release spoons
  sem_signal(&spoons[left_spoon]);
  sem_signal(&spoons[right_spoon]);

  printf("Philosopher %d: is thinking again...\n", id);
  return NULL;
}

int main() {
  pthread_t philosophers[PHILOSOPHER_COUNT];
  int philosopher_ids[PHILOSOPHER_COUNT];

  // Initialize semaphores for spoons
  for (int j = 0; j < PHILOSOPHER_COUNT; j++) {
    sem_init(&spoons[j], 1);
  }

  // Create threads for each philosopher
  for (int i = 0; i < PHILOSOPHER_COUNT; ++i) {
    philosopher_ids[i] = i;
    pthread_create(&philosophers[i], NULL, think_and_eat, &philosopher_ids[i]);
  }

  // Wait for all philosopher threads to finish
  for (int i = 0; i < PHILOSOPHER_COUNT; ++i) {
    pthread_join(philosophers[i], NULL);
  }

  return 0;
}
