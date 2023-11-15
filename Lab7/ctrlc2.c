/*
 * Luke Scott
 * COSC 350
 * Lab 7 Task 2
 * Dr. Park
*/

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int count = 0;

void sig_handler(int sig)
{
	if (sig == SIGINT)
		printf("OUCH! - I got signal %d\n", sig);
	count++;
	//(void) signal(SIGINT, SIG_DFL);
}

int main()
{
	// Original ctrlc2.c //
	/*
	struct sigaction act;

	act.sa_handler = ouch;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGINT, &act, 0);

	while(1)
	{
		printf("Hello World!\n");
		sleep(1);
	}
	*/

	// Modified ctrlc2.c //	

	pid_t pid;
	pid = getpid();
	
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		printf("\nCan't catch SIGINT\n");

	while(1)
	{
		printf("Hello World!\n");
		sleep(1);

		if (count == 2)
			kill(pid,SIGKILL);
	}
}
