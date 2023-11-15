/*
 * Luke Scott
 * COSC 350
 * Lab 8 Task 1
 * Dr. Park
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *Sum(void *n)
{
	int i;
	int sum = (int)n;
	for (i = sum - 1; i > 0; i--)
		sum += i;

	printf("Summation of %i : %i\n", (int)n, sum);
	pthread_exit(NULL);
}

void *Fact(void *n)
{
	int i;
	int product = (int)n;
	for (i = product - 1; i > 0; i--)
		product *= i;

	printf("Factorial of %i : %i\n", (int)n, product);
	pthread_exit(NULL);
}

int main(int argc, char * argv [])
{
	if (argc != 2)
	{
		perror("Invalid number of arguments");
		exit (1);	
	}

	pthread_t s, f;
	int thrd;

	int num = atoi(argv[1]);

	thrd = pthread_create(&s, NULL, Sum, (void *)num);
	if (thrd)
	{
		perror("Thread error");
		exit (-1);
	}

	thrd = pthread_create(&f, NULL, Fact, (void *)num);
	if (thrd)
	{
		perror("Thread error");
		exit (-1);
	}
	
	pthread_exit(NULL);
	exit(0);
}
