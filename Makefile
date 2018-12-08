# Makefile for lab11

fractals: fractals.cpp
	g++ fractals.cpp gfx.o -lX11 -o fractals

clean:
	rm fractals

