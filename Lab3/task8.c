/*
 * Luke Scott
 * COSC 350
 * Lab 3 Task 4
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

int main(int argc, char * argv [])
{
	if (argc <= 2)
		err_sys("Not enough parameters");
	if (argc > 3)
		err_sys("Too many parameters");

	int nread, nwrite, num = 0;

	char b[1];
	char bR[4];
	bR[0] = ' ';

	if ((nread = open(argv[1], O_RDONLY)) < 0)
		err_sys("Create File Open Error");

	if ((nwrite = open(argv[2], O_RDWR | O_EXCL | O_CREAT, 0666)) < 0)
		err_sys("Create File Write Error");

	umask(0000);

	if (nwrite != -1)
		while ((read(nread, b, 1) > 0))
		{
			num = b[0];
			int i;
			for (i = 3; i > 0; i --)
			{
				bR[i] = (num % 10) + '0';
				num /= 10;
			}

			write(nwrite, bR, 4);
		}
	else
		printf("Filename: %s already exists\n", argv[2]);

	close(nwrite);
	close(nread);
	return 0;
}

