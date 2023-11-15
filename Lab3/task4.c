/*
 * Luke Scott
 * COSC 350
 * Lab 3 Task 4
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
	int file1read, file2read, nwrite;

	if ((file1read = open("foo", O_RDONLY)) < 0)
		err_sys("Create File Open Error");

	if ((file2read = open("foo1", O_RDONLY)) < 0)
		err_sys("Create File1 Open Error");

	nwrite = open("foo12", O_RDWR | O_CREAT | O_EXCL, 0760);

	int buf = 0;
	char b[1];
	char b1[1];

	umask(0);
	if (nwrite != -1)
	{
		while ((read(file1read, b, 1) > 0))
			write (nwrite, b, 1);

		if ((buf = lseek (nwrite, 0, SEEK_CUR) == -1))
			err_sys("Create lseek Error");

		while ((read(file2read, b1, 1) > 0))
			write (nwrite, b1, 1);
	}
	
	else
		err_sys("Filename: foo12 already exists");

	close(file1read);
	close(file2read);
	close(nwrite);
	
	return 0;
}

