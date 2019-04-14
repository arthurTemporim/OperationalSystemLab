#include "semaphore.h"

int main() {

    /*
	int semid = create_semaphores(ARB_FILE, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR); 
	initialize_semaphores(semid);

	semaphore_wait_for_zero(semid); // Start blocked

	binary_semaphore_down(semid); // Unlock B, Value = 0
	binary_semaphore_up(semid); // Value = 1
	semaphore_wait_for_zero(semid); // Block this till 0
    */
	return 0;
}
