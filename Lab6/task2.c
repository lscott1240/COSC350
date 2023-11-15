/*
 * Luke Scott
 * COSC 350
 * Lab 6 Task 2
 * Dr. Park
*/

#include <utmp.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void err_sys(char * str)
{
	printf("%s\n", str);
	exit (1);
}

int openUtmpFile()
{
	int openFile;
	if ((openFile = open("/var/run/utmp", O_RDONLY)) == -1)
		err_sys("UTMP Open Error");

	return openFile;
}

int main()
{
	struct utmp log[1];

	int file = openUtmpFile();
	int nread;
	int count = 0;

	while ((nread = read(file, &log, sizeof(log))) > 0)
	{
		printf("User name = %s\n", log->ut_user);
		if(log->ut_type == 7)
			count++;
	}
	printf("The number of logged in users = %d\n", count);
}
