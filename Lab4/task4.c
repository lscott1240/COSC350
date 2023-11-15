/*
 * Luke Scott
 * COSC 350
 * Lab 4 Task 3
 * Dr. Park
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void err_sys(char * str)
{
	printf("%s\n", str);
	exit(1);
}

int palind(int fd1, int fd2)
{
	int end = lseek(fd1, 0, SEEK_END);
	int pos = lseek(fd1, 0, SEEK_SET);

	char b;
	char t;


	while (pos <= end/2)
	{
		lseek(fd1, pos, SEEK_SET);
		read(fd1, &b, 1);
		lseek(fd1, end - pos - 2, SEEK_SET);
		read(fd1, &t, 1);

		if (b != t)
			return 0;
		pos++;

	}

	return 1;
}

int main(int argc, char * argv[])
{
	if (argc < 2)
		err_sys("Not enough parameters");
	if (argc > 3)
		err_sys("Too many parameters");

	int f1read, f2read, buffer;

	if ((f1read = open(argv[1], O_RDONLY)) < 0)
		err_sys("Create File Open Error");

	f2read = dup(f1read);

	if (palind(f1read, f2read))
		printf("This is a palindrome");
	else
		printf("This is not a palindrome");
}
