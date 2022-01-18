#include <iostream>
#include <cstdlib>
#include <limits>

#include "MainWindow.h";
#include "Settings.h"

using namespace gst;
using namespace std;

int main()
{
	MainWindow window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

	window.render();

	if (STOP_AT_END) {
		cout << "Press ENTER to quit ...";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return EXIT_SUCCESS;
}