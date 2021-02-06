#include <QApplication>
#include "ui/SplashScreen.h"
#include "./core/Entry.h"

#define DEBUG

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

#ifdef DEBUG
	int select = 1;
	Entry entry(select);
	entry.showWindow();
#endif
#ifndef DEBUG
    SplashScreen splashScreen;
    splashScreen.show();

    Entry entry(splashScreen.Select);

    if (splashScreen.exec() == QDialog::Accepted) {
        entry.showWindow();
    }
#endif
	return QApplication::exec();
}
