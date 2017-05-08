#include "mainwindow.h"

#include <catalogue.h>

#include <QApplication>

int main(int argc, char *argv[])
{
	initialize_catalogue("en");
	
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	
	return a.exec();
}

extern "C"
{
float getHeadRotation(void *, char, char) { return 0; }
int getBodyDirection(void *, char) { return 0; }
}
