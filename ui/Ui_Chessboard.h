/********************************************************************************
** Form generated from reading UI file 'Chessboard.ui'
**
** Created by: Qt User Interface Compiler version 6.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHESSBOARD_H
#define UI_CHESSBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChessBoard
{
public:
    QLabel *label;

    void setupUi(QWidget *ChessBoard)
    {
        if (ChessBoard->objectName().isEmpty())
            ChessBoard->setObjectName(QString::fromUtf8("ChessBoard"));
        ChessBoard->resize(471, 430);
        label = new QLabel(ChessBoard);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, 120, 311, 91));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);

        retranslateUi(ChessBoard);

        QMetaObject::connectSlotsByName(ChessBoard);
    } // setupUi

    void retranslateUi(QWidget *ChessBoard)
    {
        ChessBoard->setWindowTitle(QCoreApplication::translate("ChessBoard", "ChessBoard", nullptr));
        label->setText(QCoreApplication::translate("ChessBoard", "this is a test", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChessBoard: public Ui_ChessBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHESSBOARD_H
