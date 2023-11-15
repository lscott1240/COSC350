/* 
 * Luke Scott
 * COSC 350
 * Lab 3 Task 3
 * Dr. Park
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP)

int main()
{
	char b[32];
	int nread, nwrite;
	nread = open("foo", O_RDONLY);
	nwrite = open("clone2", O_RDWR | O_CREAT | O_EXCL, FILE_MODE);

	if (nread == -1)
		printf("Filename: foo does not exist");

	if (nwrite != -1)
	{
		read(nread, b, 32);
		int i = 0;
		for (i; i < 32; i++)
			if (b[i] < ' ' || b[i] > '~')
				b[i] = ' ';
		write(nwrite, b, 32);
	}

	else
		printf("Filename: clone2 already exists\n");

	close(nwrite);
	close(nread);
	return 0;
}
