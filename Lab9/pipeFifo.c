/*
 * Luke Scott
 * COSC 350
 * Lab 9 Task 4
 * Dr. Park
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define TFIFO "/tmp/task4_fifo"

int main()
{
	umask(0000);
	int ffd;
	ffd = mkfifo("/tmp/task4_fifo", 0777);

	int data_processed;
	int fd;
	const char some_data[] = "123";
	char * buffer = (char*) malloc (strlen(some_data));
	int len = strlen(some_data);

	if ((fd = open("/tmp/task4_fifo", O_RDWR)) < 0)
	{
		printf("Fifo error\n");
		exit(1);
	}

	data_processed = write(fd, some_data, strlen(some_data));
	printf("Wrote %d bytes\n", data_processed);

	data_processed = read(fd, buffer, len);
	printf("Read %d bytes: %s\n", data_processed, buffer);
	close(fd);

	free(buffer);

	exit(EXIT_SUCCESS);
}
