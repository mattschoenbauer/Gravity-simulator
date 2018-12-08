//crossboard.cpp

#include<iostream>
#include "crossboard.h"
#include <algorithm>
#include <string>
#include <fstream>
//#include "word.h"
using namespace std;


Board::Board()
{
        for (int i = 0; i < SIZE; i++)
                for (int j = 0; j < SIZE; j++)
                        board[i][j] = DOT;
}

Board::~Board()
{ }

void Board::display(ostream& ofs)
{
	ofs << endl;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++) ofs << board[j][i];//This ensures that the first argument is the x value
		ofs << endl;
    }
	ofs << endl;

}

void Board::display_blank(ostream& ofs)//This display the board with the # symbols
{
	ofs << endl;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
		{
			if(isletter(j,i)){ofs << BLANK;}
			else{ofs << BLOCK;}
		}
		ofs << endl;
    }
	ofs << endl;

}


void Board::edit(int i, int j, char c)//This allows you to edit a spot on the board
{
	board[i][j] = toupper(c);
}

char Board::access(int i, int j)
{
	return board[i][j];
}

bool Board::isletter(int i, int j)
{
	if(!inbounds(i,j)){return false;}
	int n = (int)(tolower(access(i,j)));
	if( n >= 97 && n <= 122){ return true;}
	return false;
}

Word Board::addfirstword(string s)
{
	Word w;
	w.setName(s);
	int n = s.length();
	int startx = (SIZE-n)/2;
	int starty = SIZE/2;
	w.setX(startx);
	w.setY(starty);
	w.setDir("Across ");
	for( int i = 0; i < n; i++){ edit(startx + i, starty,s[i]);}
	return w;
}


Word Board::addword(string s)//This function adds a word to the board
{
	Word w;
	bool found = false;
	for(int i = 0; i < SIZE ; i++)
	{
		if(found){break;}
		for(int j = 0; j < SIZE ; j++)
		{
			if(found){break;}
			if(access(i,j) != DOT)
			{
				w = check(i,j,s);
				if(w.getName() != " "){found = true;}//This condition means that we've successfully found a match
			}
		}
	}
	return w;
}

Word Board::check(int x, int y, string s)//This function checks if a word can be fit at a particular point, and changes it if possible
{
	Word w;
	int l = s.length();
	char c = access(x,y);
	bool acrosssometimesworks = true, downsometimesworks = true;
	if(isletter(x-1,y) || isletter(x+1,y)){acrosssometimesworks = false;}
	if(isletter(x,y-1) || isletter(x,y+1)){downsometimesworks = false;}//We need to chack if across and down will ever work first
	for(int i = 0; i < l; i++)
	{
		if(toupper(s[i]) == c)
		{
			bool acrossworks = acrosssometimesworks, downworks = downsometimesworks;
			for(int j = 1; j <= i; j++)
			{
				if(acrossworks == false && downworks == false){break;}
				if(!inbounds(x-j,y)){acrossworks = false;}
				if(!inbounds(x,y-j)){downworks = false;}
				if(isletter(x-j-1,y)){acrossworks = false;}
				if(isletter(x-j,y-1)){acrossworks = false;}
				if(isletter(x-j,y+1)){acrossworks = false;}
				if(isletter(x,y-j-1)){downworks = false;}
				if(isletter(x-1,y-j)){downworks = false;}
				if(isletter(x+1,y-j)){downworks = false;}
			}
			for(int j = 1; j < l - i; j++)
			{
				if(acrossworks == false && downworks == false){break;}
				if(!inbounds(x+j,y)){acrossworks = false;}
				if(!inbounds(x,y+j)){downworks = false;}
				if(isletter(x+j+1,y)){acrossworks = false;}
				if(isletter(x+j,y-1)){acrossworks = false;}
				if(isletter(x+j,y+1)){acrossworks = false;}
				if(isletter(x,y+j+1)){downworks = false;}
				if(isletter(x-1,y+j)){downworks = false;}
				if(isletter(x+1,y+j)){downworks = false;}
			}
			if(acrossworks)
			{
				w.setWord(s,x-i,y,"Across ");
				for(int j = 0; j < l; j++)
				{
					edit(x-i+j,y,s[j]);
				}
				return w;
			}
			if(downworks)
			{
				w.setWord(s,x,y-i,"Down   ");
				for(int j = 0; j < l; j++)
				{
					edit(x,y-i+j,s[j]);
				}
				return w;
			}
		}
	}
	return w;
}



bool Board::inbounds(int x, int y)//This function determines whether a tuple is within the bounds of the board
{
    if(x < 0){return false;}
    if(x >= SIZE){return false;}
    if(y < 0){return false;}
    if(y >= SIZE){return false;}
    return true;
}
