#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

char buf1[] = "abcd";
char buf2[] = "ABCD";

int main()
{
	int filedes;

	umask(0);
	filedes = creat("filehole.txt", 0644);
	write (filedes, buf1, 4);
	lseek (filedes, 20, SEEK_SET);
	write (filedes, buf2, 4);

	return 0;
}
