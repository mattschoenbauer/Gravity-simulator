//point_mass.h

#include<string>
#include <fstream>
using namespace std;

const int rad = 15;


class Mass
{
	public:
		Board();
		~Board();
		void display(ostream&);
		void display_blank(ostream&);
		void edit(int,int,char);
		char access(int,int);
		bool isletter(int,int);
		Word addfirstword(string);
		Word addword(string);
		Word check(int,int,string);
		bool inbounds(int,int);

	private:
		char board[SIZE][SIZE];

};

