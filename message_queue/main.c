#include <stdio.h>

#include "msgque.h"

int main() {

	int msqid;
	char msg_aux[MSG_SIZE];
	Message msg;

	generate_arb_file();
	msqid = create_message_queue(ARB_FILE, 'x');

	fprintf(stdout, "Type a message.\n");
	scanf("%s", msg_aux);

	msg.mtype = MSG_NORMAL_TYPE;
	strcpy(msg.msg,msg_aux);
	sending_message(msqid, &msg, MSG_FLAG);
}
