#pragma once
#pragma execution_character_set("utf-8") 

#include <QtWidgets/QDialog>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>
#include <QtCore>
#include <QTimer>
#include <QObject>

#include "../core/Application.h"

QT_BEGIN_NAMESPACE

namespace Ui {

class StartUpWindow : public QDialog 
{
    Q_OBJECT
public:
    int counter_{ 0 };
public:
    QVBoxLayout* verticalLayout;
    QFrame* frame;
    QLabel* titleLabel;
    QWidget* horizontalLayoutWidget;
    QHBoxLayout* horizontalLayout;
    std::map<std::pair<int, QString>, QPushButton*> modeList;
    QProgressBar* progressBar; // 进度条                       
    QLabel* loadingLabel;
    //        QLabel *createdLabel;
    QTimer* timer;
public:
    StartUpWindow();
    void setUI();
    void btnClicked();
    void progress();
};

} // namespace Ui

QT_END_NAMESPACE

class SetUp : public QObject 
{
    Q_OBJECT
public:
    SetUp();
    ~SetUp();
    void setUpMainWindow(int select);

public:
    Ui::StartUpWindow *startUpWindow;
    Application *application;

signals:
    void btnIndex(int);
};
