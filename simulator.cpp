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

const int wid=gfx_screenwidth();
const int ht=gfx_screenheight();
const int mrgn=gfx_screenheight()/20;
// Terminal term(wid/2, ht/2);

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
	string option;
	gfx_open(wid,ht,"Gravity Simulator");
//	gfx_color(255,255,255);
//	gfx_line(wid/2,0,wid/2,ht/2);
	list<Mass> masslist;
	init(masslist);

	int n = 0;
	while(true) {
		draw_points(masslist);
		update(masslist);
		if(gfx_event_waiting()){
			n = gfx_wait();
			if (n == (int)'q') break;
			if (n == (int)'r') { // WIP
				main();
			}
		}
		usleep(40000);
		gfx_clear();
	}

	return 0;
}

void init(list<Mass>& masslist) {
	static Terminal term(wid/2, ht/2);
//	gfx_color(255,255,255);
	string entry = term.prompt("(i)nput initial condions, or use (p)re-made initial conditions? ", 'b');
	string s0= "Pre-made input options:";
	string s1= "1: Single-planet orbit";
	string s2= "2: Multi-planet orbit";
	string s3= "3: Large random objects";
	string s4= "4: Small random objects";
	string s5= "5: Grid of objects";
	string s6= "6: Ring of objects";
	string s7= "7: Interlaced rings";
	gfx_color(255,255,255);
	term.print(s0);
	term.print("    " + s1);
	term.print("    " + s2);
	term.print("    " + s3);
	term.print("    " + s4);
	term.print("    " + s5);
	term.print("    " + s6);
	term.print("    " + s7);
	if (entry.length() > 1) init(masslist);
	else {
		char e = entry[0];
		if (e == 'i') interactive_initialize(masslist);
		else if (e == 'p') batch_initialize(masslist);
		else init(masslist);
	}
}

void interactive_initialize(list<Mass>& masslist) {
    int wid = gfx_screenwidth();
    int ht = gfx_screenheight();
    Terminal term(wid/2, ht/2); // configurable... account for desired size

    string msg = "Screen dimension are " + to_string(wid) + " x " + to_string(ht) + ".";
    term.print(msg.c_str());
    bool finished = false;
    char c;
    int count = 1;
    Vect center, v, a(0,0);
    double cx,cy,mass,radius;
    while (!finished) {
        term.print("Object " + to_string(count++)); // unsure if ++ comes after method call in precedence, I think this should work...
        cx = atof(term.prompt("Input X Position Coordinate: ", 'd').c_str());
        cy = atof(term.prompt("Input Y Position Coordinate: ", 'd').c_str());
        center.x = cx + wid/2;
        center.y = cy + ht/2;
        mass = atof(term.prompt("Input Mass: ", 'd').c_str());
        radius = atof(term.prompt("Input Radius: ", 'd').c_str());
        v.x = atof(term.prompt("Input X Velocity Coordinate: ", 'd').c_str());
        v.y = atof(term.prompt("Input Y Velocity Coordinate: ", 'd').c_str());
        /* a.x = atof(term.prompt("Input X Acceleration Coordinate: ", 'd').c_str()); */
        /* a.y = atof(term.prompt("Input Y Acceleration Coordinate: ", 'd').c_str()); */

        Mass m(center, mass, radius, v, a);
        masslist.push_back(m);
		m.draw();
        c = term.prompt("Finished (y/n)? ", 'b')[0];
        if (c == 'y') finished = true;
    }
}

void batch_initialize(list<Mass>& masslist) {
    Terminal term(wid/2, ht/2);
	string filename = term.prompt("Enter premade initial conditions or filename: ", 'b');//second command will be filename
	if (filename == "1") {
		random_small_initialize(masslist);
		return;
	}
	if (filename == "2") {
		random_small_initialize(masslist);
		return;
	}
	if (filename == "3") {
		random_small_initialize(masslist);
		return;
	}
	if (filename == "4") {
		random_large_initialize(masslist);
		return;
	}
	if (filename == "5") {
		grid_initialize(masslist);
		return;
	}
	if (filename == "6") {
		ring_initialize(masslist);
		return;
	}
    if (filename == "7") {
        two_ring_initialize(masslist);
        return;
    }
	ifstream ifs;
	ifs.open(filename);
	while(!ifs){
		term.print("Please input a valid file name");//Checking for a valid filename
		filename = term.prompt("Try again: ", 'b');
		ifs.open(filename);
	}
	batch_initialize(masslist,ifs);
	//		for(Mass m : masslist){ cout << m.getRadius() << endl;}
}

void batch_initialize(list<Mass>& masslist, istream& ifs){
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
/*
int main(int argc, char *argv[]){

	string option;
	int wid=gfx_screenwidth();
	int ht=gfx_screenheight();
	gfx_open(wid,ht,"Gravity Simulator");

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
		gfx_open(wid,ht,"Gravity Simulator");
		batch_initialize(masslist,ifs);
		//		for(Mass m : masslist){ cout << m.getRadius() << endl;}
	}

	//Opening the window
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
*/


