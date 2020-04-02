#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdio.h>
#include "judge.h"
#include "firstCPU.h"
#include "secondCPU.h"
board data;

void * testFunc(int i, int j)
{
	printf("total = %d\n",i+j);
}

int main (void)

{
	struct timeval start, end;
	gettimeofday(&start,NULL);
	board * info = &data;
	//info = new board();

	srand(time(NULL));
	
	BoardInitialize(info);
	
	if(rand()%2 == 0)
	{
		
		info->turn = 1;
	}
	else
	{
		info->turn = 2;
	}

	gettimeofday(&end,NULL);
	double timetaken = (end.tv_sec - start.tv_sec)*1000000;
	timetaken = (timetaken + (end.tv_usec - start.tv_usec))/1000000;
	printf("time taken to initialize board is: %f\n", timetaken);

	printf("Player %d starts\n",info->turn);

	printf("Running now Players 1 & 2 for a game of tic tac toe\n\n");
	

	gettimeofday(&start,NULL);

	pthread_t first, second, testthread;

	int error1, error2, error3;
	
//	error3 = pthread_create(&testthread, NULL, testFunc, 1,1);
	error1 = pthread_create(&first, NULL, firstCPU, info);
	error2 = pthread_create(&second, NULL, secondCPU, info);

	if(error1 > 0 || error2 >0)
	{
		fprintf(stderr, "Thread creation failed, aborting.\n");
	}

	gettimeofday(&end,NULL);
	timetaken = (end.tv_sec - start.tv_sec)*1000000;
	timetaken = (timetaken + (end.tv_usec - start.tv_usec))/1000000;
	printf("Time taken to create threads is = %f\n", timetaken);

	gettimeofday(&start,NULL);
	pthread_join(first, NULL);
	pthread_join(second, NULL);
	gettimeofday(&end,NULL);
	timetaken = (end.tv_sec - start.tv_sec)*1000000;
	timetaken = (timetaken + (end.tv_usec - start.tv_usec))/1000000;
	printf("time mainthread waited for subthreads to end = %f\n",timetaken);

	return 0;
}
