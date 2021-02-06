/********************************************************************************
** Form generated from reading UI file 'SplashScreen.ui'
**
** Created by: Qt User Interface Compiler version 6.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPLASHSCREEN_H
#define UI_SPLASHSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SplashScreen
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QLabel *label;
    QLabel *label_2;
    QLabel *loading_label;
    QLabel *label_4;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *mode1;
    QPushButton *mode2;
    QPushButton *mode3;
    QProgressBar *progressBar;

    void setupUi(QDialog *SplashScreen)
    {
        if (SplashScreen->objectName().isEmpty())
            SplashScreen->setObjectName(QString::fromUtf8("SplashScreen"));
        SplashScreen->resize(680, 400);
        SplashScreen->setMaximumSize(QSize(680, 400));
        verticalLayout = new QVBoxLayout(SplashScreen);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(SplashScreen);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8("color: rgb(255, 249, 247);\n"
"background-color: #4C566A;\n"
"border-radius:10px;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(-3, 50, 661, 61));
        QFont title_font;
        title_font.setPointSize(40);
        label->setFont(title_font);
        label->setAlignment(Qt::AlignCenter);

        QFont font;
        font.setPointSize(10);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 110, 281, 61));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);
        loading_label = new QLabel(frame);
        loading_label->setObjectName(QString::fromUtf8("loading_label"));
        loading_label->setGeometry(QRect(0, 330, 661, 21));
        loading_label->setFont(font);
        loading_label->setAlignment(Qt::AlignCenter);
        loading_label->setText("WELCOME");
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 350, 641, 21));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);
        horizontalLayoutWidget = new QWidget(frame);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(100, 160, 461, 91));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        mode1 = new QPushButton(horizontalLayoutWidget);
        mode1->setObjectName(QString::fromUtf8("mode1"));
        mode1->setMaximumSize(QSize(100, 40));
        mode1->setStyleSheet(QString::fromUtf8("color: #E5E9F0;\n"
"background-color: #5E81AC;\n"
"border: none;\n"
"border-radius:7px;"));

        horizontalLayout->addWidget(mode1);

        mode2 = new QPushButton(horizontalLayoutWidget);
        mode2->setObjectName(QString::fromUtf8("mode2"));
        mode2->setMaximumSize(QSize(100, 40));
        mode2->setStyleSheet(QString::fromUtf8("color: #E5E9F0;\n"
"background-color: #5E81AC;\n"
"border: none;\n"
"border-radius:7px;"));

        horizontalLayout->addWidget(mode2);

        mode3 = new QPushButton(horizontalLayoutWidget);
        mode3->setObjectName(QString::fromUtf8("mode3"));
        mode3->setMaximumSize(QSize(100, 40));
        mode3->setStyleSheet(QString::fromUtf8("color: #E5E9F0;\n"
"background-color: #5E81AC;\n"
"border: none;\n"
"border-radius:7px;"));

        horizontalLayout->addWidget(mode3);

        progressBar = new QProgressBar(frame);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(60, 300, 531, 23));
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"background-color: #434C5E;\n"
"color: #D8DEE9;\n"
"border-style: none;\n"
"border-radius:10px;\n"
"text-align:center;\n"
"}\n"
"QProgressBar::chunk {\n"
"border-radius:10px;\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0.369, x2:1, y2:0.727, stop:0 rgba(0, 135, 202, 255), stop:1 rgba(67, 92, 255, 255));\n"
"}"));
        progressBar->setValue(24);

        verticalLayout->addWidget(frame);


        retranslateUi(SplashScreen);

        QMetaObject::connectSlotsByName(SplashScreen);
    } // setupUi

    void retranslateUi(QDialog *SplashScreen)
    {
        SplashScreen->setWindowTitle(QCoreApplication::translate("SplashScreen", "SplashScreen", nullptr));
        label->setText(QCoreApplication::translate("SplashScreen", "\344\270\255\345\233\275<strong>\350\261\241\346\243\213</strong>", nullptr));
        label_2->setText(QCoreApplication::translate("SplashScreen", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700;\">\351\200\211\346\213\251\346\250\241\345\274\217\357\274\232</span></p></body></html>", nullptr));
        loading_label->setText(QCoreApplication::translate("SplashScreen", "<html><head/><body><p><span style=\" font-size:10pt;\">loading..</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("SplashScreen", "<html><head/><body><p align=\"right\"><span style=\" font-size:10pt;\">Created: Luke</span></p></body></html>", nullptr));
        mode1->setText(QCoreApplication::translate("SplashScreen", "\344\270\216\350\207\252\345\267\261\345\257\271\346\210\230", nullptr));
        mode2->setText(QCoreApplication::translate("SplashScreen", "\344\270\216AI\345\257\271\346\210\230", nullptr));
        mode3->setText(QCoreApplication::translate("SplashScreen", "\347\275\221\347\273\234\345\257\271\346\210\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SplashScreen: public Ui_SplashScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPLASHSCREEN_H
