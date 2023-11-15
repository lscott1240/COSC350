/*
 * Luke Scott
 * COSC 350
 * Lab 7 Task 1
 * Dr. Park
*/

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static int alarm_fired = 0;

void ding(int sig)
{
	alarm_fired = 1;
}

int main()
{
	pid_t pid;

	printf("alarm application starting\n");

	struct sigaction act;
	memset(&act, 0, sizeof(act));
	act.sa_handler = ding;

	pid = fork();
	switch (pid)
	{
		case -1:
			perror("fork failed");
			exit(1);
		case 0:
			sleep(5);
			kill(getppid(), SIGALRM);
			_exit(0);
	}

	printf("waiting for alarm to go off\n");
	sigaction(SIGALRM, &act, 0);
	pause();
	if (alarm_fired)
		printf("Ding!\n");

	printf("done\n");
	exit(0);
}
