#include "mainwindow.h"

#include <catalogue.h>

#include <QApplication>

int main(int argc, char *argv[])
{
	initialize_catalogue("catalogue", "en");
	
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	
	return a.exec();
}
