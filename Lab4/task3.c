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

void err_sys(char * str)
{
	printf("%s", str);
	exit(1);
}

int str_to_int(char * str)
{
	int num = 0, strc = 0;
	
	for (strc; str[strc] >= '0' && str[strc] <= '9'; strc++)
		num = num * 10 + str[strc] - '0';

	return num;
}

void int_to_str(char * str, int n, int k)
{
	int temp;
	while (n > 1)
	{
		temp = n % 10;
		n = n / 10;
		str[k] = temp + '0';
		k--;
	}
}

int main(int argc, char * argv[])
{
	if (argc != 2)
		err_sys("Requires Only One Parameter");

	int nread, num = 0;

	char b[80];
	char n[80];
	char s[80];

	if ((nread = open(argv[1], O_RDONLY)) < 0)
		err_sys("Open File Error");

	umask(0000);

	if ((read(nread, b, 80) < 0))
		err_sys("Read File Error");

	int i = 0, k = 0, j = 0;

	for (i; i < 80; i++)
	{
		if (b[i] >= '0' && b[i] <= '9')
		{
			n[k] = b[i];
			k++;
		}
	}

	num = str_to_int(n);
	num += 10;
	int_to_str(s, num, k);
	write(1, s, k+1);
}
