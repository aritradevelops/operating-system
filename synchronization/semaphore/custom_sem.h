#ifndef __CUSTOM_SEMAPHORE_H
#define __CUSTOM_SEMAPHORE_H
#include <stdatomic.h>
typedef volatile atomic_int sem_t;

void sem_init(sem_t *, int);

void sem_wait(sem_t *);

void sem_signal(sem_t *);

#endif