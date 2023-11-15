/*
 * Luke Scott
 * COSC 350
 * Lab 9 Task 3
 * Dr. Park
*/


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>


int main()
{
	int data_processed, status;
	int file_pipes[2], file_pipes2[2];
	const char some_data[] = "Hi there Kiddo";
	char buffer[BUFSIZ + 1];
	pid_t fork_result, p1;

	memset(buffer, '\0', sizeof(buffer));

	if (pipe(file_pipes) < 0)
	{
		printf("Error Pipe 1\n");
		exit (1);
	}

	if (pipe(file_pipes2) < 0)
	{
		printf("Error Pipe 2\n");
		exit (1);
	}

	fork_result = fork();
	if (fork_result == (pid_t)-1)
	{
		fprintf(stderr, "Fork failure");
		exit(EXIT_FAILURE);
	}

	if (fork_result == 0)
	{
		char fp0[BUFSIZ+1], fp1[BUFSIZ+1], fp20[BUFSIZ+1], fp21[BUFSIZ+1];

		memset(fp0, '\0', sizeof(fp0));
		memset(fp1, '\0', sizeof(fp1));
		memset(fp20, '\0', sizeof(fp20));
		memset(fp21, '\0', sizeof(fp21));

		sprintf(fp0, "%d", file_pipes[0]);
		sprintf(fp1, "%d", file_pipes[1]);
		sprintf(fp20, "%d", file_pipes2[0]);
		sprintf(fp21, "%d", file_pipes2[1]);

		(void)execl("twoPipesChild", "twoPipesChild", fp0, fp1, fp20, fp21, (char *)0);
		exit(EXIT_FAILURE);
	}

	else
	{
		close(file_pipes[0]);
		close(file_pipes2[1]);
		data_processed = write(file_pipes[1], some_data, strlen(some_data));
		printf("%d - wrote %d bytes\n", getpid(), data_processed);
		wait(&fork_result);
		data_processed = read(file_pipes2[0], buffer, BUFSIZ);
		printf("%d read %d bytes: %s\n", getpid(), data_processed, buffer);
	}
	exit(EXIT_SUCCESS);
}

