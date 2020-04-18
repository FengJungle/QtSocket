#include "Server.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Server w;
	w.show();
	return a.exec();
}
