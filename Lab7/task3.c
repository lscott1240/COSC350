/*
 * Luke Scott
 * COSC 350
 * Lab 7 Task 3
 * Dr. Park
*/

#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

static int alarm_fired = 0;

void ding(int sig)
{
	alarm_fired = 1;
}

int main()
{
	pid_t pid;
	int nwrite, status, nread;
	char b[1];
	char * message = "Hello mama\n";
	printf("Beginning file processing\n");

	pid = fork();
	if (pid == -1)
	{
		perror ("fork error");
		exit (1);
	}

	else if (pid == 0)
	{
		umask(0000);
		nwrite = open("foo", O_WRONLY, 0755);

		write(nwrite, message, strlen(message));
		close(nwrite);
		_exit(0);
	}

	else
	{
		pid = wait(&status);
		message = "My son said ";
		write(1, message, strlen(message));
		nwrite = open("foo", O_RDONLY);
		while ((nread = read(nwrite, b, 1)) > 0)
		{
			write(1, b, nread);
		}
		close(nwrite);
	}

	exit(0);
}
