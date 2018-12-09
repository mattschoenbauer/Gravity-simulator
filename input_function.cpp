// input function TEMPORARY FILE

// needs inclusion of cstdlib library
void interactive_init(list<Mass>& masslist) {
	int wid = gfx_screenwidth();
	int ht = gfx_screenheight();
	Terminal term(wid/2, ht/2); // configurable... account for desired size

	string msg = "Screen dimension are " + wid.to_string() + " x " + ht.to_string() + ".\n";
	term.print(msg.c_str());
	bool finished = false;
	char c;
	int count = 1;
	Vect center, v, a;
	double cx,cy,mass,radius;
	while (!finished) {
		term.print("Object " + count++.to_string()); // unsure if ++ comes after method call in precedence, I think this should work...
		cx = atof(term.prompt("Input X Position Coordinate: "));
		cy = atof(term.prompt("Input Y Position Coordintae: "));
		center.x = cx + wid/2;
		center.y = cy + ht/2;
		mass = atof(term.prompt("Input Mass: "));
		radius = atof(term.prompt("Input Radius: "));
		v.x = atof(term.prompt("Input X Velocity Coordinate: "));
		v.y = atof(term.prompt("Input Y Velocity Coordinate: "));
		a.x = atof(term.prompt("Input X Acceleration Coordinate: "));
		a.y = atof(term.prompt("Input Y Acceleration Coordinate: "));

		Mass m(center, mass, radius, v, a);
		masslist.push_back(m);
		c = term.prompt("Finished (y/n)? ")[0];
		if (c == 'y') finished = true;
	}
}
