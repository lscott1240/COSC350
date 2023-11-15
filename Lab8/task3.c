/*
 * Luke Scott
 * COSC 350
 * Lab 8 Task 3
 * Dr. Park
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

void err_sys(char * str)
{
	printf("%s\n", str);
	exit(1);
}

int main(void)
{
	int n, fd[2], int1, int2, size;
	char line[MAX];
	pid_t pid;

	if (pipe(fd) < 0)
		err_sys("Pipe error");

	if ((pid = fork()) < 0)
		err_sys("Fork error");

	if (pid > 0)
	{
		close(fd[0]);
		printf("Submit two integers\n");
		while (fgets(line,MAX, stdin) != NULL)
		{
			n = strlen(line);
			if (write(fd[1], line, n) != n)
				err_sys("write error to pipe");
			if (n == 0)
			{
				err_sys("child closed pipe");
				break;
			}
			line[n] = '\0';
		}
		if (ferror(stdin))
			err_sys("fputs error on stdin");
		exit(0);
	}
	else
	{
		close(fd[1]);

		while ((n = read(fd[0], line, MAX)) > 0)
		{
			if (sscanf(line, "%d%d", &int1, &int2) == 2)
			{
				sprintf(line, "Sum: %d\n", int1 + int2);
				n = strlen(line);
				if (write(0, line, n) != n)
					err_sys("Write error");
			}
			else
			{
				if (write(0, "Inavlid args\n", 13) != 13)
					err_sys("Write error");
				exit(0);
			}
		}
		exit(0);
	}
	exit(0);
}
