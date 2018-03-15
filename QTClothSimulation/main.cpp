#include "qtclothsimulation.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTClothSimulation w;
	w.show();
	return a.exec();
}
