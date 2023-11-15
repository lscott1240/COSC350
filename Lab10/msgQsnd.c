/*
 * Luke Scott
 * COSC 350
 * Lab 10 Task 1
 * Dr. Park
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <errno.h>
#define SHSIZE 100

struct my_msgbuf {
	long mtype;
	char mtext[200];
};

int main(int argc, char *argv[])
{
	int msqid;
	key_t key;
	struct my_msgbuf buffer;
	key = ftok("msgQsnd.c", 'B');

	if ((msqid = msgget(key, 0644 | IPC_CREAT)) < 0)
	{
		perror("msgget error \n");
		exit (1);
	}
	
	printf("Enter two integers:\n");
	buffer.mtype = 1;	

	while (gets(buffer.mtext), !feof(stdin))
	{
		if (msgsnd(msqid, (struct msgbuf *) &buffer, sizeof(buffer), 0) == -1)
			perror("msgsnd error");
	}

	if (msgctl(msqid, IPC_RMID, NULL) == -1)
	{
		perror("msgctl error");
		exit(1);
	}
	exit (0);
}
