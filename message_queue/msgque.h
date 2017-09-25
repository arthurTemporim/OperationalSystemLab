#ifndef MSGQUE_H
#define MSGQUE_H

#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MSG_SIZE 141
#define ARB_NUMBER 1
#define MSG_FLAG 0
#define ARB_FILE "../.arb_file"
#define MSG_NORMAL_TYPE 1

typedef struct Message {
	long mtype;
	char msg[MSG_SIZE];
} Message;

void generate_arb_file();

int create_message_queue(char *file_path, char ch);

void sending_message(int msqid, Message *msg, int flag);

int receiving_message(int msqid, Message *msg, int arb_number, int flag);

void delete_message_queue(int msqid);

#endif
