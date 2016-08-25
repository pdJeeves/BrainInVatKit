#include "mainwindow.h"

#include "freetures/catalogue/catalogue_interface.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	initialize_catalogue("catalogue", "en");
	
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	
	return a.exec();
}
