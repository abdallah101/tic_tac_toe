#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdio.h>
#include <sys/time.h>
#include "judge.h"
int main (void)

{
	struct timeval start, end;
	gettimeofday(&start, NULL);
	int shmid = shmget((key_t)123, sizeof(board), IPC_CREAT | 0666);

	srand(time(NULL));

	if(shmid == -1)
	{
		fprintf(stderr, "unable to create shared memory, aborting\n");
		exit(EXIT_FAILURE);
	}
	board * info = (board*)shmat(shmid, NULL, SHM_RND);
	if(info == NULL)
	{
		fprintf(stderr, "could not attach shared memory, aborting\n");
		exit(EXIT_FAILURE);
	}
	
	BoardInitialize(info);
	
	if(rand()%2 == 0)
	{
		
		info->turn = 1;
	}
	else
	{
		info->turn = 2;
	}

	gettimeofday(&end, NULL);


	printf("Player %d starts\n",info->turn);
	double timetaken = (end.tv_sec - start.tv_sec)*1000000.0;
				timetaken = (timetaken + (end.tv_usec - start.tv_usec))/1000000.0;
				printf("time taken to create shared memory and initialize board is = %f\n",timetaken);



	printf("Running now Players 1 & 2 for a game of tic tac toe\n\n");
	pid_t first;
	pid_t second;
gettimeofday(&start,NULL);
	first = fork();
	//second = fork();
	gettimeofday(&end, NULL);
 timetaken = (end.tv_sec - start.tv_sec)*1000000.0;
				timetaken = (timetaken + (end.tv_usec - start.tv_usec))/1000000.0;
if(first == 0)
{
				printf("time taken for first fork child = %f\n",timetaken);
}
else if(first > 0)
{
printf("time taken for first fork parent = %f\n",timetaken);
}
	if(first == 0)
	{
		//first child which is player 1
		//printf("I am Player 1");
		//second = fork();
		execvp("./firstCPU",NULL);
		
	}
	else if (first > 0)
	{
		//this is the parent
gettimeofday(&start,NULL);
		second = fork();
gettimeofday(&end,NULL);

timetaken = (end.tv_sec - start.tv_sec)*1000000.0;
				timetaken = (timetaken + (end.tv_usec - start.tv_usec))/1000000.0;
if(second == 0)
{
				printf("time taken for second fork child is = %f\n",timetaken);
}
else if(second > 0)
{printf("time taken for second fork parent is = %f\n",timetaken);}
			if(second == 0)
			{
				execvp("./secondCPU",NULL);
			}

		else if (second > 0)
		{
gettimeofday(&start,NULL);
			while(info->win == 0);

			waitpid(first, NULL, 0);
			waitpid(second, NULL, 0);
gettimeofday(&end,NULL);
timetaken = (end.tv_sec - start.tv_sec)*1000000.0;
				timetaken = (timetaken + (end.tv_usec - start.tv_usec))/1000000.0;

				printf("time waited by parent is = %f\n",timetaken);
			for(int i =0 ; i < 9 ; i++)
			{
				if(info->turntime[i] != 0)
				{printf("Turn %d took %f sec\n",i, info->turntime[i]);}
			}

			if(shmdt(info) != 0)
			{
				fprintf(stderr, "shared memory failed to detach, aborting");
				exit(EXIT_FAILURE);
			}

			if(shmctl(shmid, IPC_RMID, NULL))
			{
				fprintf(stderr, "shared memory failed to destroy, aborting");
				exit(EXIT_FAILURE);
			}
	
			
			printf("\n\nJudge left \"mic drop\"\n\n");
			exit(0);
		}
	}
	return 0;
}
