/*
 * Luke Scott
 * COSC 350
 * Lab 3 Task 1
 * Dr. Park
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	char buffer[128];
	int nread;
	nread = read(0, buffer, 128);

	if (nread == -1)
		write (2, "A read error\n", 12);
	
	if ((write (1, buffer, nread)) != nread)
		write (2, "A write Error!\n", 14);
	exit (0);
}
