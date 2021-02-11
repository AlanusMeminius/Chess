#include <QApplication>
#include "ui/StartUpWindow.h"
//#include "core/Application.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    SetUp setUp;
    return QApplication::exec();
}
