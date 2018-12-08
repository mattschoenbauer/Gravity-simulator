// termtest.cpp

#include "terminal.h"
#include <X11/Xlib.h>
#include <unistd.h>
#include "gfx3.h"
using namespace std;

int main() {
	const int w = 500, h = 500;
	gfx_open(w,h, "Terminal Test");

	Terminal term(w,h);
	while (true) {
		int e = (int)gfx_wait();
		if (e == 27) break;
		else if (e == ' ') term.print("Hello this is a test");
		usleep(10000);
	}
	return 0;

}