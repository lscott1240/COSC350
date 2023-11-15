/*
 * Luke Scott
 * COSC 350
 * Lab 9 Task 2
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
	int file_pipes[2];
	const char some_data[] = "123";
	char buffer[BUFSIZ + 1];
	pid_t fork_result, p1;

	memset(buffer, '\0', sizeof(buffer));

	if (pipe(file_pipes) == 0) 
	{
		fork_result = fork();
		if (fork_result == (pid_t)-1) 
		{
			fprintf(stderr, "Fork failure");
			exit(EXIT_FAILURE);
		}
		
		if (fork_result == 0) 
		{
			close(file_pipes[0]);
			sprintf(buffer, "%d", file_pipes[0]);
			(void)execl("pipe4", "pipe4", buffer, (char *)0);
			exit(EXIT_FAILURE);
		}

		else
       		{
			wait(NULL);
			close(file_pipes[1]);
			data_processed = write(file_pipes[1], some_data,
			strlen(some_data));
			printf("%d - wrote %d bytes\n", getpid(), data_processed);
		}
	}
	exit(EXIT_SUCCESS);
}

