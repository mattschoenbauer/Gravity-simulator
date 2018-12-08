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

void interactive_initialize(vector<Mass>&);
void batch_initialize(vector<Mass>&, istream&);
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
		interactive_initialize(massvect,cin);
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
		batch_initialize(massvect,ifs);
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

void interactive_initialize(list<Mass>& masslist){
	bool finished = false;
	int count = 1;
	double cx, cy, vx, vy, mass, radius;
	XPoint center;
	Vect accel(0,0);
	while(!finished){
		cout << "Object " << count << endl << endl;
		cout << "Input X Position Coordinate ";
		cin << cx;
		cout << endl << endl;
		cout << "Input Y Position Coordinate ";
		cin << cy;
		cout << endl << endl;
		center.x = cx;
		center.y = cy;
		cout << "Input Mass ";
		cin << mass;
		cout << endl << endl;
		cout << "Input Radius ";
		cin << radius;
		cout << endl << endl;
		cout << "Input X Velocity Coordinate ";
		cin << vx;
		cout << endl << endl;
		cout << "Input Y Velocity Coordinate ";
		cin << vy;
		Vect veloc(vx,vy);
		cout << endl << endl;
		Mass m(center,mass,radius,veloc,accel);
		count++;
		masslist.push_back(m);
	}
}
