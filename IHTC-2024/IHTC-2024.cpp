#include <iostream>

#include "MainWindow.h"

static const int STARTING_WIDTH{ 1100 };
static const int STARTING_HEIGHT{ 800 };

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MainWindow mainWindow;
	
	mainWindow.resize(STARTING_WIDTH, STARTING_HEIGHT);
	mainWindow.show();
	
	return app.exec();
}
