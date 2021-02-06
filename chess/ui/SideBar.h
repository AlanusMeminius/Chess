
#ifndef CHESS_SIDEBAR_H
#define CHESS_SIDEBAR_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>

class VerticalSplitLine : public QWidget {
public:
    explicit VerticalSplitLine(QVBoxLayout *layout, const QString &objName) {
        setMinimumHeight(2);
        setObjectName(objName);
        layout->addWidget(this);
    }
};

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

class BoldFont : public QFont {
public:
    BoldFont() {
        this->setPixelSize(13);
        this->setBold(true);
    }
};

class SideBar : public QWidget {
Q_OBJECT

private:
    BoldFont boldFont;
public:
    QVBoxLayout *sideBarMainLayout;
    QHBoxLayout *sideBarLayout;
    QWidget *horizontalSplitLine;
    QLabel *timeRecordLabel;
    QLabel *timeRecord;
    QHBoxLayout *firstBtnLayout;
    QPushButton *restoreBtn;
    QPushButton *startStopBtn;

    QHBoxLayout *secondBtnLayout;
    VerticalSplitLine *firstVerticalSplitLine;
    CustomLabel *stepHistoryLabel;
    QListWidget *stepHistoryList;
    QPushButton *backBtn;

    CustomLabel *fightHistoryLabel;
    VerticalSplitLine *secondVerticalSplitLine;
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
                sideBarMainLayout, "timeRecordLabel", "对战计时", 30
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
                {"startStopBtn", startStopBtn},
                {"restoreBtn",   restoreBtn}
        };
        for (auto &item : btnList) {
            item.second = new QPushButton(item.first);
            item.second->setObjectName(item.first);
            item.second->setMinimumHeight(25);
            firstBtnLayout->addWidget(item.second);
        };
        btnList["startStopBtn"]->setText("开始");
        btnList["restoreBtn"]->setText("重置");

        // add split line
        firstVerticalSplitLine = new VerticalSplitLine(sideBarMainLayout, "firstVerticalSplitLine");
        stepHistoryLabel = new CustomLabel(
                sideBarMainLayout, "stepHistoryLabel", "着法记录", 30
        );
        stepHistoryLabel->setFont(boldFont);

        // add step history list
        stepHistoryList = new QListWidget;
        stepHistoryList->setObjectName("stepHistoryList");
        sideBarMainLayout->addWidget(stepHistoryList);

        // add btn
        secondBtnLayout = new QHBoxLayout;
        secondBtnLayout->setObjectName(QString::fromUtf8("firstBtnLayout"));
        secondBtnLayout->setContentsMargins(10, 10, 10, 10);
        sideBarMainLayout->addLayout(secondBtnLayout);

        backBtn = new QPushButton;
        backBtn->setObjectName("backBtn");
        backBtn->setText("悔棋");
        backBtn->setMinimumHeight(25);
        secondBtnLayout->addWidget(backBtn);

        // add split line
        secondVerticalSplitLine = new VerticalSplitLine(sideBarMainLayout, "secondVerticalSplitLine");
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

#endif //CHESS_SIDEBAR_H
