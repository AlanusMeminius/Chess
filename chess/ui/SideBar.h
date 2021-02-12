
#ifndef CHESS_SIDEBAR_H
#define CHESS_SIDEBAR_H

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

    class SideBar : public QWidget {
        Q_OBJECT

    private:
        QFont boldFont;
    public:
        QVBoxLayout *sideBarMainLayout;
        QHBoxLayout *sideBarLayout;
        QWidget *horizontalSplitLine;
        QLabel *timeRecordLabel;
        QLabel *timeRecord;
        QHBoxLayout *firstBtnLayout;

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
            timeRecord = new CustomLabel(
                    sideBarMainLayout, "timeRecord", "this is time", 30
            );

            // add btn
            firstBtnLayout = new QHBoxLayout;
            firstBtnLayout->setObjectName(QString::fromUtf8("firstBtnLayout"));
            firstBtnLayout->setContentsMargins(10, 10, 10, 10);
            sideBarMainLayout->addLayout(firstBtnLayout);

            std::map<QString, QPushButton *> btnList{
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
            btnList["restoreBtn"]->setText(tr("重置"));

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
            sideBarMainLayout->addWidget(fightHistoryList);

        }

    };

}
QT_END_NAMESPACE

#endif //CHESS_SIDEBAR_H
