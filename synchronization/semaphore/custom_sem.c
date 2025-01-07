#include "custom_sem.h"
#include <stdatomic.h>

void sem_init(sem_t *sem, int val) {
  atomic_init(sem, val);
}

void sem_wait(sem_t *sem) {
  int expected;
  do {
    // wait for other processes
    while ((expected = atomic_load(sem)) <= 0)
      ;

    // attempt to change its value if it have not
    // changed between last read and now ( via expected )
  } while (!atomic_compare_exchange_weak(sem, &expected, expected - 1));
}

void sem_signal(sem_t *sem) {
  atomic_fetch_add(sem, 1);
}