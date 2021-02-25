
#ifndef CHESS_SIDEBAR_H
#define CHESS_SIDEBAR_H

#include <QTimer>
#include <QTime>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

namespace Ui {
    class CustomLabel : public QLabel {
    public:
        CustomLabel(
                QVBoxLayout *layout, const QString &objName, const QString &label, const int &minimumHeight) {
            setText(label);
            setObjectName(objName);
            setMinimumHeight(minimumHeight);
            layout->addWidget(this);
        }
    };

    class TimeRecord : public QLabel {
    Q_OBJECT
    public:
        QTime *qTime;
        QTimer *showTimer;
        // 初始化 showTime->start(100)
        // 改变阵营改变 startTime
        // 对局结束 showTime->stop()
        // 一定时间提醒一下 直接在

    public:
        TimeRecord(QObject *parent = nullptr) : qTime(new QTime), showTimer(new QTimer), secs(0), total(0) {
            showTimer->setInterval(100);
            connect(showTimer, &QTimer::timeout, this, [this]() {
                *qTime = QTime::currentTime();
                secs = -(qTime->secsTo(startTime));
                if (secs > 180) {
                    emit timeRemind(secs);
                }
                setText(QString("00:") + QString::number(secs).rightJustified(2, '0'));
            });
        }

    public slots:

        void reverse() {
            total += secs;
            startTime = startTime.currentTime();
        }

        void reset() {
            total = 0;
            secs = 0;
            startTime = startTime.currentTime();
        }

    signals:

        void timeRemind(int secs);

    private:
        int secs;
        int total;
        QTime startTime;

    };

    class SideBar : public QWidget {
    Q_OBJECT

    private:
        QFont boldFont;
    public:
        QVBoxLayout *sideBarMainLayout;
        QHBoxLayout *sideBarLayout;
        QWidget *horizontalSplitLine;
        QLabel *timeRecordLabel;
        TimeRecord *timeRecord;
        QHBoxLayout *firstBtnLayout;
        std::map<QString, QPushButton *> btnList;

        QHBoxLayout *secondBtnLayout;
        QWidget *firstVerticalSplitLine;
        CustomLabel *stepHistoryLabel;
        QListWidget *stepHistoryList;
        QPushButton *backBtn;

        CustomLabel *fightHistoryLabel;
        QWidget *secondVerticalSplitLine;
        QListWidget *fightHistoryList;

    public:
        explicit SideBar() {
            // set main layout
            sideBarLayout = new QHBoxLayout;
            this->setLayout(sideBarLayout);

            // set horizontal split line
            horizontalSplitLine = new QWidget;
            horizontalSplitLine->setObjectName("horizontalSplitLine");
            horizontalSplitLine->setMinimumWidth(2);
            sideBarLayout->addWidget(horizontalSplitLine);
            sideBarLayout->addSpacing(10);

            // set side bar main layout
            sideBarMainLayout = new QVBoxLayout;
            sideBarLayout->addLayout(sideBarMainLayout);

            // add time record label
            timeRecordLabel = new CustomLabel(
                    sideBarMainLayout, "timeRecordLabel", "\u5f00\u59cb\u5bf9\u6218", 30
            );
            timeRecordLabel->setFont(boldFont);

            // add time widget
            timeRecord = new TimeRecord();
            timeRecord->setText("this is a time ");
            timeRecord->setObjectName("TimeRecord");
            sideBarMainLayout->addWidget(timeRecord);
            timeRecord->setAlignment(Qt::AlignCenter);

            // add btn
            firstBtnLayout = new QHBoxLayout;
            firstBtnLayout->setObjectName(QString::fromUtf8("firstBtnLayout"));
            firstBtnLayout->setContentsMargins(10, 10, 10, 10);
            sideBarMainLayout->addLayout(firstBtnLayout);

            btnList = {
                    {"startStopBtn", new QPushButton},
                    {"restoreBtn",   new QPushButton}
            };
            for (auto &item : btnList) {
                item.second = new QPushButton(item.first);
                item.second->setObjectName(item.first);
                item.second->setMinimumHeight(25);
                firstBtnLayout->addWidget(item.second);
            };
            btnList["startStopBtn"]->setText(tr("开始"));
            connect(btnList["startStopBtn"], &QPushButton::clicked,
                    timeRecord, [=]() {
                        timeRecord->reset();
                        timeRecord->showTimer->start();
                    }, Qt::DirectConnection);
            btnList["restoreBtn"]->setText(tr("重置"));
            connect(btnList["restoreBtn"], SIGNAL(clicked()),
                    timeRecord->showTimer, SLOT(stop()), Qt::DirectConnection);

            // add split line
            firstVerticalSplitLine = new QWidget;
            firstVerticalSplitLine->setObjectName("firstVerticalSplitLine");
            firstVerticalSplitLine->setMinimumHeight(2);
            sideBarMainLayout->addWidget(firstVerticalSplitLine);

            stepHistoryLabel = new CustomLabel(
                    sideBarMainLayout, "stepHistoryLabel", "着法记录", 30
            );
            boldFont.setPointSize(10);
            stepHistoryLabel->setFont(boldFont);

            // add step history list
            stepHistoryList = new QListWidget;
            stepHistoryList->setObjectName("stepHistoryList");
            stepHistoryList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            sideBarMainLayout->addWidget(stepHistoryList);

            // add back btn
            secondBtnLayout = new QHBoxLayout;
            secondBtnLayout->setObjectName(QString::fromUtf8("firstBtnLayout"));
            secondBtnLayout->setContentsMargins(10, 10, 10, 10);
            sideBarMainLayout->addLayout(secondBtnLayout);

            backBtn = new QPushButton("悔棋");
            backBtn->setObjectName("backBtn");
            backBtn->setMinimumHeight(25);
            secondBtnLayout->addWidget(backBtn);

            // add split line
            secondVerticalSplitLine = new QWidget;
            secondVerticalSplitLine->setObjectName("secondVerticalSplitLine");
            secondVerticalSplitLine->setMinimumHeight(2);

            sideBarMainLayout->addWidget(secondVerticalSplitLine);
            fightHistoryLabel = new CustomLabel(
                    sideBarMainLayout, "fightHistoryLabel", "对战记录", 30
            );
            fightHistoryLabel->setFont(boldFont);

            // add fight history list
            fightHistoryList = new QListWidget;
            fightHistoryList->setObjectName("fightHistoryList");
            fightHistoryList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            sideBarMainLayout->addWidget(fightHistoryList);

        }

    };

}
QT_END_NAMESPACE

#endif //CHESS_SIDEBAR_H
