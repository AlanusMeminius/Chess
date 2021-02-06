
#ifndef CHESS_BASEWINDOW_H
#define CHESS_BASEWINDOW_H

#include <QFile>
#include <QMainWindow>
#include <QtCore/QVariant>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>

#include "ChessBoard.h"
#include "SideBar.h"

class BaseWindow : public QMainWindow {
Q_OBJECT
private:
    QWidget *centralwidget;
    QHBoxLayout *mainLayout;
public:
    ChessBoard *chessBoard;
    SideBar *sideBar;
public:
    BaseWindow() :
            centralwidget(new QWidget(this)),
            mainLayout(new QHBoxLayout(centralwidget)),
            chessBoard(new ChessBoard),
            sideBar(new SideBar) {
        // set icon, windowSize, objectName
        this->setWindowIcon(QPixmap(":/resources/icon.png"));
        this->resize(980, 900);
        this->setObjectName(QString::fromUtf8("MainWindow"));

        // set central widget
        this->setCentralWidget(centralwidget);
        centralwidget->setObjectName(QString::fromUtf8("centralWidget"));

        // set style
        QFile styleFile(":/resources/style.qss");
        styleFile.open(QFile::ReadOnly);
        QString style(styleFile.readAll());
        this->setStyleSheet(style);

        // set main layout
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        centralwidget->setLayout(mainLayout);

        // add chess board
        chessBoard->setMinimumWidth(500);
        mainLayout->addWidget(chessBoard);

        // add sidebar
        mainLayout->addWidget(sideBar);
        sideBar->setMaximumWidth(200);
    };

};

#endif //CHESS_BASEWINDOW_H
