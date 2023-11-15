/*
 * Luke Scott
 * COSC 350
 * Lab 9 Task 5
 * Dr. Park
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include "header.h"

int main(int argc, char * argv [])
{
	key_t key;
	int shmid;
	struct Memory *shm;
	key = ftok(".", 'x');
	if ((shmid = shmget(key, sizeof(struct Memory), 0)) < 0)
	{
		perror("shmget error\n");
		exit(1);
	}

	shm = (struct Memory *) shmat(shmid, NULL, 0);
	if ((long) shm == -1)
	{
		perror("shmat error\n");
		exit(1);
	}

	while (shm->gostop == GO)
	{
		while(shm->status != FILLED)
		{
			if (shm->gostop == STOP)
				break;
			;
		}
		printf("Sum of the two integers: %d\n", shm->data.int1 + shm->data.int2);
		shm->status = TAKEN;
	}
	shmdt((void *)shm);
	return 0;
}
