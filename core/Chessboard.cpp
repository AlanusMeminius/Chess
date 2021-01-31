//
// Created by Uniqu on 2/1/2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Chessboard.h" resolved

#include "Chessboard.h"
#include "../ui/Ui_Chessboard.h"

ChessBoard::ChessBoard(QWidget *parent) :
        QWidget(parent), ui(new Ui::ChessBoard) {
    ui->setupUi(this);
}

ChessBoard::~ChessBoard() {
    delete ui;
}
