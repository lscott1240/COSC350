/*
 * Luke Scott
 * COSC 350
 * Lab 10 Task 3
 * Dr. Park
*/

#include <stdio.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdlib.h>
#include "header2.h"
#include <sys/ipc.h>
#include <sys/sem.h>

int main(int argc, char * argv [])
{
	key_t key;
	int shmid;
	int semid;
	struct Memory shm;
	union semun arg;
	key = ftok (".", 'x');
	if ((shmid = shmget(key, sizeof(struct Memory), 0)) < 0)
	{
		perror("shmget error \n");
		exit (1);
	}
	shmctl(shmid, IPC_RMID, NULL);
	if ((semid = semget(key, 3, 0)) == -1)
	{
		perror("semget error\n");
		exit(1);
	}
	if (semctl(semid, 0, IPC_RMID, arg) == -1)
	{
		perror("semctl error");
		exit(1);
	}
	return 0;
}
