#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
using namespace std;

//--------------------------------------------------------------------------
//------------------------	CELL CLASS	------------------------------------
//--------------------------------------------------------------------------

class Cell{
	protected:
		bool state;
		int neighbours;
	public:
		Cell();
		Cell(bool state_in, int neighbours_in);
		Cell(const Cell &clone);
		~Cell();
		
		virtual bool get_state(){return state;}
		virtual void set_state(bool state_in){state = state_in;}
		virtual void update_state();
		virtual int get_neighbours(){return neighbours;}
		virtual void set_neighbours(int neighbours_in){neighbours = neighbours_in;}
		virtual void print();
};

//--------------------------------------------------------------------------

Cell::Cell()
{
	state = 0;
	neighbours = 0;
}

Cell::Cell(bool state_in, int neighbours_in)
{
	state = state_in;
	neighbours = neighbours_in;
}

Cell::Cell(const Cell& clone)
{
	state = clone.state;
	neighbours = clone.neighbours;
}

Cell::~Cell()
{
	
}

void Cell::update_state()
{
	//updates state of cell (dead or alive) based on conditions (i.e state and neighbours)

	if (state == 1)
	{
		if ((neighbours >= 4) || (neighbours <= 1))
		{
			state = 0;
		}
	}
	else
	{
		if (neighbours == 3)
		{
			state = 1;
		}
	}
}

void Cell::print()
{
	//prints state of cell
	
	if (state == 1)
	{
		cout << "O";
	}
	else
	{
		cout << " ";
	}
}

//--------------------------------------------------------------------------
//-------------------------	CANCER CLASS -----------------------------------
//--------------------------------------------------------------------------

class Cancer:public Cell
{	
	public:
		Cancer();
		Cancer(bool state_in, int neighbours_in);
		Cancer(const Cancer &clone);
		~Cancer();

		void update_state(); //virtual functions which are different for cell and cancer
		void print(); // 			^^
};

//--------------------------------------------------------------------------

Cancer::Cancer():Cell()
{
	state = 0;
	neighbours = 0;
}

Cancer::Cancer(bool state_in, int neighbours_in):Cell()
{
	state = state_in;
	neighbours = neighbours_in;
}

Cancer::Cancer(const Cancer& clone):Cell()
{
	state = clone.state;
	neighbours = clone.neighbours;
}

Cancer::~Cancer()
{
	
}

void Cancer::update_state()
{
	//updates state of cell (dead or alive) based on conditions (i.e state and neighbours)
	
	if (state == 1)
	{
		if ((neighbours >= 5) || (neighbours <= 1))
		{
			state = 0;
		}
	}
	else
	{
		if (neighbours == 3)
		{
			state = 1;
		}
	}
}

void Cancer::print()
{
	//prints state of cell
	
	if (state == 1)
	{
		cout << "X";
	}
	else
	{
		cout << " ";
	}

}

//--------------------------------------------------------------------------
//-------------------------	BOARD CLASS	------------------------------------
//--------------------------------------------------------------------------

class Board{
private:
	vector< vector<Cell*> > matrix;
	int time;
public:
	Board();
	Board(int row, int column);
	Board(const Board& Board_in);
	~Board();
	
	void set_time(int time_in){time = time_in;}
	int get_time(){return time;}
	int get_num_Cells();
	void display();
	void seed_Cells(int selection, int confluency);
	void count_neighbours();
	void next_state();
};

//--------------------------------------------------------------------------

Board::Board()
{		
	//initialises a 2D vector of null pointers
	
	for (int i=0; i<20; i++)
	{
		vector<Cell*> row;
		for (int j=0; j<75; j++)
		{
			row.push_back(NULL);
		}
		matrix.push_back(row);
	}
	
	time = 0;
}

Board::Board(int totalrows, int totalcolumns)
{
	//intialises a 2D vector of specified size
	
	for (int i=0; i<totalrows; i++)
	{
		vector<Cell*> row;
		for (int j=0; j<totalcolumns; j++)
		{
			row.push_back(NULL);
		}
		matrix.push_back(row);
	}
	
	time = 0;
}

Board::Board(const Board& Board_in)
{
	int totalrows = matrix.size();
	int totalcolumns = matrix[0].size();
	
	matrix = Board_in.matrix;

}

Board::~Board()
{
	//destructor
}

//--------------------------------------------------------------------------

int Board::get_num_Cells()
{
	//returns number of cells on board which are alive (state 1)
	
	int totalrows = matrix.size();
	int totalcolumns = matrix[0].size();
	int num_Cells = 0;
	
	for (int i=0; i<totalrows; i++)
	{
		for (int j=0; j<totalcolumns; j++)
		{
			if (matrix[i][j]->get_state() == 1)
			{
				num_Cells++;
			}
		}
	}
	return num_Cells;
}

void Board::display()
{
	//prints each cell (element) of the board 
	
	int totalrows = matrix.size();
	int totalcolumns = matrix[0].size();
	
	for (int i=0; i<totalrows; i++)
	{
		for (int j=0; j<totalcolumns; j++)
		{
			matrix[i][j]->print();
		}
		cout << endl;
	}
}

void Board::seed_Cells(int selection, int confluency)
{
	//populates board of null pointers with 'dead' (0) cells, then changes state to 'alive' (1) at random locations 
	//IF cell has not already had state changed by function
	
	int row, column, Cell_quantity;
	int k = 0;
	
	int totalrows = matrix.size();
	int totalcolumns = matrix[0].size();
	
	Cell_quantity = round(totalrows * totalcolumns * 0.01 * confluency);
	
	srand(1);

	for (int i=0; i<totalrows; i++)
	{
		for (int j=0; j<totalcolumns; j++)
		{
			if (selection == 1)
			{
				matrix[i][j] = new Cell(0,0);
			}
			else
			{
				matrix[i][j] = new Cancer(0,0);
			}
		}
	}
	
	while (k < Cell_quantity)
	{
		row = rand() % totalrows;
		column = rand() % totalcolumns;
				
		if (matrix[row][column]->get_state() == 0)
		{
			matrix[row][column]->set_state(1);
			k++;
		}
	}
}

void Board::count_neighbours()
{
	//updates 'neighbours' variable for each cell on the board
	
	int i, j, m, n;
	int neighbours;
	
	int totalrows = matrix.size();
	int totalcolumns = matrix[0].size();
	
	for (i=0; i< totalrows; i++) //loop for entire board
	{
		for (j=0; j< totalcolumns; j++) 
		{
			neighbours = 0;
					
			for (m=-1; m<=1; m++) //loop through 3x3 area around individual cell
			{
				if ((i+m < matrix.size()) && (i+m >= 0)) //limits area to within board array
				{
					for (n=-1; n<=1; n++)
					{
						if ((j+n < matrix[0].size()) && (j+n >= 0))
						{
							if (matrix[i+m][j+n]->get_state() == 1)
							{
								neighbours++;
							}
						}
					}
				}
			}
			
			if (matrix[i][j]->get_state() == 1)
			{
				neighbours--; //accounts for counting the cell itself in 3x3 grid
			}	
			
			matrix[i][j]->set_neighbours(neighbours);
		}
	}
}

void Board::next_state()
{
	//changes state of all cells based on neighbours and increments time by 1
	
	int i, j;
	int totalrows = matrix.size();
	int totalcolumns = matrix[0].size();
	
	count_neighbours();
	
	for (i=0; i< totalrows; i++)
	{
		for (j=0; j< totalcolumns; j++) 
		{
			matrix[i][j]->update_state();
		}
	}
	
	time++;
}

//--------------------------------------------------------------------------
//-------------------------		MAIN	------------------------------------
//--------------------------------------------------------------------------

int main()
{
	int selection = 0;
	int confluence = 0;
	int c;
	Board board(100,350);
	string trash;
	
	system("cls");
	
	cout << "Welcome to the Cell simulator" << endl;
	cout << endl;
	cout << "Select your Cell type: (1) normal Cells or (2) cancer Cells" << endl;
	
	while ( (selection < 1) || (selection > 2))
	{
		cout << ">";
		cin >> selection;
	}
		
	getline(cin,trash);
	
	cout << "Select the confluence percentage (%)" << endl;
	
	while ( (confluence <= 0) || (confluence > 100))
	{
		cout << ">";
		cin >> confluence;
	}
	
	getline(cin,trash);
	board.seed_Cells(selection, confluence);
	system("cls");
	
	while(c!='q')
	{
	system("cls");
	cout << "time: " << board.get_time() << endl;
	cout << "number of Cells: " << board.get_num_Cells() << endl;
	board.display();
	c = cin.get();
	board.next_state();
	}
	
	return 0;
}