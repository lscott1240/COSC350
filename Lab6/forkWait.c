/*
 * Luke Scott
 * COSC 350
 * Lab 6 Task 4
 * Dr. Park
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
	if (argc != 5)
		err_sys("Invalid number of arguments");

	int num;
	int nums[4];
	for (argc; argc > 1; argc--)
		nums[argc - 2] = str_to_int(argv[argc - 1]);

	pid_t pid;
	char * message;
	int n;
	int time;
	int exit_code;

	printf("fork program starting\n");
	pid = fork();

	switch(pid)
	{
		case -1:
			err_sys("Fork error");
		case 0:
			message = "This is the child";
			n = nums[0];
			time = nums[2];
			exit_code = 37;
			break;
		default:
			message = "This is the parent";
			n = nums[1];
			time = nums[3];
			exit_code = 0;
			break;
	}

	for (; n > 0; n--)
	{
		puts(message);
		sleep(time);
	}

	if (pid != 0)
	{
		int stat_val;
		pid_t child_pid;
		
		child_pid = wait(&stat_val);

		printf("Child has finished: PTD = %d\n", child_pid);
		if (WIFEXITED(stat_val))
			printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
		else
			printf("Child terminated abnormally\n");
	}
	exit(exit_code);
}
