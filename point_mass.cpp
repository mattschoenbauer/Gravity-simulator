// point_mass.cpp

#include "point_mass.h"
using namespace std;

Mass::Mass() {
	XPoint c; c.x = 0; c.y = 0;
	Vect v(0,0); Vect a(0,0);
	setMass(c,0,1,v,a);
}

Mass::Mass(XPoint c, double m, double r, Vect v, Vect a) {
	setMass(c,m,r,v,a);
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