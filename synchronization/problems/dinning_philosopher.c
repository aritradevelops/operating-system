/*
  Problem Statement:
  ------------------
  Solve the classical "Dining Philosophers Problem" using threads and semaphores.
  This problem models a scenario where a certain number of philosophers sit
  around a circular table, each with a plate of food in front of them. Between
  every two plates is a single spoon (shared between two adjacent philosophers).
  Each philosopher alternates between thinking and eating, but to eat, they
  need to pick up both spoons adjacent to their plate.

  Requirements:
  1. Philosophers can only eat if they have both spoons.
  2. Philosophers must release the spoons after eating so others can eat.
  3. Avoid deadlock: A situation where all philosophers hold one spoon and wait
     indefinitely for the other spoon to become available.
  4. Ensure fairness: No philosopher should starve.

  Solution:
  ---------
  - Use semaphores to represent the spoons.
  - Each philosopher picks up the left spoon first, then the right spoon.
  - After eating, the philosopher releases both spoons.
  !! While this solution mimics the problem, it suffers from potential deadlocks
  !!  if all philosophers pick up their left spoon at the same time and wait for
  !!  their right spoon.

  Implementation:
  ---------------
  - Create an array of semaphores (`spoons`) to represent the shared resources.
  - Use threads (`pthread`) to simulate the philosophers' behavior.
  - Each philosopher alternates between "thinking" and "eating."
  - Logs are printed to indicate the current activity of each philosopher.
*/

#include "../semaphore/custom_sem.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define PHILOSOPHER_COUNT 5 // Number of philosophers and spoons

// Array of semaphores to represent spoons
sem_t spoons[PHILOSOPHER_COUNT];

/*
  Philosopher Function:
  ---------------------
  Simulates the behavior of a philosopher who alternates between thinking
  and eating. To eat, the philosopher picks up the left spoon first, then
  the right spoon. After eating, the philosopher releases both spoons.
*/
void *think_and_eat(void *args) {
  int id = *(int *)args; // Philosopher ID
  printf("Philosopher %d: is thinking...\n", id);

  // Calculate the index of the left and right spoons
  int left_spoon = id;
  int right_spoon = (id + 1) % PHILOSOPHER_COUNT;

  // Pick up the left spoon
  sem_wait(&spoons[left_spoon]);
  // Pick up the right spoon
  sem_wait(&spoons[right_spoon]);

  // Eating
  printf("Philosopher %d: started eating. Using spoon (%d,%d)\n",
         id, left_spoon, right_spoon);
  sleep(1); // Simulate eating process
  printf("Philosopher %d: finished eating. Released spoon (%d,%d)\n",
         id, left_spoon, right_spoon);

  // Release the left spoon
  sem_signal(&spoons[left_spoon]);
  // Release the right spoon
  sem_signal(&spoons[right_spoon]);

  printf("Philosopher %d: is thinking again...\n", id);

  return NULL; // Exit thread
}

/*
  Main Function:
  --------------
  Initializes the semaphores, creates threads to simulate philosophers, and
  waits for all threads to finish.
*/
int main() {
  pthread_t philosophers[PHILOSOPHER_COUNT]; // Array of philosopher threads
  int philosopher_ids[PHILOSOPHER_COUNT];    // Array of philosopher IDs

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
