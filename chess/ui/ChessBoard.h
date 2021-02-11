#ifndef CHESS_CHESSBOARD_H
#define CHESS_CHESSBOARD_H

#include <QPainter>
#include <QSvgWidget>
#include <QPainterPath>
#include <QResizeEvent>
#include <QWidget>
#include <QtWidgets/QGridLayout>
#include "../core/Piece.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class PieceWidget : public QSvgWidget {
        Q_OBJECT
    public:
        std::shared_ptr<Piece> logicPiece;

    public:
        explicit PieceWidget(std::shared_ptr<Piece> &piece) : logicPiece(piece) {}

        signals:

                void getPos(int);

    protected:
        void mousePressEvent(QMouseEvent *) { emit getPos(logicPiece->pos_); }
    };

    class ChessBoardQWidget : public QSvgWidget {
        Q_OBJECT
    public:
        ChessBoardQWidget() { load(QString(":/board.svg")); }
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
        ChessBoard() : widthRatio(9), heightRatio(10) {
            layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
            layout->setContentsMargins(0, 0, 0, 0);
            layout->setSpacing(0);
            this->setLayout(layout);
            board = new ChessBoardQWidget;

            layout->addWidget(board);
            boardLayout = new QGridLayout;
            boardLayout->setContentsMargins(0, 0, 0, 0);
            boardLayout->setSpacing(2);
            board->setLayout(boardLayout);
            for (int i = 0; i < 9; ++i) {
                boardLayout->setColumnStretch(i, 1);
                boardLayout->setRowStretch(i, 1);
            }
            boardLayout->setRowStretch(9, 1);
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

}
QT_END_NAMESPACE
#endif // CHESS_CHESSBOARD_H
