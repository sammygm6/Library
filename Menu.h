# pragma once
# include <string>
# define MENUMAX 6
# define MFILEMAX 4
# define MFIELDMAX 5
# define MRECORDMAX 6
# define MINDEXMAX 3
# define MUTILITIESMAX 4
# include <sstream>
# include <ncurses.h>

using namespace std;

class Menu{
public:
	Menu();	
	void main_menu(int item);
	void files_menu(int item);
	void field_menu(int item);
	void record_menu(int item);
	void index_menu(int item);
	void utilities_menu(int item);
};