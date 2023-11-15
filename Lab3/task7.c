/*
 * Luke Scott
 * COSC 350
 * Lab 3 Task 7
 * Dr. Park
*/

#include <stdio.h>
#include <stdlib.h>

void err_sys(char *str)
{
	printf ("%s", str);
	exit (1);
}

int str_to_int(char * str)
{
	int num = 0, strc = 0, neg = 0;
	if (str[0] == '-')
	{
		neg = 1;
		strc++;
	}
	
	for (strc; str[strc] != '\0'; strc++)
	{
		if (str[strc] >= '0' && str[strc] <= '9')
			num = num * 10 + str[strc] - '0';
		else
			err_sys("Invalid Number");
	}

	if (neg == 1)
		return num*-1;

	return num;
}

int main (int argc, char * argv [])
{
	int num = 0;
	
	if (argc == 1)
		err_sys("Not enough parameters");

	int total = 0;
	for (int i = 1; i < argc; i++)
	{
		if (str_to_int(argv[i]) == -1)
			return 1;
		else
			total+=str_to_int(argv[i]);
	}

	printf ("Total of all the parameters = %d \n",total);	

	return 0;
}
