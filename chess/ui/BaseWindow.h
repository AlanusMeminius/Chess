#pragma once

#include <QFile>
#include <QMainWindow>
#include <QStatusBar>
#include <QSystemTrayIcon>
#include <QtWidgets/QWidget>

#include "ChessBoard.h"
#include "SideBar.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class BaseWindow final : public QMainWindow {
    Q_OBJECT
    private:
        QWidget* centralwidget;
        QHBoxLayout* mainLayout;
    public:
        Ui::ChessBoard* chessBoard;
        Ui::SideBar* sideBar;
        Ui::CampHint* campHint;
        QStatusBar* statusBar;
        QSystemTrayIcon* trayIcon;
    public:
        BaseWindow() :
            centralwidget(new QWidget(this)),
            mainLayout(new QHBoxLayout),
            chessBoard(new Ui::ChessBoard),
            sideBar(new Ui::SideBar),
            campHint(new Ui::CampHint),
            statusBar(new QStatusBar),
            trayIcon(new QSystemTrayIcon) {
            // set icon, windowSize, objectName
            this->setWindowIcon(QPixmap(":/icon.png"));
            this->resize(980, 900);
            this->setObjectName(QString::fromUtf8("MainWindow"));

            // set central widget
            this->setCentralWidget(centralwidget);
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

        void showMainWindow() {
            show();
        }

        void sendMsg(const QString& msg) const {
            const QString message = tr(" Status Info | ") + msg;
            statusBar->showMessage(message);
        }

        void setMainStyle() {
            QFile styleFile(":/style.qss");
            styleFile.open(QFile::ReadOnly);
            const QString style(styleFile.readAll());
            this->setStyleSheet(style);
        }

        void setCampHint() const {
            mainLayout->addWidget(campHint);
            campHint->setMinimumWidth(5);
            campHint->setMaximumWidth(20);
        }

        void setChessBoard() const {
            chessBoard->setMinimumWidth(500);
            mainLayout->addWidget(chessBoard);
        }

        void setSideBar() const {
            mainLayout->addWidget(sideBar);
            sideBar->setMaximumWidth(200);
            sideBar->setMinimumWidth(170);
        }

        void setSystemTrayIcon() {
        }
    };
}

QT_END_NAMESPACE
