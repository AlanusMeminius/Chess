#pragma execution_character_set("utf-8") 

#include "BaseWindow.h"

Ui::BaseWindow::BaseWindow() 
    : centralwidget(new QWidget(this))
    , mainLayout(new QHBoxLayout)
    , chessBoard(new Ui::ChessBoard)
    , sideBar(new Ui::SideBar)
    , campHint(new Ui::CampHint)
    , statusBar(new QStatusBar)
    , trayIcon(new QSystemTrayIcon) 
{
    // set icon, windowSize, objectName
    setWindowIcon(QPixmap(":/icon.png"));
    resize(980, 900);
    setObjectName(QString::fromUtf8("MainWindow"));

    // set central widget
    setCentralWidget(centralwidget);
    centralwidget->setObjectName(QString::fromUtf8("centralWidget"));

    // set main layout
    mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
    centralwidget->setLayout(mainLayout);

    setMainStyle();
    setCampHint();
    setChessBoard();
    setSideBar();
    setSystemTrayIcon();

    setStatusBar(statusBar);
}

void Ui::BaseWindow::showMainWindow() 
{
    show();
}

void Ui::BaseWindow::sendMsg(const QString& msg)  
{
    const QString message = tr(" Status Info | ") + msg;
    statusBar->showMessage(message);
}

void Ui::BaseWindow::setMainStyle() 
{
    QFile styleFile(":/style.qss");
    if (styleFile.open(QFile::ReadOnly))
    {
        const QString style(styleFile.readAll());
        setStyleSheet(style);
    }
    else
    {
        qDebug() << "样式表打开失败，请检查样式表路径是否正确！";
    }
}

void Ui::BaseWindow::setCampHint() 
{
    mainLayout->addWidget(campHint);
    campHint->setMinimumWidth(5);
    campHint->setMaximumWidth(20);
}

void Ui::BaseWindow::setChessBoard()  
{
    chessBoard->setMinimumWidth(500);
    mainLayout->addWidget(chessBoard);
}

void Ui::BaseWindow::setSideBar()  
{
    mainLayout->addWidget(sideBar);
    sideBar->setMaximumWidth(200);
    sideBar->setMinimumWidth(170);
}

void Ui::BaseWindow::setSystemTrayIcon() 
{
}