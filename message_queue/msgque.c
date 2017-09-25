#include "msgque.h"

void generate_arb_file() {
	FILE *arb_file = fopen(ARB_FILE, "w");
	fclose(arb_file);
}

int create_message_queue(char *file_path, char ch) {
	generate_arb_file();
	key_t key = ftok(ARB_FILE, ch);
	int msqid = msgget(key, 0666 | IPC_CREAT);
}

void sending_message(int msqid, Message *msg, int flag) {
	if(msgsnd(msqid, msg, sizeof(Message), flag == -1)) {
		perror("Error while sending message.");
	}
}

void delete_message_queue(int msqid) {
	if(msgctl(msqid, IPC_RMID, NULL) == -1) {
		perror("Couldn't delete queue.");
	}
}

int receiving_message(int msqid, Message *msg, int arb_number, int flag) {
	struct msqid_ds buf;
	unsigned int amount_messages;

	do {
		if(msgctl(msqid, IPC_STAT, &buf)) {
			perror("Couldn't check this queue");
			exit(1);
		}
		amount_messages = buf.msg_qnum;
	} while(!amount_messages);

	int bytes = msgrcv(msqid, msg, sizeof(Message), ARB_NUMBER, MSG_FLAG);
}
