#include <stdio.h>

#include "msgque.h"

int main() {

	int msqid;
	char msg_aux[MSG_SIZE];
	Message send_msg;
	Message receive_msg;

	generate_arb_file();
	msqid = create_message_queue(ARB_FILE, 'x');

	fprintf(stdout, "Type a message.\n");
	scanf("%s", msg_aux);

	send_msg.mtype = MSG_NORMAL_TYPE;
	receive_msg.mtype = MSG_NORMAL_TYPE;

	strcpy(send_msg.msg,msg_aux);
	sending_message(msqid, &send_msg, MSG_FLAG);
	receiving_message(msqid, &receive_msg, ARB_NUMBER, MSG_FLAG);
	
	fprintf(stdout, "Message: %s.\n", receive_msg.msg);

	delete_message_queue(msqid);
	fprintf(stdout, "Message queue removed.\n");
	fprintf(stdout, "Done.\n");
}
