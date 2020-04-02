typedef struct board {
	int grid [3][3];
	int turn;
	int move;
	int msg;
	int count;
	int win;
	int IsDisp;
	int turnTime[9];
	
	

} board;

void BoardInitialize (board * info);
int isWin (board * info);
void displayBoard(board *info);
