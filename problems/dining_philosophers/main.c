#include <stdio.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <unistd.h>

#define SHARED 1
#define INITIAL_SEM_VALUE -1

int main() {

	sem_t sem;
	sem_init(&sem, SHARED, INITIAL_SEM_VALUE);
	int semvalue=0;
	pid_t pid;
	pid = fork();
	if(pid) {
		fprintf(stdout,"PAI\n");
		sem_getvalue(&sem, &semvalue);
		fprintf(stdout,"ANTES  WAIT SEMAFORO %d\n", semvalue);
		// Begin Critical Region
		sem_wait(&sem);
		sem_getvalue(&sem, &semvalue);
		fprintf(stdout,"DEPOIS WAIT SEMAFORO %d\n", semvalue);
		fprintf(stdout,"Dentro PAI %d\n", getpid());
		sem_post(&sem);

		// Wait for the first son process die.
		wait();

	} else {

		fprintf(stdout,"FILHO\n");
		sleep(3);
		sem_getvalue(&sem, &semvalue);
		fprintf(stdout,"ANTES POST SEMAFORO %d\n", semvalue);
		// Begin Critical Region
		sem_post(&sem);
		sem_getvalue(&sem, &semvalue);
		fprintf(stdout,"DEPOIS POST SEMAFORO %d\n", semvalue);
		//sem_wait(&sem);
		fprintf(stdout,"Dentro FILHO %d\n", getpid());
	}

	sem_destroy(&sem);
	return 0;
}
