/*
 * Luke Scott
 * COSC 350
 * Lab 7 Task 4
 * Dr. Park
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handle(int sig)
{
	if (sig == SIGUSR1)
		printf("Hi honey! Anything wrong?\n");
	if (sig == SIGUSR2)
		printf("Did you make trouble again?\n");
}

int main()
{
	pid_t pid, pid2;
	pid = fork();

	if (pid < 0) 
	{
		perror("Fork error");
		exit (1);
	}

	else if (pid == 0)
	{
		printf("Waiting for signal from SIGUSR1...\n");
		sleep(2);
		kill(getppid(), SIGUSR1);
		exit(0);
	}

	else
	{
		signal(SIGUSR1, handle);
		pause();
		pid2 = fork();
		if (pid2 < 0)
		{
			perror("Fork error");
			exit(1);
		}
		
		else if (pid2 == 0)
		{		
			sleep(3);
			kill(getppid(), SIGUSR2);
			exit(0);
		}
		else
		{
			signal(SIGUSR2, handle);
			printf("Waiting for SIGUSR2 signal...\n");
			pause();
			exit(0);
		}
	}
}
