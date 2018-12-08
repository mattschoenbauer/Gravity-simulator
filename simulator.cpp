//simulator.cpp
//Gravity simulator
#include <iostream>
#include <unistd.h>
#include "gfx.h"
#include "point_mass.h"
#include <cmath>
#include <tgmath.h>
#include <cstdlib>
#include <vector>
using namespace std;

#define PI 3.14159265
#define rad 80 //radius increment in spiral

void interactive_initialize(vector<Mass>&);
void batch_initialize(vector<Mass>&);
void draw_points(vector<Mass>);
void update(vector<Mass>&);

int main(int argc, char *argv[]){

    string option;

    switch(argc){
        case 1: option = "interactive";
            break;

        case 2: option = "batch";
            break;

        default: cout << "Too many arguments\n";
             return 0;
    }

	int wid = gfx.screenwidth(), ht = gfx.screenwidth();

    vector<Mass> massvect;

    if(option == "interactive"){
        cout << "Entering interactive mode\n";
		cout << "Screen dimension are " << wid << " x " << ht << ".\n";
		initialize(massvect,cin);
    }

    if(option == "batch"){
        string filename = argv[1];//second command will be filename
        ifstream ifs;
        ifs.open(filename);
        while(!ifs){
            cout << "Please input a valid file name\n";//Checking for a valid filename
            cout << "Try again: ";
            cin >> filename;
            cout << endl;
            ifs.open(filename);
        }
		initialize(massvect,ifs);
    }


  gfx_open(wid,ht, "Gravity Simulator");

  while(true) {
	draw_points(massvect);
	update(massvect);
  	if(gfx_event_waiting()){
   		n = gfx_wait();
        if (n == (int)'q') break;
	}
    usleep(40000);
    gfx_clear();
  }

  return 0;
}

void initialize(vector<Mass>& massvect, istream& is){

}
