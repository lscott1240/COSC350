#define NOT_READY -1
#define FILLED 0
#define TAKEN 1
#define GO 2
#define STOP 3

struct Integers {
	int n[5];
	int i;
};

struct Memory {
	int status;
	int gostop;
	struct Integers data;
};
