/*
 * Luke Scott
 * COSC 350
 * Lab 8 Task 4
 * Dr. Park
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define MAX 256

void err_sys(char * str)
{
	printf("%s\n", str);
	exit (1);
}

int main(int argc, char * argv [])
{
	FILE *wfp;
	char *cmd = (char*) malloc (strlen(argv[1]) + strlen(argv[2]));
	sprintf(cmd, "%s %s", argv[1], argv[2]);

	if (argc != 3)
		err_sys("Invalid number of arguments");
	
	if ((wfp = popen(cmd, "w")) != NULL)
	{
		fwrite(cmd, sizeof(char), strlen(cmd), wfp);
		pclose(wfp);
		exit (0);
	}
	exit (1);	
}

