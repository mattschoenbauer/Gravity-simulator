// terminal.cpp
// Kyle Duffy and Matt Schoenbauer

#include "terminal.h"
#include <iostream>

Terminal::~Terminal() {}

Terminal::Terminal(int w, int h) {
	this->w = w;
	this->h = h;
	font_size = 12;
}

/* gets and sets */
void Terminal::set_font_size(short s) { font_size = s; }
int Terminal::get_font_size(const char* text) { return gfx_textpixelheight((char*)text, font); }
int Terminal::get_width(const char* text) { return gfx_textpixelwidth((char*)text, font); }

void Terminal::print(const char* text) {
	// prints a single line
	int row = prep_term(text);
	gfx_text(5, row, text);
}
void Terminal::print(string text) { print(text.c_str()); } // adaptation for c++ strings

string Terminal::prompt(const char* msg, char code) {
	// prints a msg and awaits a response, managing which inputs are allowed
	
	string entry;
	int row = prep_term(msg);
	int col = get_width(msg);
	int pt = get_font_size(msg);
	gfx_color(255,255,255);
	gfx_text(0,row,msg);
	int event;
	do {
		event = gfx_event_waiting();
		if (event != 0) {
			int e = (int)gfx_wait();
			if (event == 2) {
				if (e == 13) break;
				if(check_type(e,code)) entry += (char)e;
				else if (e == 8) entry.pop_back();

				gfx_color(tbgR,tbgG,tbgB);
				gfx_fill_rectangle(0,row-pt, w, pt+tween);
				gfx_color(255,255,255);
				gfx_text(0,row,msg);
				gfx_text(col, row, entry.c_str());
			} else {
				continue;
			}
		}
	} while (true);
	return entry;
}
string Terminal::prompt(string msg, char code) { return prompt(msg.c_str(), code); } // adaptation for c++ strings

int Terminal::prep_term(const char* text) {
	// detects end of terminal and formats text location
	
	int pt = get_font_size(text);
	static int printY = pt;
	gfx_color(255,255,255);
	if (printY > h) {
		terminal_clear();
		printY = pt;
	}
	printY += get_font_size(text) + tween;
	return printY - get_font_size(text) - tween;
}

void Terminal::terminal_clear() {
	// clears terminal
	
	gfx_color(tbgR, tbgG, tbgB);
	gfx_fill_rectangle(0,0, w, h);
}

bool Terminal::check_type(int e, char code) {
	// manages which inputs are valid
	
	switch (code) {
		case 'b':
			return (isalpha(e) || isdigit(e) || e == '.');
		case 'd':
			return (isdigit(e) || e == '-');
		case 'p':
			return (isdigit(e));
		default: return true;
	}
}
