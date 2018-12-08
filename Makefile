# Makefile for lab11

fractals: simulator.cpp point_mass.o
	g++ -std=c++11 simulator.cpp gfx3_mac.o point_mass.o -I/usr/X11/include/ -L/usr/X11/lib/ -lX11 -o grav
	rm point_mass.o

point_mass.o: point_mass.cpp
	g++ -std=c++11 -c point_mass.cpp -I/usr/X11/include/ -L/usr/X11/lib/ -lX11 -o point_mass.o

clean:
	rm grav point_mass.o

