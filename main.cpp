#include <QApplication>
#include "core/Splashscreen.h"
#include "core/Mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    SplashScreen splashScreen;
    splashScreen.show();

    MainWindow mainWindow(splashScreen.Select);

    if (splashScreen.exec() == QDialog::Accepted) {
        mainWindow.show();
    }
    return QApplication::exec();
}
