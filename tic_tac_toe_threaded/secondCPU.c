#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include "judge.h"
#include <pthread.h>
#include "secondCPU.h"
void secondCPU(board * info)
{
	
	struct timeval start, end;

	srand(time(NULL));

	if(info == NULL)
	{
		fprintf(stderr, "Input is NULL, aborting\n");
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		
		while(info->turn == 1);

		int score = isWin(info);
		gettimeofday(&start, NULL);
		int choicex = 0, choicey = 0;
		if(score == 0)
		{
			if(info->count > 8)
			{
				printf("It's a Tie!\n");
				info->turn = 1;
				info->win = 1;
				break;
			}

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

			info->grid[choicex][choicey] = -1;
			info->count = info->count + 1;
			info->IsDisp = 1;
			display(info);
			while(info->IsDisp == 1);
			gettimeofday(&end,NULL);
			double timetaken = (end.tv_sec - start.tv_sec)*1000000;
			timetaken = (timetaken + (end.tv_usec - start.tv_usec))/1000000;
			info->turnTime[info->count] = timetaken;
			printf("Turn %d took: %f\n", info->count, timetaken);
			info->turn = 1;

		}
		else if ((score == 1 || score == 2) && info->win == 0)
		{
			printf("Congrats Player %d Won\nFinal Board:\n",score);
			info->IsDisp =1 ;
			display(info);
			while(info->IsDisp == 1);
			info->win = 1;
			info->turn = 1;
			
			break;
		}

		if(info->win == 1)
		{
			break;
		}


		
	}

	printf("\nPlayer 2 is done\n");
	pthread_exit(NULL);
}
