#ifndef CHESS_CHESSBOARD_H
#define CHESS_CHESSBOARD_H

#include <QPainterPath>
#include <QResizeEvent>
#include <QWidget>
#include <QtWidgets/QGridLayout>

#include "PieceWidget.h"

class ChessBoardQWidget : public QWidget {
Q_OBJECT
    std::vector<std::pair<int, QString>> HanPos = {{37, "楚"},
                                                   {38, "河"},
                                                   {41, "汉"},
                                                   {42, "界"}};

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);

        painter.setRenderHints(QPainter::Antialiasing |
                               QPainter::SmoothPixmapTransform);

        const QList<PieceWidget *> PieceList = this->findChildren<PieceWidget *>();

        const QPoint halfHeightWidth(PieceList[0]->width() / 2,
                                     PieceList[0]->width() / 2);

        // 画横线
        for (int i = 0; i < 10; i++)
            painter.drawLine(PieceList[i * 9]->pos() + halfHeightWidth,
                             PieceList[i * 9 + 8]->pos() + halfHeightWidth);
        // 画竖线
        for (int j = 0; j < 9; j++) {
            // 画两边的长竖线
            if (j == 0 || j == 8)
                painter.drawLine(PieceList[j]->pos() + halfHeightWidth, PieceList[j + 81]->pos() + halfHeightWidth);
                // 画中间的短竖线
            else {
                painter.drawLine(PieceList[j]->pos() + halfHeightWidth, PieceList[36 + j]->pos() + halfHeightWidth);
                painter.drawLine(
                        PieceList[45 + j]->pos() + halfHeightWidth, PieceList[81 + j]->pos() + halfHeightWidth);
            }
        }
        painter.setFont(QFont("Microsoft YaHei", 25, 60, false));
        for (auto &item: HanPos) {
            painter.drawText(
                    QRect(
                            PieceList[item.first]->pos() + halfHeightWidth,
                            PieceList[item.first + 10]->pos() + halfHeightWidth
                    ),
                    Qt::AlignCenter, item.second
            );
        }
        painter.end();
    }
};

class ChessBoard : public QWidget {
Q_OBJECT
private:
    int widthRatio;
    int heightRatio;

public:
    QBoxLayout *layout;
    ChessBoardQWidget *board;
    QGridLayout *boardLayout;

public:
    ChessBoard() : widthRatio(8), heightRatio(9) {
        layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
        this->setLayout(layout);
        board = new ChessBoardQWidget;

        layout->addWidget(board);
        boardLayout = new QGridLayout;
        boardLayout->setContentsMargins(0, 0, 0, 0);
        boardLayout->setSpacing(0);
        board->setLayout(boardLayout);
    }

    void resizeEvent(QResizeEvent *event) override {
        const QSize oldSize = event->size();
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

#endif  // CHESS_CHESSBOARD_H
