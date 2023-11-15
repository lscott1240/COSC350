/*
 * Luke Scott
 * COSC 350
 * Lab 3 Task 9
 * Dr. Park
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void err_sys(char * str)
{
	printf("%s", str);
	exit(1);
}

int str_to_int(char * str)
{
	int strc = 1, num = 0, total = 0;

	for (strc; strc < 4; strc++)
	{
		if (str[strc] >= '0' && str[strc] <= '9')
			num = str[strc] - '0';
		else
			err_sys("Invalid Number");
		if (strc == 1)
			total += num * 100;
		else if (strc == 2)
			total += num * 10;
		else 
			total += num;
	}
	return total;
}

int main(int argc, char * argv [])
{
	if (argc <= 2)
		err_sys("Not enough parameters");
	if (argc > 3)
		err_sys("Too many parameters");

	int nread, nwrite;

	char b[1];
	char bR[4];
	bR[0] = ' ';

	if ((nread = open(argv[1], O_RDONLY)) < 0)
		err_sys("Create File Open Error");

	if ((nwrite = open(argv[2], O_RDWR | O_EXCL | O_CREAT, 0666)) < 0)
		err_sys("Create File Write Error");

	umask(0000);

	if (nwrite != -1)
		while ((read(nread, bR, 4) > 0))
		{
			int num = str_to_int(bR);
			
			b[0] = num;
			write(nwrite, b, 1);		
		}
	else
		printf("Filename: %s already exists\n", argv[2]);

	close(nwrite);
	close(nread);
	return 0;
}
