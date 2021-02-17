#ifndef CHESS_BASEWINDOW_H
#define CHESS_BASEWINDOW_H

#include <QFile>
#include <QMainWindow>
#include <QStatusBar>
#include <QPropertyAnimation>
#include <QtWidgets/QWidget>

#include "ChessBoard.h"
#include "SideBar.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class BaseWindow : public QMainWindow {
    Q_OBJECT
    private:
        QPropertyAnimation *animation;
        QWidget *centralwidget;
        QHBoxLayout *mainLayout;
    public:
        Ui::ChessBoard *chessBoard;
        Ui::SideBar *sideBar;
        Ui::CampHint *campHint;
        QStatusBar *statusBar;
    public:
        BaseWindow() :
                centralwidget(new QWidget(this)),
                mainLayout(new QHBoxLayout),
                chessBoard(new Ui::ChessBoard),
                sideBar(new Ui::SideBar),
                campHint(new Ui::CampHint),
                statusBar(new QStatusBar),
                animation(new QPropertyAnimation) {
            // set icon, windowSize, objectName
            this->setWindowIcon(QPixmap(":/icon.png"));
            this->resize(980, 900);
            this->setObjectName(QString::fromUtf8("MainWindow"));

            // set central widget
            this->setCentralWidget(centralwidget);
            centralwidget->setObjectName(QString::fromUtf8("centralWidget"));

            // set style
            QFile styleFile(":/style.qss");
            styleFile.open(QFile::ReadOnly);
            const QString style(styleFile.readAll());
            this->setStyleSheet(style);

            animation->setTargetObject(this);
            animation->setPropertyName(QByteArray("windowOpacity"));
            animation->setDuration(800);

            // set main layout
            mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
            centralwidget->setLayout(mainLayout);

            // add camp hint
            mainLayout->addWidget(campHint);
            campHint->setMinimumWidth(5);
            campHint->setMaximumWidth(20);
            // add chess board
            chessBoard->setMinimumWidth(500);
            mainLayout->addWidget(chessBoard);

            // add sidebar
            mainLayout->addWidget(sideBar);
            sideBar->setMaximumWidth(200);
            sideBar->setMinimumWidth(150);

            setStatusBar(statusBar);
        }

        void showMainWindow() {
            show();
        }

        void sendMsg(const QString &msg) const {
            QString message = tr(" Status Info | ") + msg;
            statusBar->showMessage(message);
        }

    };
}
QT_END_NAMESPACE

#endif //CHESS_BASEWINDOW_H
