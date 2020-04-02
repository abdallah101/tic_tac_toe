#include <stdio.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include "judge.h"
#include <time.h>
#include <sys/time.h>
int main (void)
{
	struct timeval start, end;
	int shmid = shmget ((key_t)123, sizeof(board), IPC_CREAT | 0666);

	srand(time(NULL));

	if(shmid == -1)
	{
		fprintf(stderr, "Wasn't able to create shared memory, aborting>\n");
		exit(EXIT_FAILURE);
	}

	board * info = (board*)shmat(shmid, NULL, 0);

	if(info == NULL)
	{
		fprintf(stderr, "Attaching shared memory failed, aborting\n");
		exit(EXIT_FAILURE);
	}


	while(1)
	{

	
		while (info->turn == 2);

		int score = isWin(info);
		gettimeofday(&start, NULL);
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
				gettimeofday(&end, NULL);


				double timetaken = (end.tv_sec - start.tv_sec)*1000000.0;
				timetaken = (timetaken + (end.tv_usec - start.tv_usec))/1000000.0;
				printf("time taken is = %f\n",timetaken);
				info->turntime[info->count] = timetaken;




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


if(shmdt(info) != 0)
{
	fprintf(stderr, "failed to detach shared memory, aborting\n");
	exit(EXIT_FAILURE);
}
printf("\nPlayer 1 is done\n");
return 0;

}
