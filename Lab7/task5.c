/*
 * Luke Scott
 * COSC 350
 * Lab 7 Task 5
 * Dr. Park
*/

#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void hdl(int sig) {}

int main()
{
	sigset_t new_set, old_set;

	sigemptyset(&new_set);
	sigaddset(&new_set, SIGINT);
	sigaddset(&new_set, SIGQUIT);

	sigprocmask (SIG_BLOCK, &new_set, &old_set);

	printf ("Signals SIGINT and SIGQUIT are blocked\n");

	int i = 1;
	for (i; i < 6; i++)
	{
		sleep(1);
		printf("%d\n", i);
	}

	signal(SIGINT, &hdl);
	signal(SIGQUIT, &hdl);

	sigprocmask( SIG_UNBLOCK, &new_set, &old_set);
	sigemptyset(&new_set);
	sigaddset(&new_set, SIGINT);
	sigprocmask(SIG_BLOCK, &new_set, &old_set);
	printf("Signals SIGQUIT is now unblocked\n");

	signal(SIGQUIT, SIG_DFL);
	
	i = 1;
	for (i; i < 6; i++)
	{
		sleep(1);
		printf("%d\n", i);
	}
	exit (0);
}
