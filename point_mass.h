//point_mass.h
//Class implementation of circular objects

#ifndef POINT_MASS_H
#define POINT_MASS_H

#include <X11/Xlib.h>
using namespace std;

struct Vect {
	double x,y;
	Vect() { x = 0.; y = 0.; }
	Vect(double x, double y) { this->x = x; this->y = y; }
	Vect operator+(Vect v) { Vect u(x+v.x, y+v.y); return u; }
	Vect operator*(double t) { Vect u(t*x, t*y); return u; }
};


class Mass {
	public:
		Mass();
		~Mass();
		Mass(Vect center, double mass, double radius, Vect veloc, Vect accel);
		void setMass(Vect center, double mass, double radius, Vect veloc, Vect accel);
		void setMa(double mass);
		void setVeloc(Vect);
		void setRadius(double);
		void setCenter(Vect);
		void setAccel(Vect);
		Vect getCenter(void);
		Vect getVelocity(void);
		Vect getAcceleration(void);
		double getMa(void);
		double getRadius(void);
		void draw(void);
		void update(void);
		void merge(Mass);//This merges two points into one, preserving center of mass and momentum
		void add_acceleration(Mass);
		double distance(Mass);
	private:
		Vect center;
		double radius;
		double mass;
		Vect veloc;
		Vect accel;
};

#endif
