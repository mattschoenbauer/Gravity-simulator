//funanim.cpp
//This program creates a moving spiral in yellow, and when the user clicks on the screen blue squares will "fall down" the spiral
#include <iostream>
#include <unistd.h>
#include "gfx.h"
#include <cmath>
#include <tgmath.h>
#include <cstdlib>
#include <vector>
using namespace std;

#define dim 900//Dimensions of the square window
#define PI 3.14159265
#define rad 80 //radius increment in spiral
#define clicks 16//number of lines in polygonal approximation of one loop in spiral

void draw_spiral(int);
vector<vector<float> > draw_squares(vector<vector<float> >);

int main()
{
  gfx_open(dim, dim, "A fun animation");

  gfx_color(255,255,0);

  int count = 0;
  int xc, yc;
  int n = 0;
  vector<vector<float> > square_list;

  while(true) {
	draw_spiral(count);
	square_list = draw_squares(square_list);
	count++;

    if(gfx_event_waiting()) {
      n = gfx_wait();
      if (n == (int)'q') break;
	  if (n == 1)//This is the situation where we add a square
	  {
		xc = gfx_xpos();
		yc = gfx_ypos();
		vector<float> square_vect;
		square_vect.push_back(xc);
		square_vect.push_back(yc);
		square_list.push_back(square_vect);
		n = 0;
	  }
  	}

    usleep(40000);
    gfx_clear();
  }

  return 0;
}

void draw_spiral(int count)//This draws a polygonal approximations of a spiral,with each circle of radius rad, and clicks many pines per circle. count will be increasing every time the functions is called, so as to create the effect of motion
{
  	gfx_color(255,255,0);
	int radius = 0, x0, y0, x1 = dim/2, y1 = dim/2, i = count - 1;
	while(radius <= dim/2*sqrt(2))
	{
		x0 = x1;
		y0 = y1;
		x1 = dim/2 + radius*sin(2* PI * i/((float)clicks));
		y1 = dim/2 + radius*cos(2* PI * i/((float)clicks));
		gfx_line(x0,y0,x1,y1);
		radius += rad/clicks;
		i++;
	}
}


vector<vector<float> > draw_squares(vector<vector<float> > square_list)//This draws squares centered at coordinates in the list, and returns an updated list
{
	gfx_color(0,0,225);
	vector<vector<float> > returnvect;
	int max_radius = 100, x, y;
	for(vector<float> square : square_list)
	{
		x = square[0], y = square[1];
		float d = sqrt(pow((x-dim/2),2) + pow((y-dim/2),2));
		float square_rad = max_radius * d * 2/((float)dim);
		//Drawing the square
		gfx_line(x-square_rad,y-square_rad,x-square_rad,y+square_rad);
		gfx_line(x-square_rad,y-square_rad,x+square_rad,y-square_rad);
		gfx_line(x+square_rad,y-square_rad,x+square_rad,y+square_rad);
		gfx_line(x+square_rad,y+square_rad,x-square_rad,y+square_rad);
		float scale = 1 - rad/((float)clicks * d);//decreasing distance to center
		float newx = scale * (x-dim/2) + dim/2;
		float newy = scale * (y-dim/2) + dim/2;
		if(abs(newx-dim/2)> 4 || abs(newy-dim/2) > 4)//We only keep the square if it is not too close to the center
		{
			vector<float> newvect;
			newvect.push_back(newx);
			newvect.push_back(newy);
			returnvect.push_back(newvect);
		}
	}
	return returnvect;
}


