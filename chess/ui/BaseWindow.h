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
    BaseWindow();

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
        setStyleSheet(style);
    }

    void setCampHint() {
        mainLayout->addWidget(campHint);
        campHint->setMinimumWidth(5);
        campHint->setMaximumWidth(20);
    }

    void setChessBoard()  {
        chessBoard->setMinimumWidth(500);
        mainLayout->addWidget(chessBoard);
    }

    void setSideBar()  {
        mainLayout->addWidget(sideBar);
        sideBar->setMaximumWidth(200);
        sideBar->setMinimumWidth(170);
    }

    void setSystemTrayIcon() {
    }
};

} // namespace Ui

QT_END_NAMESPACE
