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

int main(int argc, char * argv[])
{
	int msqid;
	key_t key;
	struct my_msgbuf buffer;
	int int1, int2;
	char * char1, char2;

	if ((key = ftok("msgQsnd.c", 'B')) == -1)
	{
		perror("ftok error \n");
		exit (1);
	}

	if ((msqid = msgget(key, 0644)) == -1)
	{
		perror("msgget error \n");
		exit (1);
	}

	printf("Waiting for integers.\n");

	for (;;)
	{
		if (msgrcv(msqid, (struct msgbuf *)&buffer, sizeof(buffer), 0, 0) == -1)
		{
			perror("msgrcv error");
			exit(1);
		}

		if (sscanf(buffer.mtext, "%d%d", &int1, &int2) == 2)
			printf("%d + %d = %d\n", int1, int2, int1 + int2);
		else
			printf("Message did not include two integers\n");	
	}
	return 0;
}
