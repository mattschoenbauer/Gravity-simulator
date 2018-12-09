// point_mass.cpp

#include "point_mass.h"
#include <iostream>
#include "gfx3.h"
#include <cmath>
#define GG 160000

using namespace std;

Mass::Mass() {
	Vect c; c.x = 0; c.y = 0;
	Vect v(0,0); Vect a(0,0);
	setMass(c,0,1,v,a);
}

Mass::Mass(Vect c, double m, double r, Vect v, Vect a) {
	setMass(c,m,r,v,a);
}

Mass::~Mass(){

}

void Mass::setMa(double mass) { this->mass = mass; }
void Mass::setRadius(double radius) { this->radius = radius; }
void Mass::setVeloc(Vect veloc) { this->veloc = veloc; }
void Mass::setCenter(Vect center) { this->center = center; }
void Mass::setAccel(Vect accel) { this->accel = accel; }
void Mass::setMass(Vect center, double mass, double radius, Vect veloc, Vect accel) {
	setCenter(center);
	setMa(mass);
	setRadius(radius);
	setVeloc(veloc);
	setAccel(accel);
}

Vect Mass::getCenter() { return center; }
double Mass::getRadius() { return radius; }
double Mass::getMa() { return mass; }
Vect Mass::getVelocity() { return veloc; }
Vect Mass::getAcceleration() { return accel; }

//This function draws our point masses.
//The denisty is diplayed by the color of the mass.
//More dense objects are red, less dense objects are blue
void Mass::draw(void){
	double average_radius = 40;
	double average_mass = 100;
	double average_volume = M_PI * pow(average_radius,2);
	double average_density = average_mass/average_volume;
	int max_color = 225;
	double volume = M_PI * pow(getRadius(),2);
	double density = getMa()/volume;
	gfx_color(max_color * (density/average_density)/(1 + density/average_density),0,max_color * 1/(1 + density/average_density));
	Vect center = getCenter();
	gfx_fill_circle(center.x,center.y,getRadius());
	gfx_flush();
}

//Updates the position and velocity based on the acceleration
void Mass::update(void){
	Vect c = getCenter();
	Vect v = getVelocity(), a = getAcceleration();
	double delta_t = .05;//Increasing this value gives slower but more accurate simulations
	c.x = c.x + delta_t*v.x + pow(delta_t,2)*a.x/2.;
	c.y = c.y + delta_t*v.y + pow(delta_t,2)*a.y/2.;
	v.x = v.x + delta_t*a.x;
	v.y = v.y + delta_t*a.y;
	setCenter(c);
	setVeloc(v);
}

//Note that momentum and center of mass are preserved when two objects collide
void Mass::merge(Mass m){
	double new_mass = getMa() + m.getMa();
	Vect c = getCenter(), cc = m.getCenter();
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

//This configues in the contribution of gravity from one point onto another
void Mass::add_acceleration(Mass m){
	float dist = distance(m);
	setAccel((getCenter() + m.getCenter() * (-1))*(-GG*m.getMa()/pow(dist,3)) + getAcceleration());
}

//returns distance between two points
double Mass::distance(Mass m){
    Vect c1 = getCenter(), c2 = m.getCenter();
    return sqrt(pow(c1.x - c2.x,2) + pow(c1.y-c2.y,2));
}
