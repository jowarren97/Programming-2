/******NB Protein b too large too upload to github******/

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

struct protein{
	string gi;
	string ref;
	string name;
	string sequence;
};

//take item id of protein, print information stored in corresponding struct within data vector
void print_overview(int protein_count);
void print_description(int item_id, vector<protein> data);
void print_sequence(int item_id, vector<protein> data);
void print_statistics(int item_id, vector<protein> data);

//reads 'info' line and categorises into a strings within protein struct
void info_to_struct(string info, protein* a);

//user input, search for matching protein, output corresponding item id
int search_id(vector<protein> data);
int search_gi(vector<protein> data);
int search_ref(vector<protein> data);
int search_keyword(vector<protein> data);

//takes item id, saves info stored in corresponding protein struct into a file called selected_proteins.cpp
void write_to_file(int item_id, vector<protein> data);

//prints menu and takes user input - updates a variable called option which is used in main as a condition for continuation/exit
void welcome_menu(string* option);

//prints menu and takes user input - updates option variable, updates item_id found by search functions which is then passed to submenu2
void sub_menu1(vector<protein> data, string* option, int* item_id);

//as above but takes item_id via send by value
void sub_menu2(vector<protein> data, string* option, int item_id);


int main()
{
	string line;
	string info;
	string current_sequence;
	string new_sequence;
	string selection;
	string keyword;
	protein temp;
	
	int protein_count = 0;
	int item_id;
	
	vector<protein> data;	
//----------FILE SELECTION-------------
	do
	{
		welcome_menu(&selection);
//----------IF OPTION 1 or 2-----------------	
		if (selection != "exit")
		{
			cout << "Loading Database..." << endl;
			ifstream f_in((selection).c_str());
			
			if(f_in)
			{
//--------------LOADING DATA INTO VECTOR OF STRUCTS---------------				
				while (!f_in.eof()) //sorting data
				{
					getline(f_in, line);
					
					if (line[0] == '>') //begin with > means info line
					{
						if (!current_sequence.empty())
						{
							temp.sequence = current_sequence;
							data.push_back(temp);
							(current_sequence).clear();
							protein_count++;
						}
						
						info = line;
						info_to_struct(info, &temp);
					}
					else //if line not info then sequence
					{
						new_sequence = line;
						current_sequence = current_sequence + new_sequence; //concatenate sequences
					}		
				} //reached end of file
				if (f_in.eof())
				{
					temp.sequence = current_sequence;
					data.push_back(temp);
					protein_count++;
				} //compile final protein sequence stored in strings
				
//--------------LOADING COMPLETE---------------------------
				cout << "Database Loaded\n" << endl;	

//--------------SUBMENU1 SELECTION-------------------------
				do
				{
					sub_menu1(data, &selection, &item_id);
					
					if ((selection != "exit")&&(selection != "print_overview"))
					{
//----------------------SUBMENU2 SELECTION---------------------
						do
						{
							sub_menu2(data, &selection, item_id);
						} while (selection != "mainmenu");
					}
					
				} while (selection != "exit");
			}//end if file open
			else
			{
				cout << "file error" << endl;
			}
			
			f_in.close();
		}//end if welcome menu selection not exit
		
	} while (selection != "exit");
	
	return 0;
}

void print_overview(int protein_count)
{
	cout << "The proteins in the database are from GenBank(R)" << endl;
	cout << "Total number of proteins in the database: " << protein_count << endl;
	cout << "Amino acids are represeted by the following characters:" << endl;
	cout << "A alanine\t\tP proline" << endl;
	cout << "B aspartate/asparagine\tQ glutamine" << endl;
	cout << "C cystine\t\tR arginine" << endl;
	cout << "D aspartate\t\tS serine" << endl;
	cout << "E glutamate\t\tT threonine" << endl;
	cout << "F phenylalanine\t\tU selenocysteine" << endl;
	cout << "G glycine\t\tV valine" << endl;
	cout << "H histidine\t\tW tryptophane" << endl;
	cout << "I isoleucine\t\tY tyrosine" << endl;
	cout << "K lysine\t\tZ glutamate/glutamine" << endl;
	cout << "L leusine\t\tX any" << endl;
	cout << "M methionine\t\t* translation stop" << endl;
	cout << "N asparagine\t\t- gap of indeterminate length" << endl;
	cout << "\n";
}

void print_description(int item_id, vector<protein> data)
{
	cout << "Description of protein:" << endl;
	cout << "item id:\t " << item_id << endl;
	cout << "gi id:\t\t " << (data[item_id - 1]).gi << endl;
	cout << "ref id:\t\t " << (data[item_id - 1]).ref << endl;
	cout << "name:\t\t " << (data[item_id - 1]).name << endl << endl;
}

void print_sequence(int item_id, vector<protein> data)
{
	cout << "Protein sequence:" << endl;
	cout << data[item_id-1].sequence << endl << endl;
}

void print_statistics(int item_id, vector<protein> data)
{
	string sequence = data[item_id-1].sequence;
	
	cout << "Report on protein statistics:\n" << endl;
	cout << "Total number of amino acids: " << sequence.size() << endl;
	cout << "A\t" << count(sequence.begin(), sequence.end(), 'A') << "\t";
	cout << "P\t" << count(sequence.begin(), sequence.end(), 'P') << "\n";
	
	cout << "B\t" << count(sequence.begin(), sequence.end(), 'B') << "\t";
	cout << "Q\t" << count(sequence.begin(), sequence.end(), 'Q') << "\n";
	
	cout << "C\t" << count(sequence.begin(), sequence.end(), 'C') << "\t";
	cout << "R\t" << count(sequence.begin(), sequence.end(), 'R') << "\n";
	
	cout << "D\t" << count(sequence.begin(), sequence.end(), 'D') << "\t";
	cout << "S\t" << count(sequence.begin(), sequence.end(), 'S') << "\n";
	
	cout << "E\t" << count(sequence.begin(), sequence.end(), 'E') << "\t";
	cout << "T\t" << count(sequence.begin(), sequence.end(), 'T') << "\n";
	
	cout << "F\t" << count(sequence.begin(), sequence.end(), 'F') << "\t";
	cout << "U\t" << count(sequence.begin(), sequence.end(), 'U') << "\n";
	
	cout << "G\t" << count(sequence.begin(), sequence.end(), 'G') << "\t";
	cout << "V\t" << count(sequence.begin(), sequence.end(), 'V') << "\n";
	
	cout << "H\t" << count(sequence.begin(), sequence.end(), 'H') << "\t";
	cout << "W\t" << count(sequence.begin(), sequence.end(), 'W') << "\n";
	
	cout << "I\t" << count(sequence.begin(), sequence.end(), 'I') << "\t";
	cout << "Y\t" << count(sequence.begin(), sequence.end(), 'Y') << "\n";
	
	cout << "K\t" << count(sequence.begin(), sequence.end(), 'K') << "\t";
	cout << "Z\t" << count(sequence.begin(), sequence.end(), 'Z') << "\n";
	
	cout << "L\t" << count(sequence.begin(), sequence.end(), 'L') << "\t";
	cout << "X\t" << count(sequence.begin(), sequence.end(), 'X') << "\n";
	
	cout << "M\t" << count(sequence.begin(), sequence.end(), 'M') << "\t";
	cout << "*\t" << count(sequence.begin(), sequence.end(), '*') << "\n";
	
	cout << "N\t" << count(sequence.begin(), sequence.end(), 'N') << "\t";
	cout << "-\t" << count(sequence.begin(), sequence.end(), '-') << "\n";
	
	cout << "\n";
}

void info_to_struct(string info, protein* a)
{
	int gi_start, gi_end;
	int ref_start, ref_end;
	int name_start, name_end;
	
	gi_start = info.find('|') + 1;
	gi_end = info.find('|', gi_start);
	
	ref_start = info.find('|', gi_end + 1) + 1;
	ref_end = info.find('|', ref_start);
	
	name_start = ref_end + 2;
	name_end = info.find(']') +1;
		
	(*a).gi = info.substr(gi_start, gi_end - gi_start);
	(*a).ref = info.substr(ref_start, ref_end - ref_start);
	(*a).name = info.substr(name_start, name_end - name_start);
}

int search_id(vector<protein> data)
{
	int id;
	string invalid_input;
	
	cout << "Enter an item id\n>> ";
	cin >> id;
	cout << "\n";
	
	while ((cin.fail())||(id<1)||(id>data.size()))
	{
		cin.clear();
		cout << "Invalid input, please enter a new item id\n>>";
		getline(cin, invalid_input);
		cin >> id;
		cout << "\n";
	}	
	return id;
}

int search_gi(vector<protein> data)
{
	string gi;
	int protein_count = data.size();
	
	cout << "Enter a gi id>> " << endl;
	
	while(1)
	{
		cin >> gi;
		cout << endl;
				
		for (int i = 0; i<= protein_count; i++)
		{
			if ((data[i].gi) == gi)
			{
				return i+1;
			}
		}
		
		cout << "No matches found, please enter a gi id\n>>";
	}	
}

int search_ref(vector<protein> data)
{
	string ref;
	int protein_count = data.size();
	
	cout << "Enter a reference id" << endl;

	while(1)
	{
		cin >> ref;
		cout << endl;
				
		for (int i = 0; i<= protein_count; i++)
		{
			if ((data[i].ref) == ref)
			{
				return i+1;
			}
		}

		cout << "No matches found, please enter a new reference id\n>> ";
		
	}
}

int search_keyword(vector<protein> data)
{
	int item_id;
	int protein_count = data.size();
	vector<int> search_results;
	string keyword;
	int selection;
	string invalid_input;

	cout << "Enter keyword: " << endl;

	
	do{
		cin >> keyword;
		cout << endl;
		
		(search_results).clear();
	
		for (int i = 0; i< protein_count; i++)
		{
			if (((data[i].name).find(keyword))!=string::npos)
			{
				(search_results).push_back(i);
			}
		}
		
		cout << "Number of matches found: " << (search_results).size() << endl;
		
		if (search_results.size() == 0)
		{
			cout << "Please enter a new keyword: ";
		}
		
		for (int j = 0; j< (search_results).size(); j++)
		{
			cout << j+1 << ") ";
			cout << "item id: " << (search_results)[j] + 1 << ", ";
			cout << "gi id: " << data[(search_results)[j]].gi << ", ";
			cout << "ref id: " << data[(search_results)[j]].ref << endl;
			cout << "   " << data[(search_results)[j]].name << endl;
		}
	}while ((search_results).size()==0);
		
	cout << "\n" << endl;
	cout << "Select one of the matches" << endl;
	cout << ">> ";
	cin >> selection;
	
	while (cin.fail() || selection<1 || selection>(search_results).size())
	{
		cin.clear();
		cout << "Invalid selection, please try again\n>>";
		getline(cin, invalid_input);
		cin >> selection;
		cout << "\n";
	}
	
	item_id = search_results[selection];
	
	return item_id;
}

void write_to_file(int item_id, vector<protein> data)
{
	ofstream f_out("selected_proteins.txt");
	
	if (f_out)
	{
		f_out << item_id << endl;
		f_out << data[item_id].gi << endl;
		f_out << data[item_id].ref << endl;
		f_out << data[item_id].name << endl;
		f_out << data[item_id].sequence << endl << endl;
	}
	else
	{
		cout << "Could not open file" << endl;
	}
	
	f_out.close();
}

void welcome_menu(string* option)
{
	int selection;
	string invalid_input;

	cout << "Welcome to the Protein Database\n" << endl;
	cout << "Select an option from the menu below" << endl;
	cout <<	"1) Load the abridged protein data" << endl;
	cout <<	"2) Load the complete protein data" << endl;
	cout <<	"3) Quit the database" << endl;
	cout << ">> ";
	cin >> selection;
	cout << "\n";
	
	while (selection<1 || selection>3 || cin.fail())
	{
		cin.clear();
		cout << "Invalid selection, please try again\n>>";
		getline(cin, invalid_input);
		cin >> selection;
		cout << "\n";
	}
	
	if (selection == 1)
	{
		*option = "protein_a.fa";
	}
	else if (selection == 2)
	{
		*option = "protein_c.fa";

	}
	else
	{
		*option = "exit";
	}
}

void sub_menu1(vector<protein> data, string* option, int* item_id)
{
	string invalid_input;
	int selection;
	int protein_count = data.size();
	
	cout << "Select an option from the menu below" << endl;
	cout <<	"1) Print overview of the protein database" << endl;
	cout <<	"2) Search by protein #" << endl;
	cout <<	"3) Search by gi #" << endl;
	cout <<	"4) Search by ref #" << endl;
	cout <<	"5) Search by keyword" << endl;
	cout <<	"6) Quit database" << endl;
	cout << ">> ";
	cin >> selection;
	cout << "\n";
		
	while ((selection<1) || (selection>6) || (cin.fail()))
	{
		cin.clear();
		cout << "Invalid selection, please try again\n>>";
		getline(cin, invalid_input);
		cin >> selection;
		cout << "\n";
	}
	switch (selection)
	{
		case 1:
			*option = "print_overview";
			print_overview(protein_count);
			break;
		case 2:
			*option = "id";
			*item_id = search_id(data);
			break;
		case 3:
			*option = "gi";
			*item_id = search_gi(data);
			break;
		case 4:
			*option = "ref";
			*item_id = search_ref(data);
			break;
		case 5:
			*option = "keyword";
			*item_id = search_keyword(data);
			break;
		case 6:
			*option = "exit";
			break;		
	}
}

void sub_menu2(vector<protein> data, string* option, int item_id)
{
	string invalid_input;
	int selection;

	cout << "Select an option from the menu below" << endl;
	cout <<	"1) Description of the protein" << endl;
	cout <<	"2) Protein sequence" << endl;
	cout <<	"3) Protein statistics" << endl;
	cout <<	"4) Record protein to file" << endl;
	cout <<	"5) Return to main menu" << endl;
	cout << ">> ";
	cin >> selection;
	cout << "\n";
	
	while (selection<1 || selection>5 || cin.fail())
	{
		cin.clear();
		cout << "Invalid selection, please try again\n>>";
		getline(cin, invalid_input);
		cin >> selection;
		cout << "\n";
	}
	switch (selection)
	{
		case 1:
			*option = "description";
			print_description(item_id, data);
			break;
		case 2:
			*option = "sequence";
			print_sequence(item_id, data);
			break;
		case 3:
			*option = "stats";
			print_statistics(item_id, data);
			break;
		case 4:
			*option = "file";
			write_to_file(item_id, data);
			break;
		case 5:
			*option = "mainmenu";
			break;		
	}
}
