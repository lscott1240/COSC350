/*
 * Luke Scott
 * COSC 350
 * Lab 3 Task 5
 * Dr. Park
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void err_sys(char *str)
{
	printf ("%s", str);
	exit (1);
}

int main()
{
	int file1read, nwrite, buffer;

	if ((file1read = open("foo", O_RDONLY)) < 0)
		err_sys("Create File Open Error");

	if ((buffer = lseek(file1read, 0, SEEK_END)) == -1)
		err_sys("Create lseek Error");

	nwrite = open("foorev", O_RDWR | O_EXCL | O_CREAT, 0760);

	char b[buffer];

	umask(0);
	int i = 0;
	if (file1read != -1 && nwrite != -1)
	{
		while (i <= buffer)
		{
			if (lseek(file1read, buffer - i, SEEK_SET) == -1)
				err_sys("Create lseek Error");
			read(file1read, b, 1);
			if ((write (nwrite, b, 1) != 1))
				err_sys("Create Write Error");
			i++;
		}
	}

	else
		err_sys("Filename: foorev already exists");

	close(file1read);
	close(nwrite);

	return 0;
}
