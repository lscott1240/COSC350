/*
 * Luke Scott
 * COSC 350
 * Lab 4 Task 1
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
	int nread, alphawr, numwr, othwr;
	char b[1];
	char sp[1];
	char nl[1];
	sp[0] = ' ';
	nl[0] = '\n';

	if (argc < 5)
		err_sys("Not enough arguments\n");

	if (argc > 5)
		err_sys("Too many arguments\n");

	if ((nread = open(argv[1], O_RDONLY)) < 0)
		err_sys("Create File Open Error");

	if ((alphawr = open(argv[2], O_RDWR | O_EXCL | O_CREAT, 0600)) < 0)
		err_sys("Create File Write Error");

	if ((numwr = open(argv[3], O_RDWR | O_EXCL | O_CREAT, 0600)) < 0)
		err_sys("Create File Write Error");	

	if ((othwr = open(argv[4], O_RDWR | O_EXCL | O_CREAT, 0600)) < 0)
		err_sys("Create File Write Error");

	umask(0);

	while ((read(nread, b, 1) > 0))
	{
		if (b[0] <= 'z' && b[0] >= 'A')
		{
			write(alphawr, b, 1);
			write(numwr, sp, 1);
			write(othwr, sp, 1);
		}

		else if (b[0] <= '9' && b[0] >= '0')
		{
			write(alphawr, sp, 1);
			write(numwr, b, 1);
			write(othwr, sp, 1);
		}

		else if (b[0] == ' ')
		{
			write(alphawr, sp, 1);
			write(numwr, sp, 1);
			write(othwr, sp, 1);
		}

		else if (b[0] == '\n')
		{
			write(alphawr, nl, 1);
			write(numwr, nl, 1);
			write(othwr, nl, 1);
		}

		else
		{
			write(alphawr, sp, 1);
			write(numwr, sp, 1);
			write(othwr, b, 1);
		}
	}

	close(nread);
	close(alphawr);
	close(numwr);
	close(othwr);
	return 0;
}
