// point_mass.cpp

#include "point_mass.h"
#include <iostream>
#include "gfx3.h"
#include <cmath>
#define GG 1

using namespace std;

Mass::Mass() {
	XPoint c; c.x = 0; c.y = 0;
	Vect v(0,0); Vect a(0,0);
	setMass(c,0,1,v,a);
}

Mass::Mass(XPoint c, double m, double r, Vect v, Vect a) {
	setMass(c,m,r,v,a);
}

Mass::~Mass(){

}

void Mass::setMa(double mass) { this->mass = mass; }
void Mass::setRadius(double radius) { this->radius = radius; }
void Mass::setVeloc(Vect veloc) { this->veloc = veloc; }
void Mass::setCenter(XPoint center) { this->center = center; }
void Mass::setAccel(Vect accel) { this->accel = accel; }
void Mass::setMass(XPoint center, double mass, double radius, Vect veloc, Vect accel) {
	setCenter(center);
	setMa(mass);
	setRadius(radius);
	setVeloc(veloc);
	setAccel(accel);
}

XPoint Mass::getCenter() { return center; }
double Mass::getRadius() { return radius; }
double Mass::getMa() { return mass; }
Vect Mass::getVelocity() { return veloc; }
Vect Mass::getAcceleration() { return accel; }

void Mass::draw(void){
	double average_radius = 7;
	double average_mass = 40;
	double average_volume = M_PI * pow(average_radius,2);
	double average_density = average_mass/average_volume;
	int max_color = 225;
	double volume = M_PI * pow(getRadius(),2);
	double density = getMa()/volume;
	gfx_color(max_color * (density/average_density)/(1 + density/average_density),0,max_color * 1/(1 + density/average_density));
	XPoint center = getCenter();
	gfx_fill_circle(center.x,center.y,getRadius());
}

void Mass::update(void){
	XPoint c = getCenter();
	Vect v = getVelocity(), a = getAcceleration();
//	cout << "Position is " << c.x << "," << c.y << endl;
//	cout << "Velocity is " << v.x << "," << v.y << endl;
	c.x = c.x + v.x/20.;
	c.y = c.y + v.y/20.;
	v.x = v.x + a.x/20.;
	v.y = v.y + a.y/20.;
	setCenter(c);
	setVeloc(v);
//	cout << "Position is " << c.x << "," << c.y << endl;
//	cout << "Velocity is " << v.x << "," << v.y << endl;
}

void Mass::merge(Mass m){
	double new_mass = getMa() + m.getMa();
	XPoint c = getCenter(), cc = m.getCenter();
	Vect v = getVelocity(), vv = m.getVelocity();
	c.x = (c.x * getMa() + cc.x * m.getMa())/(new_mass);
	c.y = (c.y * getMa() + cc.y * m.getMa())/(new_mass);
	v.x = (v.x * getMa() + vv.x * m.getMa())/(new_mass);
	v.y = (v.y * getMa() + vv.y * m.getMa())/(new_mass);
	setRadius(sqrt(pow(getRadius(),2) + pow(m.getRadius(),2)));
	setVeloc(v);
	setCenter(c);
	setMa(new_mass);
}

void Mass::compute_acceleration(Mass){

}
