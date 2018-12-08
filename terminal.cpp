// terminal.cpp

#include "terminal.h"

Terminal::~Terminal() {}

Terminal::Terminal(int w, int h) {
	this->w = w;
	this->h = h;
	font_size = 12;
}

void Terminal::set_font_size(short s) { font_size = s; }
int Terminal::get_font_size(char* text) { return gfx_textpixelheight(text, font); }

void Terminal::print(char* text) {
	static int printY = get_font_size(text);
	gfx_color(255,255,255);
	if (printY > h) {
		terminal_clear();
		printY = 0;
	}
	gfx_text(0, printY, text);
	printY += get_font_size(text);
}

void Terminal::terminal_clear() {
	gfx_color(tbgR, tbgG, tbgB);
	gfx_fill_rectangle(0,0, w, h);
}
