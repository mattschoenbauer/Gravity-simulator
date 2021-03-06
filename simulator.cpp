//simulator.cpp
//Gravity simulator
//Kyle Duffy and Matt Schoenbauer
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include "gfx3.h"
#include "point_mass.h"
#include "terminal.h"
#include <cmath>
#include <cstdlib>
#include <list>
using namespace std;

#define PI 3.14159265

// global constants that will be used across functions and depend on display
const int wid=gfx_screenwidth();
const int ht=gfx_screenheight();
const int mrgn=gfx_screenheight()/20;

void interactive_initialize(list<Mass>&);
void batch_initialize(list<Mass>&, istream&);
void draw_points(list<Mass>);
void update(list<Mass>&);
void init(list<Mass>&);
void batch_initialize(list<Mass>&);
void random_small_initialize(list<Mass>&);
void random_large_initialize(list<Mass>&);
void grid_initialize(list<Mass>&);
void ring_initialize(list<Mass>&);
Mass random(int,int,int,int);
void two_ring_initialize(list<Mass>&);

int main(){
	srand(time(NULL));
	gfx_open(wid,ht,"Gravity Simulator");
	list<Mass> masslist;
	init(masslist);

	// runs graphics environment
	int n = 0;
	while(true) {
		draw_points(masslist);
		update(masslist);
		if(gfx_event_waiting()){
			n = gfx_wait();
			if (n == (int)'q') break;
			if (n == 27) {
				masslist.clear();
				gfx_clear();
				system("./grav"); // NB: must build with included makefile
				return 0;
			}
		}
		usleep(40000);
		gfx_clear();
	}

	return 0;
}

void init(list<Mass>& masslist) {
	// initializes environment, and gathers user desires

	static Terminal term(wid/2, ht/3);
	string entry = term.prompt("(i)nput initial condions, or use (p)re-made initial conditions? ", 'b');
	if (entry.length() > 1) init(masslist);
	else {
		char e = entry[0];
		if (e == 'i') interactive_initialize(masslist);
		else if (e == 'p') batch_initialize(masslist);
		else init(masslist);
	}
}

void interactive_initialize(list<Mass>& masslist) {
	// initializes environment in interactive mode
	// gathers user input using a Terminal and draws to screen

    int wid = gfx_screenwidth();
    int ht = gfx_screenheight();
    Terminal term(wid/2, ht/3); // configurable... accounts for desired size

    string msg = "Screen dimension are " + to_string(wid) + " x " + to_string(ht) + ".";
    term.print(msg.c_str());
    bool finished = false;
    char c;
    int count = 1;
    Vect center, v, a(0,0);
    double cx,cy,mass,radius;
    while (!finished) {
        term.print("Object " + to_string(count++));
        cx = atof(term.prompt("Input X Position Coordinate: ", 'd').c_str());
        cy = atof(term.prompt("Input Y Position Coordinate: ", 'd').c_str());
        center.x = cx + wid/2;
        center.y = cy + ht/2;
        mass = atof(term.prompt("Input Mass: ", 'p').c_str());
        radius = atof(term.prompt("Input Radius: ", 'p').c_str());
        v.x = atof(term.prompt("Input X Velocity Coordinate: ", 'd').c_str());
        v.y = atof(term.prompt("Input Y Velocity Coordinate: ", 'd').c_str());

        Mass m(center, mass, radius, v, a);
        masslist.push_back(m);
		m.draw();
        c = term.prompt("Finished (y/n)? ", 'b')[0];
        if (c == 'y') finished = true;
    }
}

void batch_initialize(list<Mass>& masslist) {
	// initializes environment in batch mode
	// in this mode the window is congigured using pre-existing conditions

    Terminal term(wid/2, ht/3);
	bool not_cool = false;
	ifstream ifs;

	// menu
	string s0= "Pre-made input options:";
	string s1= "1: Large random objects";
	string s2= "2: Small random objects";
	string s3= "3: Grid of objects";
	string s4= "4: Ring of objects";
	string s5= "5: Interlaced rings";
	string s6= "6: Single-planet orbit";
	string s7= "7: Multi-planet orbit";
	string s8= "8: Neutron stars";

	gfx_color(255,255,255);
	do {
		// print menu
		term.print(s0);
		term.print("    " + s1);
		term.print("    " + s2);
		term.print("    " + s3);
		term.print("    " + s4);
		term.print("    " + s5);
		term.print("    " + s6);
		term.print("    " + s7);
		term.print("    " + s8);
		string filename = term.prompt("Enter premade initial conditions or filename: ", 'b');//second command will be filename

		if (filename == "1") {
			random_large_initialize(masslist);
			return;
		}
		if (filename == "2") {
			random_small_initialize(masslist);
			return;
		}
		if (filename == "3") {
			grid_initialize(masslist);
			return;
		}
		if (filename == "4") {
			ring_initialize(masslist);
			return;
		}
		if (filename == "5") {
			two_ring_initialize(masslist);
			return;
		}
		if (filename == "6") {
			filename = "orbit1";
		}
		if (filename == "7") {
			filename = "orbit2";
		}
		if (filename == "8") {
			filename = "neutron";
		}
		ifs.open(filename);
		if (!ifs){
			term.print("File not found, try again.");//Checking for a valid filename
			not_cool = true;
		}
	} while (not_cool);

	batch_initialize(masslist,ifs);
}

void batch_initialize(list<Mass>& masslist, istream& ifs){
	// processes data and objects to the master list

	int wid=gfx_screenwidth();
	int ht=gfx_screenheight();
	double cx, cy, mass, radius;
	Vect center, v, a(0,0);
	ifs >> cx;
	while(!ifs.eof()){
		ifs >> cy;
		center.x = cx + wid /2;
		center.y = cy + ht /2;
		ifs >> mass;
		ifs >> radius;
		ifs >> v.x;
		ifs >> v.y;
		Mass m(center,mass,radius,v,a);
		masslist.push_back(m);
		ifs >> cx;
	}
}

/* Functions that generate pre-configured scenarios */
void random_large_initialize(list<Mass>& masslist) {
	const int num = 15;
	for (int i = 0; i < num; i++) {
		masslist.push_back(random(10,30,1,8));
	}
}

void random_small_initialize(list<Mass>& masslist) {
	const int num = 40;
	for (int i = 0; i < num; i++) {
		masslist.push_back(random(3,10,1,10));
	}
}

Mass random(int r_min, int r_max, int m_min, int m_max) {
	Vect c,v(0,0),a(0,0);
	double r = (double)(r_min + (rand()%(r_max-r_min+1)));
	double m = (double)(m_min + (rand()%(m_max-m_min+1)));
	c.x = (double)(mrgn + (int)r + (rand()%(wid-2*mrgn-(int)r+1)));
	c.y = (double)(mrgn + (int)r + (rand()%(ht-2*mrgn-(int)r+1)));
	return Mass(c,m,r,v,a);
}

void grid_initialize(list<Mass>& masslist) {
    Vect zero(0,0), center;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j< 7; j++){
            center.x = mrgn + i * wid/10;
            center.y = mrgn + j*ht/7;
            Mass m(center,1,3.8,zero,zero);
            masslist.push_back(m);
        }
    }
}

void ring_initialize(list<Mass>& masslist) {
    Vect zero(0,0), center;
    double radius = 3 * ht/8.;
    for(int i = 0; i < 50; i++){
        center.x = wid/2 + radius * cos(2 * M_PI * i/50.);
        center.y = ht/2 + radius * sin(2 * M_PI * i/50.);
        Mass m(center,.3,3.5,zero,zero);
        masslist.push_back(m);
    }
}

void two_ring_initialize(list<Mass>& masslist) {
    Vect zero(0,0), center;
    double radius = 1 * ht/3.;
    for(int i = 0; i < 50; i++){
        center.x = 2*wid/3 + radius * cos(2 * M_PI * i/50.);
        center.y = ht/2 + radius * sin(2 * M_PI * i/50.);
        Mass m(center,.5,4,zero,zero);
        masslist.push_back(m);
    }
    for(int i = 0; i < 50; i++){
        center.x = wid/3 + radius * cos(2 * M_PI * i/50.);
        center.y = ht/2 + radius * sin(2 * M_PI * i/50.);
        Mass m(center,.5,4,zero,zero);
        masslist.push_back(m);
    }
}

/* Update and manage window */
void draw_points(list<Mass> masslist){
	// draws all the masses
	for(Mass m : masslist){m.draw();}
}

void update(list<Mass>& masslist){
	// updates relative effect of gravity on each mass

	for(auto itr = masslist.begin(); itr != masslist.end(); itr++){
		for(auto itr2 = next(itr,1); itr2 != masslist.end(); itr2++){
			if((*itr).distance(*itr2) <= (*itr).getRadius() + (*itr2).getRadius()){
				(*itr).merge(*itr2);
				masslist.erase(itr2);
			}
		}
	}
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
		(*itr).update();
	}
}

