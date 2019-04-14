#include <stdio.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <unistd.h>

#define SEMAPHORES_NUMBER 1

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

int create_semaphores(char *file_path, int sem_flags) {
	key_t key = ftok(file_path, 'x');
	
	int semid = semget(key, SEMAPHORES_NUMBER, sem_flags);
	
	if(semid != -1) {
		return semid;
	} else {
		perror("Was not possible to allocate semaphores.");
	}
}

int initialize_semaphores(int semid){
    unsigned short SEMNUM_TH = 0;

    union semun argument;
    unsigned short values[1];
    values[0] = 1;
    argument.array = values;

    int code = semctl(semid, SEMNUM_TH, SETALL, argument);
    if(code != -1){
        return code;
    } else {
        perror("Wasn't possible intializing semaphores");
    }   
}

void binary_semaphore_up(int semid){
    struct sembuf operations[1];

    operations[0].sem_num = 0;
    operations[0].sem_op = 1;

    if(semop(semid, operations, 1)){
       perror("Wasn't possible to up the semaphore");
    }
}

void semaphore_wait_for_zero(int semid) {
    struct sembuf operations[1];

    operations[0].sem_num = 0;
    operations[0].sem_op = 0;

    if(semop(semid, operations, 1)){
       perror("Wasn't possible to down the semaphore");
    }
}

void binary_semaphore_down(int semid) {
    struct sembuf operations[1];

    operations[0].sem_num = 0;
    operations[0].sem_op = -1;

    if(semop(semid, operations, 1)){
       perror("Wasn't possible to down the semaphore");
    }
}

int main() {
	int semid = create_semaphores("/bin/ls", IPC_CREAT);
	initialize_semaphores(semid);
	fprintf(stdout, "Begining dinner.\n");

	pid_t pid = fork();
	if(pid) {
		fprintf(stdout, "PAI working. %d\n", getpid());
		binary_semaphore_down(semid);
		fprintf(stdout, "Inside semaphore PAI. %d\n", semid);
		binary_semaphore_up(semid);
		fprintf(stdout, "Outside semaphore PAI.\n");
	} else {
		fprintf(stdout, "Filho working.%d\n", getpid());
		binary_semaphore_down(semid);
		fprintf(stdout, "Inside semaphore FILHO. %d\n", semid);
		binary_semaphore_up(semid);
		fprintf(stdout, "Outside semaphore FILHO.\n");
	}

	
	return 0;
}	
