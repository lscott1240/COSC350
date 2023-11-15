/*
 * Luke Scott
 * COSC 350
 * Lab 10 Task 2
 * Dr. Park
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <errno.h>
#include "header.h"

int main(int argc, char * argv[])
{
	int shmid;
	key_t key;
	struct Memory * shm;
	int n[5];
	int counter;

	key = ftok(".", 'x');
	if ((shmid = shmget(key, sizeof(struct Memory), 0)) < 0)
	{
		perror("shmget error \n");
		exit (1);
	}

	shm = (struct Memory *) shmat (shmid, NULL, 0);
	if ((long)shm == -1)
	{
		perror("shmat error \n");
		exit (1);
	}
	shm->gostop = GO;
	shm->status = NOT_READY;

	counter = sizeof(shm->data.n) / sizeof(shm->data.n[0]);
	shm->data.i = 0;

	while (1)
	{
		int i, j;
		for (i = 0; i < counter; i++)
		{
			shm->data.n[i] = (rand() % (10)) + 1;
			shm->data.i++;
			if (shm->data.i == counter)
			{
				shm->status = FILLED;
				while (shm->status != TAKEN);
			}
			for (j = 0; j < counter; j++)
				printf("%d ", shm->data.n[j]);
			printf("\n");
			sleep(1);
		}
	}
	shm->gostop = STOP;
	shmdt((void *) shm);
	return 0;
}
