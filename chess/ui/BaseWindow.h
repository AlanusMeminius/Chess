#pragma once
#pragma execution_character_set("utf-8") 

#include <QFile>
#include <QMainWindow>
#include <QStatusBar>
#include <QSystemTrayIcon>
#include <QtWidgets/QWidget>
#include <QDebug>

#include "ChessBoard.h"
#include "SideBar.h"

QT_BEGIN_NAMESPACE

namespace Ui {

class BaseWindow final : public QMainWindow 
{
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
    void showMainWindow();
    void sendMsg(const QString& msg);
    void setMainStyle();
    void setCampHint();
    void setChessBoard();
    void setSideBar();
    void setSystemTrayIcon();
};

} // namespace Ui

QT_END_NAMESPACE
