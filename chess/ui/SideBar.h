#pragma once
#pragma execution_character_set("utf-8") 

#include <QLabel>
#include <QTime>
#include <QTimer>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>

namespace SideBarComponent 
{

class CustomLabel final : public QLabel 
{
    Q_OBJECT
public:
    CustomLabel(QVBoxLayout* layout, const QString& objName, const QString& label, const int& minimumHeight) {
        setText(label);
        setObjectName(objName);
        setMinimumHeight(minimumHeight);
        layout->addWidget(this);
    }
};

class TimeRecord final : public QLabel 
{
    Q_OBJECT
public:
    QTime* qTime;
    QTimer* showTimer;

public:
    explicit TimeRecord(QObject* object= nullptr);
    void reverse();
    void reset();

signals:
    void timeRemind(int secs);

private:
    int secs;
    int total;
    QTime startTime;

private:
    QString _set_text(int& secs_);
};

class SubStartPanel final : public QWidget 
{
    Q_OBJECT
public:
    QFont boldFont;
    QVBoxLayout* layout;
    QLabel* timeRecordLabel;
    TimeRecord* timeRecord;
    QHBoxLayout* firstBtnLayout;
    QPushButton* startStopBtn;
    QWidget* btnSplitLine;
    QPushButton* restoreBtn;
public:
    SubStartPanel();
};

class SubStepHistoryPanel final : public QWidget 
{
    Q_OBJECT
public:
    QFont boldFont;
    QVBoxLayout* layout;
    CustomLabel* label;
    QListWidget* list;
    QPushButton* undoBtn;
public:
    SubStepHistoryPanel();
};

class SubFightHistoryPanel final : public QWidget 
{
    Q_OBJECT
public:
    QFont boldFont;
    QVBoxLayout* layout;
    CustomLabel* label;
    QListWidget* list;
public:
    SubFightHistoryPanel();
};

class SettingWidget final : public QWidget 
{
    Q_OBJECT
public:
    QVBoxLayout* mainLayout;
    QLabel* trayIconLabel;
    QGroupBox* iconGroupBox;
    QComboBox* iconComboBox;
    QCheckBox* showIconCheckBox;
    QHBoxLayout* iconLayout;
public:
    SettingWidget();
};

class SubSettingPanel final : public QWidget 
{
    Q_OBJECT
public:
    QVBoxLayout* settingPanelLayout;
    QPushButton* settingBtn;
    SettingWidget* settingWidget;
public:
    SubSettingPanel();
    void isToggled(bool isHide);
    
protected:
    void resizeEvent(QResizeEvent* event) override;

signals:
    void setOtherHide(bool);
};

} // namespace SideBarComponent

QT_BEGIN_NAMESPACE

namespace Ui {

class SideBar final : public QWidget 
{
    Q_OBJECT
public:
    QVBoxLayout* sideBarLayout;
public:
    QWidget* startPanel;
    QVBoxLayout* startPanelLayout;
    SideBarComponent::SubStartPanel* subStartPanel;

public:
    QWidget* stepHistoryPanel;
    QVBoxLayout* stepHistoryPanelLayout;
    SideBarComponent::SubStepHistoryPanel* subStepHistoryPanel;
public:
    QWidget* fightHistoryPanel;
    QVBoxLayout* fightHistoryPanelLayout;
    SideBarComponent::SubFightHistoryPanel* subFightHistoryPanel;
public:
    QWidget* settingPanel;
    QVBoxLayout* settingPanelLayout;
    SideBarComponent::SubSettingPanel* subSettingPanel;

public:
    SideBar();
};

} // namespace Ui

QT_END_NAMESPACE
