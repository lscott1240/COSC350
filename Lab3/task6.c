/*
 * Luke Scott
 * COSC 350
 * Lab 3 Task 6
 * Dr. Park
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1

void err_sys(char *str)
{
	printf ("%s", str);
	exit (1);
}

int main()
{
	int nread, nwrite, end = 0;
	char b[BUFFER_SIZE];

	if ((nread = open("foo", O_RDONLY)) < 0)
		err_sys("Create File Open Error");

	if ((nwrite = open("foorev", O_RDWR | O_EXCL | O_CREAT, 0760)) < 0)
		err_sys("Create File Write Error");

	umask(0);

	while (read(nread,&b,1) == 1)
		end++;

	while (end > 0)
	{
		if ((pread(nread, &b, BUFFER_SIZE, end-1)) == -1)
			err_sys("File Read Error");
		if (write (nwrite, &b, 1) == -1)
			err_sys("File Write Error");
		end--;
	}

	close(nread);
	close(nwrite);

	return 0;
}
