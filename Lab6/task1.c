/*
 * Luke Scott
 * COSC 350
 * Lab 6 Task 1
 * Dr. Park
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern char ** environ;

void err_sys(char * str)
{
	printf("%s\n", str);
	exit (1);
}

char * mygetenv(const char * name)
{
	char ** envp = environ;
	int len = strlen(name);

	for (; *envp != NULL; envp++)
		if (strncmp(*envp, name, len) == 0 /*&& (*envp)[len] == '='*/)
			return &((*envp)[len+1]);
	return NULL;
}

int main(int argc, char * argv [])
{
	if (argc != 2)
		err_sys("Invalid number of arguments");

	char * en = getenv(argv[1]);
	printf("Executing getenv(%s)\n", argv[1]);

	if (en != NULL)
		printf("RETURN: %s", en);
	else
		printf("RETURN: NULL");
	
	en = mygetenv(argv[1]);
	printf("\nExecuting mygetenv(%s)\n", argv[1]);

	if (en != NULL)
		printf("RETURN: %s\n", en);
	else
		printf("RETURN: NULL\n");

}

