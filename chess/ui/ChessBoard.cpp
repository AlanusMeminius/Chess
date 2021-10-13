#pragma execution_character_set("utf-8") 

#include "ChessBoard.h"
/*
* 行进方阵营标记
* */
Ui::CampHint::CampHint() 
{
    hint = new QWidget(this);
    hint->setGeometry(QRect(0, height(), 3, 200));
    hint->setObjectName("Hint");

    animation = new QPropertyAnimation;
    animation->setPropertyName(QByteArray("geometry")); // 这里是？
    animation->setDuration(400);
    animation->setTargetObject(hint);
}

void Ui::CampHint::reverse(const bool flag) 
{
    if (flag)
    {
        animation->setStartValue(QRect(0, height() / 2 - 200, 3, 200));
        animation->setEndValue(QRect(0, height() / 2, 3, 200));
        animation->start();
    }
    else
    {
        animation->setStartValue(QRect(0, height() / 2, 3, 200));
        animation->setEndValue(QRect(0, height() / 2 - 200, 3, 200));
        animation->start();
    }
}



Ui::PieceWidget::PieceWidget(std::shared_ptr<Piece>& piece) 
    : logicPiece(piece)
{
}

void Ui::PieceWidget::mousePressEvent(QMouseEvent* event) 
{
    emit getPos(logicPiece->pos_);
    return QSvgWidget::mousePressEvent(event);
}


Ui::ChessBoard::ChessBoard() 
    : widthRatio(9)
    , heightRatio(10) 
{
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
    for (int i = 0; i < 9; ++i)
    {
        boardLayout->setColumnStretch(i, 1);
        boardLayout->setRowStretch(i, 1);
    }
    boardLayout->setRowStretch(9, 1);
}

void Ui::ChessBoard::resizeEvent(QResizeEvent* event) 
{
    const QSize oldSize = event->size();
    QSize newSize = event->size();

    if (newSize.width() < widthRatio * newSize.height() / heightRatio)
    {
        newSize.setHeight(heightRatio * newSize.width() / widthRatio);
        board->move(0, (oldSize.height() - newSize.height()) / 2);
    }
    else
    {
        newSize.setWidth(widthRatio * newSize.height() / heightRatio);
        board->move((oldSize.width() - newSize.width()) / 2, 0);
    }
    
    board->resize(newSize);
}