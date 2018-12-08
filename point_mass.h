//point_mass.h

#include <X11/Xlib.h>
using namespace std;

struct Vect {
	int x,y;
	Vect operator+(Vect v) { Vect u; u.x = x + v.x; u.y = y + v.y; return u; }
};


class Mass {
	public:
		Mass();
		Mass(XPoint center, double mass);
		Mass(XPoint center, double mass, double radius);
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
		Vect veloc;
		Vect accel;
		double radius;
		double mass;
};

