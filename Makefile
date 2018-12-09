# Makefile for lab12

grav: simulator.cpp point_mass.o terminal.o
	g++ -std=c++11 simulator.cpp gfx3_mac.o point_mass.o terminal.o -I/usr/X11/include/ -L/usr/X11/lib/ -lX11 -o grav
	rm point_mass.o terminal.o

point_mass.o: point_mass.cpp
	g++ -std=c++11 -c point_mass.cpp -I/usr/X11/include/ -o point_mass.o

terminal.o: terminal.cpp
	g++ -std=c++11 -c terminal.cpp -I/usr/X11/include/ -o terminal.o

clean:
	rm grav point_mass.o

