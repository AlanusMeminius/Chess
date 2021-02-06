#include "ui/SplashScreen.h"
#include "./core/Application.h"

#define DEBUG

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

#ifdef DEBUG
	int select = 1;
	Application app(select);
    app.show_window();
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
