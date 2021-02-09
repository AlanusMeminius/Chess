#ifndef CHESS_PIECEWIDGET_H
#define CHESS_PIECEWIDGET_H

#include <string>
#include <QWidget>
#include <QPainter>
#include <QtWidgets/QBoxLayout>
#include "../core/Engine.h"

class PieceWidget : public QWidget {
Q_OBJECT
    std::vector<std::string> types = {"将", "士", "象", "马", "车", "炮", "兵"};

public:
    std::shared_ptr<Piece> &logicPiece;

public:
    explicit PieceWidget(std::shared_ptr<Piece> &piece);

    void HighLightPiece();

    void ReverseHighLight();

signals:

    void getPos(int);

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *) override;
};

#endif //CHESS_PIECEWIDGET_H
