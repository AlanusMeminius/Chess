#include <QApplication>

#include "ui/StartUpWindow.h"
#include "core/Application.h"

int main(int argc, char* argv[]) 
{
    QApplication a(argc, argv);
    Application application(Application::SigleMode);
    application.show_window();

    return QApplication::exec();
}