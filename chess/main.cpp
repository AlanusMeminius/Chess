#include <QApplication>
#include "ui/StartUpWindow.h"
#include "core/Application.h"
#define DEBUG

int main(int argc, char* argv[]) 
{
    QApplication a(argc, argv);

#ifndef DEBUG
    SetUp setUp;
#endif
#ifdef DEBUG
    Application application(0);
    application.show_window();
#endif
    return QApplication::exec();
}