#pragma once
#pragma execution_character_set("utf-8") 

#include <QPainter>
#include <QSvgWidget>
#include <QPainterPath>
#include <QResizeEvent>
#include <QWidget>
#include <QPropertyAnimation>
#include <QtWidgets/QGridLayout>

#include "../core/Piece.h"

QT_BEGIN_NAMESPACE

namespace Ui {
/*
* 行进方阵营标记
* */
class CampHint final : public QWidget {
    Q_OBJECT
public:
    QPropertyAnimation* animation;
    QWidget* hint;

public:
    CampHint();
    void reverse(const bool flag);
};

/*
* 棋子控件，加载棋子图片
* */
class PieceWidget final : public QSvgWidget {
    Q_OBJECT
public:
    std::shared_ptr<Piece> logicPiece;

public:
    explicit PieceWidget(std::shared_ptr<Piece>& piece);
signals:
    void getPos(int);

protected:
    [[maybe_unused]] void mousePressEvent(QMouseEvent*) override;
};

/*
    * 棋盘控件，加载棋盘图片
    * */
class ChessBoardQWidget final : public QSvgWidget {
    Q_OBJECT
public:
    ChessBoardQWidget() { load(QString(":/board.svg")); }
};

/*
* 棋盘主控件，重写resizeEvent，使子控件->棋盘控件保持比例
* */
class ChessBoard final : public QWidget {
Q_OBJECT
private:
    int widthRatio;
    int heightRatio;

public:
    QBoxLayout* layout;
    ChessBoardQWidget* board;
    QGridLayout* boardLayout;

public:
    ChessBoard();
    void resizeEvent(QResizeEvent* event) override;
};

} // namespace Ui

QT_END_NAMESPACE
