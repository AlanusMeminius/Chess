#include "StartUpWindow.h"





SetUp::SetUp() 
    : startUpWindow() 
{
    application = nullptr;
    startUpWindow = new Ui::StartUpWindow;
    for (auto&& item : startUpWindow->modeList)
    {
        connect(item.second, &QPushButton::clicked, this, [this, item](int) { 
            emit btnIndex(item.first.first); 
        });
    }

    connect(this, SIGNAL (btnIndex(int)), this, SLOT (setUpMainWindow(int)));
    startUpWindow->show();
}

SetUp::~SetUp() 
{
    delete startUpWindow;
    delete application;
}

void SetUp::setUpMainWindow(int select)
{
    application = new Application(select);
    if (startUpWindow->exec() == QDialog::Accepted)
    {
        application->show_window();
    }
}