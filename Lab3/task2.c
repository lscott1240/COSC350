/* 
 * Luke Scott
 * COSC 350
 * Lab 3 Task 2
 * Dr. Park
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int main()
{
	char b[1];
	int nread, nwrite;
	nread = open("foo", O_RDONLY);
	nwrite = open("clone1", O_RDWR | O_CREAT | O_EXCL, FILE_MODE);

	if (nread == -1)
		printf("Filename: foo does not exist");

	if (nwrite != -1)
		while ((read(nread, b, 1) > 0))
			write (nwrite, b, 1);

	else
		printf("Filename: clone1 already exists\n");

	close(nwrite);
	close(nread);
	return 0;
}
