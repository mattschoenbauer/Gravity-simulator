// termtest.cpp

#include "terminal.h"
#include <X11/Xlib.h>
#include <unistd.h>
#include <iostream> // for testing
#include "gfx3.h"
using namespace std;

int main() {
	const int w = 500, h = 500;
	gfx_open(w,h, "Terminal Test");
	string test = "testt";
	test += '\b';
	cout << test.c_str() << endl;

	Terminal term(w,h);
	while (true) {
		string entry = term.prompt("enter something: ");
		cout << entry << endl;
	}
	return 0;

}
