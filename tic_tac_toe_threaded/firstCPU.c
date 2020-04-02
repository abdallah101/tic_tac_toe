#include <stdio.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include "judge.h"
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include "firstCPU.h"
void firstCPU (board * info)
{
	struct timeval start, end;

	srand(time(NULL));

	if(info == NULL)
	{
		fprintf(stderr, "Got NULL as input, aborting\n");
		exit(EXIT_FAILURE);
	}


	while(1)
	{

	
		while (info->turn == 2);
		int score = isWin(info);
		
		gettimeofday(&start,NULL);
		if(score == 0)
		{
			int choicex = 0;
			int choicey = 0;
			if(info->count > 8)
			{
				printf("Its a Tie!\n");
				info->turn = 2;
				info->win = 1;
				break;
			}
			else
			{
				if(info->count == 0)
				{
					choicex = rand()%3;
					choicey = rand()%3;
				}
				else
				{
					choicex = rand()%3;
					choicey = rand()%3;

					while(info->grid[choicex][choicey] != 0)
					{
						choicex = rand()%3;
						choicey = rand()%3;
					}

				}

				info->grid[choicex][choicey] = 1;
				info->count = info->count + 1;
				info->IsDisp = 1;
				display(info);
				while(info->IsDisp == 1);
				gettimeofday(&end,NULL);
				double timetaken = (end.tv_sec - start.tv_sec)*1000000;
				timetaken = (timetaken + (end.tv_usec - start.tv_usec))/1000000;
				info->turnTime[info->count] = timetaken;
				printf("Turn %d took: %f\n", info->count, timetaken);
				info->turn = 2;
			}

		}
		else if ((score == 1 || score == 2) && info->win == 0)
		{
			printf("Congrats Player %d Won!!\nFinal Board:\n",score); 
			info->IsDisp = 1;
			display(info);
			while(info->IsDisp == 1);
			info->win = 1;
			info->turn = 2;
			
			break;		
		}
		if(info->win == 1)
		{
			break;
		}
	

	}

	printf("player 1 is done\n");
	pthread_exit(NULL);


}
