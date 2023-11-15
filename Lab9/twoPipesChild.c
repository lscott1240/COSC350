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

int main(int argc, char *argv[])
{
	int data_processed;
	char buffer[BUFSIZ + 1];
	char some_data[] = "Hi, Mom";
	int fd[2], fd1[2];

	sscanf(argv[1], "%d", &fd[0]);
	sscanf(argv[2], "%d", &fd[1]);
	sscanf(argv[3], "%d", &fd1[0]);
	sscanf(argv[4], "%d", &fd1[1]);

	memset(buffer, '\0', sizeof(buffer));
	
	close(fd[1]);
	close(fd1[0]);

	data_processed = read(fd[0], buffer, BUFSIZ);
	printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);

	data_processed = write(fd1[1], some_data, strlen(some_data));
	printf("%d - wrote %d bytes\n", getpid(), data_processed);

	exit(EXIT_SUCCESS);
}

