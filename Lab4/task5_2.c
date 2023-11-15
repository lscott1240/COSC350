/*
 * Luke Scott
 * COSC 350
 * Lab 4 Task 5.2
 * Dr. Park
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void err_sys(char * str)
{
	printf("%s\n", str);
	exit (1);
}

int main()
{
	int check;
	struct stat buf;

	char *symLinkHello = "/home/cosc220/Dir1/toDir21/hello";
	char *Dir21_5 = "/home/cosc220/Dir1/toDir21/Dir21_5";

	if (unlink(symLinkHello) < 0)
		err_sys("Unlink Error");

	if (stat(Dir21_5, &buf) == -1)
	{
		umask(0000);
		if ((check = mkdir(Dir21_5, 0755)) == -1)
			err_sys("Make Dir21 error");
	}

}

