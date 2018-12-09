//simulator.cpp
//Gravity simulator
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include "gfx3.h"
#include "point_mass.h"
#include "terminal.h"
#include <cmath>
#include <tgmath.h>
#include <cstdlib>
#include <list>
using namespace std;

#define PI 3.14159265

void interactive_initialize(list<Mass>&);
void batch_initialize(list<Mass>&, istream&);
void draw_points(list<Mass>);
void update(list<Mass>&);

int main(int argc, char *argv[]){

    string option;
	int wid=gfx_screenwidth();
	int ht=gfx_screenheight();

    switch(argc){
        case 1: option = "interactive";
            break;

        case 2: option = "batch";
            break;

        default: cout << "Too many arguments\n";
             return 0;
    }


    list<Mass> masslist;

    if(option == "interactive"){
        cout << "Entering interactive mode\n";
		interactive_initialize(masslist);
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
		batch_initialize(masslist,ifs);
//		for(Mass m : masslist){ cout << m.getRadius() << endl;}
    }

//Opening the window
  gfx_open(wid,ht,"Gravity Simulator");
  int n = 0;

  while(true) {
	draw_points(masslist);
	update(masslist);
  	if(gfx_event_waiting()){
   		n = gfx_wait();
        if (n == (int)'q') break;
	}
    usleep(40000);
    gfx_clear();
  }

  return 0;
}

void interactive_initialize(list<Mass>& masslist) {
    int wid = gfx_screenwidth();
    int ht = gfx_screenheight();
    Terminal term(wid/2, ht/2); // configurable... account for desired size

    string msg = "Screen dimension are " + to_string(wid) + " x " + to_string(ht) + ".\n";
    term.print(msg.c_str());
    bool finished = false;
    char c;
    int count = 1;
    Vect center, v, a;
    double cx,cy,mass,radius;
    while (!finished) {
        term.print("Object " + to_string(count++)); // unsure if ++ comes after method call in precedence, I think this should work...
        cx = atof(term.prompt("Input X Position Coordinate: ").c_str());
        cy = atof(term.prompt("Input Y Position Coordinate: ").c_str());
        center.x = cx + wid/2;
        center.y = cy + ht/2;
        mass = atof(term.prompt("Input Mass: ").c_str());
        radius = atof(term.prompt("Input Radius: ").c_str());
        v.x = atof(term.prompt("Input X Velocity Coordinate: ").c_str());
        v.y = atof(term.prompt("Input Y Velocity Coordinate: ").c_str());
        a.x = atof(term.prompt("Input X Acceleration Coordinate: ").c_str());
        a.y = atof(term.prompt("Input Y Acceleration Coordinate: ").c_str());

        Mass m(center, mass, radius, v, a);
        masslist.push_back(m);
        c = term.prompt("Finished (y/n)? ")[0];
        if (c == 'y') finished = true;
    }
}


//void interactive_initialize(list<Mass>& masslist){
//	int wid=gfx_screenwidth();
//	int ht=gfx_screenheight();
//	cout << "Screen dimension are " << wid << " x " << ht << ".\n";
//	bool finished = false;
//	char c;
//	int count = 1;
//	double cx, cy, vx, vy, ax, ay, mass, radius;
//	Vect center;
////	Vect accel(0,0);
//	while(!finished){
//		cout << "Object " << count << endl << endl;
//		cout << "Input X Position Coordinate: ";
//		cin >> cx;
//		cout << endl;
//		cout << "Input Y Position Coordinate: ";
//		cin >> cy;
//		cout << endl;
//		center.x = cx+ wid /2;
//		center.y = cy+ ht /2;
//		cout << "Input Mass: ";
//		cin >> mass;
//		cout << endl;
//		cout << "Input Radius: ";
//		cin >> radius;
//		cout << endl;
//		cout << "Input X Velocity Coordinate: ";
//		cin >> vx;
//		cout << endl;
//		cout << "Input Y Velocity Coordinate: ";
//		cin >> vy;
//		Vect veloc(vx,vy);
//		cout << endl;
//		cout << "Input X Acceleration Coordinate: ";
//		cin >> ax;
//		cout << endl;
//		cout << "Input Y Acceleration Coordinate: ";
//		cin >> ay;
//		Vect accel(ax,ay);
//		cout << endl;
//		Mass m(center,mass,radius,veloc,accel);
//		count++;
//		masslist.push_back(m);
//		cout << "Finished? ";
//		cin >> c;
//		cout << endl;
//		if(c == 'y'){finished = true;}
//	}
//}

void batch_initialize(list<Mass>& masslist, istream& ifs){
	int wid=gfx_screenwidth();
	int ht=gfx_screenheight();
	double cx, cy, vx, vy, ax, ay, mass, radius;
	Vect center;
//	char c = ifs.peek();
//	int count = 1;
	ifs >> cx;
	while(!ifs.eof()){
//		Vect accel(0,0);
//		cout << "cx is " << cx << endl;
//		if(cx == (int)'.'){break;}
		ifs >> cy;
		center.x = cx + wid /2;
		center.y = cy + ht /2;
		ifs >> mass;
		ifs >> radius;
//		cout << "Object " << count << " radius: " << radius << endl;
//		count++;
		ifs >> vx;
		ifs >> vy;
		Vect veloc(vx,vy);
		ifs >> ax;
		ifs >> ay;
		Vect accel(ax,ay);
		Mass m(center,mass,radius,veloc,accel);
		masslist.push_back(m);
		ifs >> cx;
//		cout << ifs.eof() << endl;
//		c = ifs.peek();
//		cout << c << endl;
	}
}

void draw_points(list<Mass> masslist){
	for(Mass m : masslist){m.draw();}
}

void update(list<Mass>& masslist){
	for(auto itr = masslist.begin(); itr != masslist.end(); itr++){
		for(auto itr2 = next(itr,1); itr2 != masslist.end(); itr2++){
			if((*itr).distance(*itr2) <= (*itr).getRadius() + (*itr2).getRadius()){
				(*itr).merge(*itr2);
				masslist.erase(itr2);
			}
		}
	}
//	int count = 1;
	//Now computing accelerations
	Vect zero(0,0);
	for(auto itr = masslist.begin(); itr != masslist.end(); itr++){
		(*itr).setAccel(zero);
		for(auto itr2 = masslist.begin(); itr2 != masslist.end(); itr2++){
			if(itr != itr2){
				(*itr).add_acceleration(*itr2);
			}
		}
	}
	for(auto itr = masslist.begin(); itr != masslist.end(); itr++){
//		cout << "Updating Point " << count << endl;
		(*itr).update();
//		count++;
	}
}
