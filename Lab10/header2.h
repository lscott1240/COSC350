/*
 * Luke Scott
 * COSC 350
 * Lab 10 Task 3
 * Dr. Park
*/

#define NOT_READY -1
#define FILLED 0
#define TAKEN 1
#define GO 2
#define STOP 3
#define MUTEX 0
#define FULL 1
#define EMPTY 2
#define N 5

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short * array;
};

struct Memory
{
	int status;
	int gostop;
	int n[5];
};
