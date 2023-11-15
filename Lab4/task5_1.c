/* 
 * Luke Scott
 * COSC 350
 * Lab 4 Task 5.1
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

	char *Dir1 = "/home/cosc220/Dir1";
	char *Dir2 = "/home/cosc220/Dir2";
	char *Dir21 = "/home/cosc220/Dir2/Dir21";
	char *hello = "/home/cosc220/Dir2/Dir21/hello";
	char *symLinkDir = "/home/cosc220/Dir1/toDir21";
	char *symLinkHello = "/home/cosc220/Dir1/toHello";

	if (stat(Dir1, &buf) == -1)
	{
		umask(0000);
		if ((check = mkdir(Dir1, 0755)) == -1)
			err_sys("Make Dir1 error");
	}
	
	if (stat(Dir2, &buf) == -1)
	{
		umask(0000);
		if ((check = mkdir(Dir2, 0755)) == -1)
			err_sys("Make Dir2 error");
	}
	
	if (stat(Dir21, &buf) == -1)
	{
		umask(0000);
		if ((check = mkdir(Dir21, 0755)) == -1)
			err_sys("Make Dir21 error");
	}

	if (stat(hello, &buf) == -1)
		if (link("hello", hello) == -1)
			err_sys("Link error");

	if (stat(symLinkDir, &buf) == -1)
		if (symlink(Dir21, symLinkDir) == -1)
			err_sys("Symbolic Link Error");

	if (stat(symLinkHello, &buf) == -1)
		if (symlink(hello, symLinkHello) == -1)
			err_sys("Symbolic Link Error");

	return 0;
}
