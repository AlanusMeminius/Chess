
#ifndef CHESS_CHESSBOARD_H
#define CHESS_CHESSBOARD_H

#include <QWidget>
#include <QResizeEvent>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QGridLayout>


class ChessBoard : public QWidget {
Q_OBJECT
private:
    int widthRatio;
    int heightRatio;
public:
    QBoxLayout *layout;
    QWidget *board;
    QGridLayout *boardLayout;

public:
    ChessBoard() : widthRatio(8), heightRatio(9) {
        layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
        this->setLayout(layout);
        board = new QWidget(this);

        board->setStyleSheet("background-color:#D8DEE9;");
        layout->addWidget(board);
        boardLayout = new QGridLayout;
        board->setLayout(boardLayout);
//        this->setLayout(boardLayout);
    }

    void resizeEvent(QResizeEvent *event) override {
        QSize oldSize = event->size();
        QSize newSize = event->size();

        if (newSize.width() < widthRatio * newSize.height() / heightRatio) {
            newSize.setHeight(heightRatio * newSize.width() / widthRatio);
            board->move(0, (oldSize.height() - newSize.height()) / 2);
        } else {
            newSize.setWidth(widthRatio * newSize.height() / heightRatio);
            board->move((oldSize.width() - newSize.width()) / 2, 0);
        }
        board->resize(newSize);
    }

};

#endif //CHESS_CHESSBOARD_H
