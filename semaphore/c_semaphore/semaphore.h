#ifndef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
//#include <stdlib.h>
//#include <assert.h>
//#include <unistd.h>
//#include <string.h>
//#include <signal.h>
//#include <sys/stat.h>
#include <sys/sem.h>

#define SEMAPHORES_NUMBER 1

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct seminfo *__buf;
};


int create_semaphores(char *file_path, int sem_flags);

int initialize_semaphores(int semid);

void binary_semaphore_up(int semid);

void semaphore_wait_for_zero(int semid);

void binary_semaphore_down(int semid);

#endif
