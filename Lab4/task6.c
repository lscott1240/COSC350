/*
 * Luke Scott
 * COSC 350
 * Lab 4 Task 6
 * Dr. Park
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

void err_sys(char * str)
{
	printf("%s\n", str);
	exit (1);
}

int main(int argc, char * argv [])
{
	if (argc != 3)
		err_sys("Invalid number of parameters.");

	char *file = argv[1];
	char *path = argv[2];

	struct stat buf;
	struct stat buf1;

	stat(path, &buf);

	char buffer[(strlen(path) + 14)];
	if (path[0] == '~')
	{
		char temp[] = "/home/cosc220";
		strcat(buffer, temp);
		int i = 1;
		for (i; i < strlen(path); i++)
			buffer[11+i] = path[i];
		file = buffer;
		printf("%s\n", file);
	}

	if (S_ISDIR(buf.st_mode))
	{
		char temp[] = "/";
		strcat(path, temp);
		strcat(path, file);
		if (link(file, path) < 0)
			err_sys("Linking Error");
		else
			printf("Link completed to %s\n", path);
		unlink(file);
	}
	else
	{
		int check = 0;
		int i = 0;
		int newlen = 0;
		while (path[i] != '\0')
		{
			if (path[i] == '/')
				check++;
			i++;
		}

		int j = 0, size = 0;
		while (check > 0)
		{
			if (path[j] == '/')
				check--;
			j++;
			size++;
		}

		char buffer[(size + strlen(file))];

		int k = 0;
		while (k < size)
		{
			buffer[k] = path[k];
			k++;
		}

		strcat(buffer, file);

		if (link(file, buffer) < 0)
			err_sys("Linking Error");
		else
			printf("New file created at %s\n", buffer);
		unlink(file);
	}
}

