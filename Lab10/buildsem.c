/*
 * Luke Scott
 * COSC 350
 * LLab 10 Task 3
 * Dr. Park
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "header2.h"
#include <sys/types.h>

int main(int argc, char * argv [])
{
	int shmid;
	int semid;
	key_t key;
	struct Memory * shm;
	union semun arg;
	key = ftok(".", 'x');
	if ((shmid = shmget(key, sizeof(struct Memory), IPC_CREAT | 0666)) < 0)
	{
		perror("shmget error \n");
		exit(1);
	}
	shm = (struct Memory *) shmat(shmid, NULL, 0);
	if ((long)shm == -1)
	{
		perror("shmat error\n");
		exit(1);
	}

	if ((semid = semget(key, 4, 0666 | IPC_CREAT)) == -1)
	{
		perror("semget Error\n");
		exit(1);
	}

	arg.val = 1;
	if (semctl(semid, MUTEX, SETVAL, arg) == -1)
	{
		perror("semctl error\n");
		exit(1);
	}

	arg.val = N;
	if (semctl(semid, EMPTY, SETVAL, arg) == -1)
	{
		perror("semctl error\n");
		exit (1);
	}

	arg.val = 0;
	if (semctl(semid, FULL, SETVAL, arg) == -1)
	{
		perror("semctl error");
		exit(1);
	}
	shm->status = NOT_READY;
	shm->gostop = GO;
	return 0;
}
