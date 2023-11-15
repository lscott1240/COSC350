/*
 * Luke Scott
 * COSC 350
 * Lab 9 Task 5
 * Dr. Park
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <errno.h>
#include "header.h"

int main(int argc, char * argv [])
{
	int shmid;
	key_t key;
	struct Memory *shm;
	int n, n2;
	key = ftok(".", 'x');
	if ((shmid = shmget(key, sizeof(struct Memory), 0)) < 0)
	{
		perror("shmget error \n");
		exit(1);
	}

	shm = (struct Memory *) shmat(shmid, NULL, 0);
	if ((long)shm == -1)
	{
		perror("shmat error \n");
		exit(1);
	}

	shm->gostop = GO;
	shm->status = NOT_READY;

	char buffer[BUFSIZ+1];
	memset(buffer, '\0', sizeof(buffer));
	printf("Enter two integers: \n");
	while (read(0, buffer, BUFSIZ) > 0)
	{
		if (sscanf(buffer, "%d%d", &n, &n2) == 2)
		{
			shm->data.int1 = n;
			shm->data.int2 = n2;
			shm->status = FILLED;
			while (shm->status != TAKEN)
				;
			printf("Enter two integers: \n");
		}
		else
			printf("Invalid integers\n Enter two integers:\n");
	}
	
	shm->gostop = STOP;
	shmdt((void *) shm);
	return 0;
}
