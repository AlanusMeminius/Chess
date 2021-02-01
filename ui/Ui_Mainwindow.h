/********************************************************************************
** Form generated from reading UI file 'Naubwubdiw.ui'
**
** Created by: Qt User Interface Compiler version 6.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *ChessBoardWidget;
    QFrame *line;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *start_stop_btn;
    QPushButton *restore_btn;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(980, 900);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        ChessBoardWidget = new QWidget(centralwidget);
        ChessBoardWidget->setObjectName(QString::fromUtf8("ChessBoardWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ChessBoardWidget->sizePolicy().hasHeightForWidth());
        ChessBoardWidget->setSizePolicy(sizePolicy);
        ChessBoardWidget->setMinimumSize(QSize(750, 780));

        verticalLayout_2->addWidget(ChessBoardWidget);


        horizontalLayout_2->addLayout(verticalLayout_2);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setWindowModality(Qt::NonModal);
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setSizeIncrement(QSize(0, 0));
        line->setLineWidth(3);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 30));
        QFont font;
        font.setPointSize(13);
        font.setBold(true);
        label->setFont(font);
        label->setMargin(9);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 40));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(10, 10, 10, 10);
        start_stop_btn = new QPushButton(centralwidget);
        start_stop_btn->setObjectName(QString::fromUtf8("start_stop_btn"));
        start_stop_btn->setMinimumSize(QSize(50, 25));
        start_stop_btn->setStyleSheet(QString::fromUtf8("background-color: #5E81AC;\n"
                                                        "border: none;\n"
                                                        "border-radius:4px;\n"
                                                        "color: #E5E9F0;"));

        horizontalLayout_3->addWidget(start_stop_btn);

        restore_btn = new QPushButton(centralwidget);
        restore_btn->setObjectName(QString::fromUtf8("restore_btn"));
        restore_btn->setMinimumSize(QSize(50, 25));
        restore_btn->setStyleSheet(QString::fromUtf8("background-color: #5E81AC;\n"
                                                     "border: none;\n"
                                                     "border-radius:4px;\n"
                                                     "color: #E5E9F0;"));

        horizontalLayout_3->addWidget(restore_btn);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);


        horizontalLayout->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\257\271\346\210\230\350\256\241\346\227\266", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        start_stop_btn->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        restore_btn->setText(QCoreApplication::translate("MainWindow", "\351\207\215\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_H
