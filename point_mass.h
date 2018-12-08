//point_mass.h

#ifndef POINT_MASS_H
#define POINT_MASS_H

#include <X11/Xlib.h>
using namespace std;

struct Vect {
	double x,y;
	Vect() { x = 0.; y = 0.; }
	Vect(double x, double y) { this->x = x; this->y = y; }
	Vect operator+(Vect v) { Vect u(x+v.x, y+v.y); return u; } 
};


class Mass {
	public:
		Mass();
		~Mass();
		Mass(XPoint center, double mass, double radius, Vect veloc, Vect accel);
		void setMass(XPoint center, double mass, double radius, Vect veloc, Vect accel);
		void setMa(double mass);
		void setVeloc(Vect);
		void setRadius(double);
		void setCenter(XPoint);
		void setAccel(Vect);
		XPoint getCenter(void);
		Vect getVelocity(void);
		Vect getAcceleration(void);
		double getMass(void);
		double getRadius(void);
		double getDensity(void);
		void draw(void);
		void update(void);
		void merge(Mass);
		void compute_acceleration(Mass);
	private:
		XPoint center;
		double radius;
		double mass;
		Vect veloc;
		Vect accel;
};

#endif
