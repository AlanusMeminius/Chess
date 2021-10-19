#pragma execution_character_set("utf-8") 

#include "SideBar.h"

SideBarComponent::TimeRecord::TimeRecord(QObject* object) 
    : qTime(new QTime)
    , showTimer(new QTimer)
    , secs(0)
    , total(0)
{
    showTimer->setInterval(100);
    connect(showTimer, &QTimer::timeout, this, [&]() {
        *qTime = QTime::currentTime();
        secs = -(qTime->secsTo(startTime));
        if (secs > 180)
        {
            emit timeRemind(secs);
        }
        _set_text(secs);
    });
}

void SideBarComponent::TimeRecord::reverse() 
{
    total += secs;
    startTime = QTime::currentTime();
}

void SideBarComponent::TimeRecord::reset() 
{
    total = 0;
    secs = 0;
    _set_text(secs);
    startTime = QTime::currentTime();
}

QString SideBarComponent::TimeRecord::_set_text(int& secs_) 
{
    // max 100 minutes
    if (secs_ > 6000)
    {
        secs_ = secs_ - 6000;
    }

    const int t_sec = secs_ % 60;
    const int t_min = secs_ / 60;

    QString result = tr("%1:%2").arg(t_min, 2, 10, QChar('0')).arg(t_sec, 2, 10, QChar('0'));
    setText(result);
    return result;
}

/*******
 * 
 * **********/
SideBarComponent::SubStartPanel::SubStartPanel() 
{
    boldFont.setBold(true);
    boldFont.setPointSize(10);
    layout = new QVBoxLayout;
    setLayout(layout);

    // add time record label
    timeRecordLabel = new CustomLabel(
        layout, "timeRecordLabel", "开始对战", 30
    );

    timeRecordLabel->setFont(boldFont);

    // add time widget
    timeRecord = new TimeRecord;
    timeRecord->setText("00:00");
    QFont timeFont;
    timeFont.setBold(true);
    timeFont.setPointSize(18);
    timeRecord->setFont(timeFont);
    timeRecord->setObjectName("TimeRecord");
    layout->addWidget(timeRecord);
    timeRecord->setAlignment(Qt::AlignCenter);

    firstBtnLayout = new QHBoxLayout;
    firstBtnLayout->setObjectName(QString::fromUtf8("firstBtnLayout"));
    firstBtnLayout->setContentsMargins(10, 10, 10, 10);
    firstBtnLayout->setSpacing(0);
    layout->addLayout(firstBtnLayout);

    restoreBtn = new QPushButton;
    restoreBtn->setObjectName("restoreBtn");
    restoreBtn->setText(tr("重置"));
    restoreBtn->setMinimumHeight(25);
    firstBtnLayout->addWidget(restoreBtn);

    connect(restoreBtn, &QPushButton::click, timeRecord, [=]() {
        timeRecord->reset();
        timeRecord->showTimer->stop();
    }, Qt::DirectConnection);

    btnSplitLine = new QWidget;
    firstBtnLayout->addWidget(btnSplitLine);
    btnSplitLine->setMaximumWidth(2);
    btnSplitLine->setObjectName("btnSplitLine");

    startStopBtn = new QPushButton;
    startStopBtn->setObjectName("startStopBtn");
    startStopBtn->setText(tr("开始"));
    startStopBtn->setMinimumHeight(25);
    firstBtnLayout->addWidget(startStopBtn);
    connect(startStopBtn, &QPushButton::clicked, timeRecord, [&]() {
        timeRecord->reset();
        timeRecord->showTimer->start();
    }, Qt::DirectConnection);
}

/*******
 * 
 * **********/
SideBarComponent::SubStepHistoryPanel::SubStepHistoryPanel() 
{
    boldFont.setBold(true);
    boldFont.setPointSize(10);
    layout = new QVBoxLayout;
    setLayout(layout);

    label = new CustomLabel(layout, "stepHistoryLabel", "着法记录", 30);
    boldFont.setPointSize(10);
    label->setFont(boldFont);

    list = new QListWidget;
    list->setObjectName("stepHistoryList");
    list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    layout->addWidget(list);

    undoBtn = new QPushButton("悔棋");
    undoBtn->setObjectName("undoBtn");
    undoBtn->setMinimumHeight(25);
    layout->addWidget(undoBtn);
}

/*******
 * 
 * **********/
SideBarComponent::SubFightHistoryPanel::SubFightHistoryPanel() 
{
    boldFont.setBold(true);
    boldFont.setPointSize(10);
    layout = new QVBoxLayout;
    setLayout(layout);
    label = new CustomLabel(
        layout, "fightHistoryLabel", "对战记录", 30
    );
    label->setFont(boldFont);

    list = new QListWidget;
    list->setObjectName("fightHistoryList");
    list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    layout->addWidget(list);
}

/*******
 * 
 * **********/
SideBarComponent::SettingWidget::SettingWidget()
{
    iconGroupBox = new QGroupBox(tr("Tray Icon"));
    trayIconLabel = new QLabel(tr("Icon:"));

    iconComboBox = new QComboBox;
    iconComboBox->addItem("test1");
    iconComboBox->addItem("test2");

    showIconCheckBox = new QCheckBox(tr("Show Icon"));
    showIconCheckBox->setCheckable(true);

    iconLayout = new QHBoxLayout;
    iconLayout->addWidget(trayIconLabel);
    iconLayout->addWidget(iconComboBox);
    iconLayout->addStretch();
    iconLayout->addWidget(showIconCheckBox);
    iconGroupBox->setLayout(iconLayout);

    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    mainLayout->addWidget(iconGroupBox);
}

/*******
 * 
 * **********/
SideBarComponent::SubSettingPanel::SubSettingPanel()
{
    settingPanelLayout = new QVBoxLayout;
    setLayout(settingPanelLayout);
    settingBtn = new QPushButton(tr("setting"));
    settingBtn->setCheckable(true);
    settingPanelLayout->addWidget(settingBtn);

    settingWidget = new SettingWidget;
    settingPanelLayout->addWidget(settingWidget);
    settingWidget->hide();
    connect(settingBtn, &QPushButton::toggled, this, &SubSettingPanel::isToggled, Qt::DirectConnection);
}

void SideBarComponent::SubSettingPanel::resizeEvent(QResizeEvent* event) 
{
    settingWidget->setBaseSize(QSize(width(), height()));
}

void SideBarComponent::SubSettingPanel::isToggled(bool isHide) 
{
    settingWidget->setHidden(isHide);
    emit setOtherHide(isHide);
}

/*******
 * 
 * **********/
Ui::SideBar::SideBar() 
{
    sideBarLayout = new QVBoxLayout;
    this->setLayout(sideBarLayout);

    startPanel = new QWidget;
    sideBarLayout->addWidget(startPanel);
    startPanel->setObjectName("StartPanel");
    startPanelLayout = new QVBoxLayout;
    startPanel->setLayout(startPanelLayout);
    subStartPanel = new SideBarComponent::SubStartPanel;
    startPanelLayout->addWidget(subStartPanel);

    stepHistoryPanel = new QWidget;
    sideBarLayout->addWidget(stepHistoryPanel);
    stepHistoryPanel->setObjectName("stepHistoryPanel");
    stepHistoryPanelLayout = new QVBoxLayout;
    stepHistoryPanel->setLayout(stepHistoryPanelLayout);
    subStepHistoryPanel = new SideBarComponent::SubStepHistoryPanel;
    stepHistoryPanelLayout->addWidget(subStepHistoryPanel);

    fightHistoryPanel = new QWidget;
    sideBarLayout->addWidget(fightHistoryPanel);
    fightHistoryPanel->setObjectName("fightHistoryPanel");
    fightHistoryPanelLayout = new QVBoxLayout;
    fightHistoryPanel->setLayout(fightHistoryPanelLayout);
    subFightHistoryPanel = new SideBarComponent::SubFightHistoryPanel;
    fightHistoryPanelLayout->addWidget(subFightHistoryPanel);

    settingPanel = new QWidget;
    settingPanel->setObjectName("settingPanel");
    sideBarLayout->addWidget(settingPanel);
    settingPanelLayout = new QVBoxLayout;
    settingPanel->setLayout(settingPanelLayout);
    subSettingPanel = new SideBarComponent::SubSettingPanel;
    settingPanelLayout->addWidget(subSettingPanel);

    connect(
        subSettingPanel, &SideBarComponent::SubSettingPanel::setOtherHide,
        fightHistoryPanel, &QWidget::setHidden, Qt::DirectConnection
    );
}