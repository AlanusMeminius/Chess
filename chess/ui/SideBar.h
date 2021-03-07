#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>

#include "Component.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class SideBar : public QWidget {
    Q_OBJECT

    private:
        QFont boldFont;
    public:
        QVBoxLayout* sideBarMainLayout;
        QHBoxLayout* sideBarLayout;
        QWidget* horizontalSplitLine;
        QLabel* timeRecordLabel;
        TimeRecord* timeRecord;
        QHBoxLayout* firstBtnLayout;
        std::map<QString, QPushButton*> btnList;

        QHBoxLayout* secondBtnLayout;
        QWidget* firstVerticalSplitLine;
        CustomLabel* stepHistoryLabel;
        QListWidget* stepHistoryList;
        QPushButton* undoBtn;

        CustomLabel* fightHistoryLabel;
        QWidget* secondVerticalSplitLine;
        QListWidget* fightHistoryList;

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
                {"restoreBtn", new QPushButton}
            };
            for (auto& item : btnList)
            {
                item.second = new QPushButton(item.first);
                item.second->setObjectName(item.first);
                item.second->setMinimumHeight(25);
                firstBtnLayout->addWidget(item.second);
            }
            btnList["startStopBtn"]->setText(tr("开始"));
            connect(btnList["startStopBtn"], &QPushButton::clicked,
                    timeRecord, [=]() {
                        timeRecord->reset();
                        timeRecord->showTimer->start();
                    }, Qt::DirectConnection);
            btnList["restoreBtn"]->setText(tr("重置"));
            connect(btnList["restoreBtn"], &QPushButton::clicked,
                    timeRecord, [=]() {
                        timeRecord->reset();
                        timeRecord->showTimer->stop();
                    }, Qt::DirectConnection);

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

            undoBtn = new QPushButton("悔棋");
            undoBtn->setObjectName("backBtn");
            undoBtn->setMinimumHeight(25);
            secondBtnLayout->addWidget(undoBtn);

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
