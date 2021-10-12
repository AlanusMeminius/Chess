
#include "BaseWindow.h"

BaseWindow::BaseWindow() 
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