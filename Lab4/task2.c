/*
 * Luke Scott
 * COSC 350
 * Lab 4 Task 2
 * Dr. Park
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void err_sys(char * str)
{
	printf("%s", str);
	exit(1);
}

int main(int argc, char * argv[])
{
	int nwrite, alphard, numrd, othrd;
	char b0[1];
	char b1[1];
	char b2[1];

	if (argc < 5) 
		err_sys("Not enough arguments\n");

	if (argc > 5)
		err_sys("Too many arguments\n");

	if ((alphard = open(argv[1], O_RDONLY)) < 0)
		err_sys("Create File Open Error");
	
	if ((numrd = open(argv[2], O_RDONLY)) < 0)
		err_sys("Create File Open Error");

	if ((othrd = open(argv[3], O_RDONLY)) < 0)
		err_sys("Create File Open Error");

	if ((nwrite = open(argv[4], O_RDWR | O_EXCL | O_CREAT, 0600)) < 0)
		err_sys("Create File Write Error");

	umask(0);

	while ((read(alphard, b0, 1) > 0))
	{
		read(numrd, b1, 1);
		read(othrd, b2, 1);

		if (b0[0] == b1[0] && b0[0] == b2[0])
			write(nwrite, b0, 1);

		else if (b0[0] != ' ' && b1[0] == ' ' && b2[0] == ' ')
			write(nwrite, b0, 1);

		else if (b1[0] != ' ' && b0[0] == ' ' && b2[0] == ' ')
			write(nwrite, b1, 1);

		else if (b2[0] != ' ' && b0[0] == ' ' && b1[0] == ' ')
			write(nwrite, b2, 1);
	}

	close(alphard);
	close(numrd);
	close(othrd);
	close(nwrite);
	return 0;
}
