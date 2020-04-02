#include "judge.h"
#include <stdio.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>

void BoardInitialize(board * info)
{
	info->IsDisp = 0;
	info->win = 0;
	info->count = 0;

	for(int i =0 ; i < 9 ; i++)
	{
		info->turntime[i] = 0;
	}	

	for(int i = 0 ; i < 3 ; i++)
	{
		for(int j = 0 ; j < 3 ; j++)
		{
			info->grid[i][j] = 0;
		}
	}
}


int isWin (board * info)
{
	int count = 0;

	for(int i = 0; i < 3; i++)
	{
		count = 0;
		for(int j = 0 ; j < 3; j++)
		{
			count += info->grid[i][j];		
		}

		if((count == 3))
		{
			return 1;
		}
		if((count == -3))
		{
			return 2;
		}

	}

	count = 0;

	for(int i = 0 ; i < 3 ; i++)
	{
		count = 0;
		for(int j = 0 ; j < 3 ; j++)
		{
			count += info->grid[j][i];
		}

		if((count == 3))
		{
			return 1;
		}
		if((count == -3))
		{
			return 2;
		}
	}

	count = 0 ;
	int count2 = 0;

	for(int i = 0 ; i < 3; i++)
	{
		count += info->grid[i][i];
		count2 += info->grid[2-i][2-i];
	}

	if((count == 3) || (count2 == 3))
	{
//		printf("diagonal win\n");
		return 1;
	}
	if((count == -3) || (count2 == -3))
	{
//		printf("diagonal win\n");
		return 2;
	}

	return 0;


}

void display(board *info)

{
	
	printf("This is turn#: %d\n",info->count);
	
	for(int i = 0 ; i < 3 ; i++)
	{
		for(int j = 0 ; j < 3; j++)
		{
			if(info->grid[j][i] == 0)
			{
				printf(" - ");
			}
			else if (info->grid[j][i] == 1)
			{
				printf(" X ");
			}
			else if (info->grid[j][i] == -1)
			{
				printf(" O ");
			}
		}
		
		printf("\n");
	}

	info->IsDisp = 0;
}
