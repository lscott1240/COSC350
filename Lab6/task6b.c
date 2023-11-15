/*
 * Luke Scott
 * COSC 350
 * Lab 6 Task 6 
 * Dr. Park
*/

#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void err_sys(char * str)
{
	printf("%s", str);
	exit (1);
}

int main(int argc, char * argv [])
{
        if (argc != 2)
                err_sys("Invalid number of arguments");

        int num, i, j;
        int nread, pwrite, cwrite, size;
        char p[1];
        p[0] = ' ';
        char b[1];

        if ((nread = open(argv[1], O_RDONLY)) < 0)
                err_sys("Create File Read Error");

        pid_t pid;
        umask(0);
        pid = fork();

        if (pid == 0)
        {
                if ((cwrite = open("child.txt", O_CREAT | O_EXCL | O_RDWR, 0666)) < 0)
			err_sys("Create File Child Write Error");

		if (read(nread, b, 1) != 1)
                        err_sys("File Read Error");
                if (b[0] < '0' || b[0] > '9')
                {
                        if (write(cwrite, b, 1) != 1)
                                err_sys("File Write Error");
                }
                else if (b[0] >= '0' && b[0] <= '9')
                {
                        if (write(cwrite, p, 1) != 1)
				err_sys("File Write Error");
                }
                else if (b[0] == '\0')
                {
                        if (write(cwrite, b, 1) != 1)
                                err_sys("File Write Error");
                }
	}
	else
	{
		if ((pwrite = open("parent.txt", O_CREAT | O_EXCL | O_RDWR, 0666)) < 0)
                        err_sys("Create File Parent Write Error");

		if (read(nread, b, 1) != 1)
			err_sys("File Write Error");

		if (b[0] < '0' || b[0] > '9')
                {
                        if (write(cwrite, p, 1) != 1)
                                err_sys("File Write Error");
                }
                else if (b[0] >= '0' && b[0] <= '9')
                {
                        if (write(cwrite, b, 1) != 1)
				err_sys("File Write Error");
                }
                else if (b[0] == '\0')
                {
                        if (write(cwrite, b, 1) != 1)
                                err_sys("File Write Error");
                }
	}

	exit (0);
