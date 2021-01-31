//
// Created by Uniqu on 2/1/2021.
//

#ifndef CHESS_CHESSBOARD_H
#define CHESS_CHESSBOARD_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ChessBoard; }
QT_END_NAMESPACE

class ChessBoard : public QWidget {
Q_OBJECT

public:
    explicit ChessBoard(QWidget *parent = nullptr);

    ~ChessBoard() override;

private:
    Ui::ChessBoard *ui;
};

#endif //CHESS_CHESSBOARD_H
