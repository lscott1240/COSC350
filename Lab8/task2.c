/*
 * Luke Scott
 * COSC 350
 * Lab 8 Task 2
 * Dr. Park
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>


void thread1(int * a)
{
	int score;
	int i, j, k;
	int validScore = 1;

	for (i = 0; i < 20; i++)
	{
		printf("Enter score for test %i (-1 to exit): ", i + 1);
		scanf("%d", &score);

		while(score < -1 || score > 100)
		{
			printf("Error: invalid input, try again: ");
			scanf("%d", &score);
		}
		a[i] = score;
		if (score == -1)
			break;
	}

	for (j = 0; j < i - 1; j++)
	{
		int min = j;
		for (k = j + 1; k < i; k++)
			if (a[k] < a[min])
				min = k;
		int temp = a[j];
		a[j] = a[min];
		a[min] = temp;
	}

	pthread_exit(NULL);
}

void thread2(int * a)
{
	int i;
	int total = 0;
	float average, median;

	for (i = 0; a[i] != -1; i++)
		total += a[i];

	if (i == 0)
	{
		printf("The array is empty so both values are 0\n");
		pthread_exit(NULL);
	}

	average = (float)total / i;
	if (i % 2 == 0)
	{
		int rhs = (i/2) - 1;
		int lhs = (i/2);
		median = (float)(a[rhs] + a[lhs]) / 2;
	}
	else
		median = a[i / 2];

	printf("Average : %f\nMedian: %f\n", average, median);
	pthread_exit(NULL);
}

void thread3(int * a)
{
	int i;
	int max;
	int min = a[0];

	for (i = 0; a[i] != -1; i++)
		max = a[i];

	if (i == 0)
	{
		printf("The array is empty so there is no min and max scores\n");
		pthread_exit(NULL);
	}

	printf("Min: %i\nMax: %i\n", min, max);
	pthread_exit(NULL);
}

void thread4(int * a)
{
	int i;

	for (i = 0; i < 20; i++)
	{
		a[i] = 0;
		printf("%i ", a[i]);
	}

	printf("\nBUFFER CLEAR\n");
	pthread_exit(NULL);
}

int main()
{
	pthread_t thrd[4];
	int t;
	int i;
	int * a = malloc(20 * sizeof(int));

	t = pthread_create(&thrd[0], NULL, thread1, (void *) a);
	if (t)
	{
		printf("Thread error\n");
		exit (-1);
	}

	pthread_join(thrd[0], NULL);
	
	t = pthread_create(&thrd[1], NULL, thread2, (void *) a);
	if (t)
	{
		printf("Thread error\n");
		exit (-1);
	}

	t = pthread_create(&thrd[2], NULL, thread3, (void *) a);
	if (t)
	{
		printf("Thread error\n");
		exit (-1);
	}

	pthread_join(thrd[1], NULL);
	pthread_join(thrd[2], NULL);


	t = pthread_create(&thrd[3], NULL, thread4, (void *) a);
	if (t)
	{
		printf("Thread error\n");
		exit (-1);
	}

	pthread_join(thrd[3], NULL);
	pthread_exit(NULL);
	return 0;
}
