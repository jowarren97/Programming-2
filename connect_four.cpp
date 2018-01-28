#include <iostream>
#include <string>

using namespace std;

void initialiseArray(char array[6][7])
{
	for (int j=0; j <=6; j++ )
	{
		for (int i=0; i <= 5; i++)
		{
			array[i][j] = ' ';
		}
	}
}

void printgrid(char array[6][7])
{
	int n;
	int m;
	
	cout << " 1 2 3 4 5 6 7" << endl;
	
	for ( m=0; m<6; m = m+1)
	{
		for ( n=0; n<7; n = n+1)
		{
			cout << "|";
			cout << array[m][n];
		}
		cout << "|\n";
		cout << "---------------" << endl;
	}
	
	cout << endl << endl;
}

void placetile(char array[6][7], int column, int player)
{ 
	int trueColumn = column - 1; //allows labelling on printed grid to start at 1 rather than 0
	char tile;
	int i = 5;
	
	if (player == 1)
	{
		tile = 'X';
	}
	else
	{
		tile = 'O';
	}
	
	while (i>=0)
	{
		if (array[i][trueColumn] == ' ')
		{
			array[i][trueColumn]= tile;
			break;
		}
		else
		{
			i--;
		}
	}
	
/*	
DELETE WHEN FINISHED
if (array[5][trueColumn] == ' ')
	{
		array[5][trueColumn]= tile;
		*row = 5;
	}
	else if(array[4][trueColumn] == ' ')
	{
		array[4][trueColumn] = tile;
		*row = 4;
	}
	else if(array[3][trueColumn] == ' ')
	{
		array[3][trueColumn] = tile;
		*row = 3;
	}
	else if(array[2][trueColumn] == ' ')
	{
		array[2][trueColumn] = tile;
		*row = 2;
	}
	else if(array[1][trueColumn] == ' ')
	{
		array[1][trueColumn] = tile;
		*row = 1;
	}
	else if (array[0][trueColumn] == ' ')
	{
		array[0][trueColumn] = tile;
		*row = 0;
	}
	else
	{
		cout << "invalid move" << endl;
	}*/
}

bool checkVertical(char array[6][7], int player)
{	
char tile;
int i; //column
int j; //row

	if (player == 1)
	{
		tile = 'X';
	}
	else
	{
		tile = 'O';
	}
	
	
	for (i=0; i<7; i++)
	{
		for (j=2; j>=-1; j--)
		{
			if ((j>-1) && (tile == array[j][i]) && (tile == array[j+1][i]) && (tile == array[j+2][i]) && (tile == array[j+3][i]))
			{
				return true;
				break;
			}
			else if ((j==-1) && (i==6)) // allows exit AFTER loops completed
			{
				return false;
			}
		}
	}
}

bool checkHorizontal(char array[6][7], int player)
{
	char tile;
	int i; //column
	int j; //row

	if (player == 1)
	{
		tile = 'X';
	}
	else
	{
		tile = 'O';
	}
	
	for (j=6; j>=0; j--)
	{
		for (i=0; i<=4; i++)
		{
			if ((i<4) && (tile == array[j][i]) && (tile == array[j][i+1]) && (tile == array[j][i+2]) && (tile == array[j][i+3]))
			{
				return true;
				break;
			}
			else if ((i==4) && (j==0)) // allows exit AFTER loops completed
			{
				return false;
			}
		}
	}
}

bool checkDiagonal(char array[6][7], int player)
{
	int i; //column
	int j; //row
	int k;
	char tile;
	
	if (player == 1)
	{
		tile = 'X';
	}
	else
	{
		tile = 'O';
	}
	
	for (i=0; i<=3; i++)
	{
		for (j=5; j>=-1; j--)
		{
			//diagonal up right
			if ((5>= j >=3) && (tile == array[j][i]) && (tile == array[j-1][i+1]) && (tile == array[j-2][i+2]) && (tile == array[j-3][i+3]))
			{
				return true;
				break;
			}
			//diagonal down right
			else if ((2>= j >=0) && (tile == array[j][i]) && (tile == array[j+1][i+1]) && (tile == array[j+2][i+2]) && (tile == array[j+3][i+3]))
			{
				return true;
				break;
			}
			//end condition
			else if ((j==-1) && (i==3))
			{
				return false;
			}
		}
	}		
}

bool check4(char array[6][7], int player)
{
	if ((checkVertical(array, player)) == true)
	{
		return true;
	}
	else if ((checkHorizontal(array, player)) == true)
	{
		return true;
	}
	else if ((checkDiagonal(array, player)) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	
//declare variables
	int row = 0;
	int column = 0;
	int counter = 0;
	int turnNo = 0;
	int player;
	bool winCondition = false;
	char board[6][7];

// initialise and print board

	initialiseArray(board);
	printgrid(board);
	
	
//loop until 4 in a row or board full
	while ((check4(board, player) == false) && turnNo < 42)
	{	
		//alternate between X and O
		if (counter % 2 == 0)
		{
			player = 1;
		}
		else
		{
			player = 2;
		}
		
		//dialogue and column selection
		++turnNo;
		
		cout << "TURN " << turnNo << endl;
		cout << "Player " << player << " to play" << endl;
		cout << "Please enter a column: ";
		cin >> column;
		cout << endl;
		
		//ensure valid user input
		while ((column < 1 || column >7) || (board[0][column-1] != ' '))
		{
			cout << "invalid move, please enter a new column" << endl;
			cin >> column;
		}

		placetile(board, column, player);

		printgrid(board);
		
		++counter;
	}
	
	if (turnNo == 42)
	{
		cout << "Game ended as a draw." << endl;
	}
	else
	{
		cout << "Player " << player << " wins!" << endl;
	}
	
	return 0;
}