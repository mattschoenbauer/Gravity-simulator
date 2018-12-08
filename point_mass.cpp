// point_mass.cpp

#include "point_mass.h"

#include<cmath>
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
double Mass::getMass() { return mass; }
Vect Mass::getVelocity() { return veloc; }
Vect Mass::getAcceleration() { return accel; }

void Mass::draw(void){
	double average_radius = 7;
	double average_mass = 40;
	double average_volume = M_PI * pow(average_radius,2);
	double average_density = average_mass/average_volume;
	int color_max = 225;
	double volume = M_PI * pow(getRadius(),2);
	double density = getMa()/volume;
	gfx_color(max_color * (density/average_density)/(1 + density/average_density),0,max_color * 1/(1 + density/average_density));
	XPoint center = getCenter();
	gfx_fill_circle(center.x,center.y,getRadius);
}

void Mass::update(void){
	XPoint c = getCenter();
	Vect v = getVelocity(), a = getAcceleration();
	c.x = c.x + v.x;
	c.y = c.y + v.y;
	v.x = v.x + a.x;
	v.y = v.y + a.y;
}

void Mass::merge(Mass m){
	setMa(getMa
}

void Mass::compute_acceleration(Mass){

}
