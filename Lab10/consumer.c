/*
 * Luke Scott
 * COSC 350
 * Lab 10 Task 2
 * Dr. Park
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#include "header.h"

int main(int argc, char * argv [])
{
	key_t key;
	int shmid;
	struct Memory *shm;
	int counter;
	key = ftok(".", 'x');

	if ((shmid = shmget(key, sizeof(struct Memory), 0)) < 0)
	{
		perror("shmget error \n");
		exit (1);
	}

	shm = (struct Memory *) shmat(shmid, NULL, 0);
	if ((long) shm == -1)
	{
		perror("shmat error\n");
		exit (1);
	}

	while (shm->gostop == GO)
	{
		int i, j;
		counter = sizeof(shm->data.n) / sizeof(shm->data.n[0]);
		for (i = 0; i < counter; i++)
		{
			while (shm->data.i == 0)
				if (shm->gostop == STOP)
					break;
			shm->data.i--;
			shm->data.n[i] = 0;
			for (j = 0; j < counter; j++)
				printf("%d ", shm->data.n[j]);
			printf("\n");
			shm->status = TAKEN;
			sleep(1);
		}
	}
	shmdt((void *)shm);
	return 0;
}

