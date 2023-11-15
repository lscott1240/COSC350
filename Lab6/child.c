/*
 * Luke Scott
 * COSC 350
 * Lab 6 Task 5
 * Dr. Park
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void err_sys(char * str)
{
	printf("%s\n", str);
	exit (1);
}

int str_to_int(char * str)
{
	int i = 0;
	int num = 0;
	for (i; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			num = num*10 + (str[i] - '0');
		else
			err_sys("Invalid input parameter");
	}
	return num;
}

int main(int argc, char * argv [])
{
	if (argc != 3)
		err_sys("Invlaid Number of Arguments");
	
	char * message = argv[0];
	int Nc = str_to_int(argv[1]);
	int Tc = str_to_int(argv[2]);

	int i = 0;
	for (; i < Nc; i++)
	{
		puts(message);
		sleep(Tc);
	}
	exit(37);
}
