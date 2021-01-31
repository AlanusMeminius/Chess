//
// Created by Uniqu on 1/31/2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "Mainwindow.h"
#include "../ui/Ui_Mainwindow.h"

MainWindow::MainWindow(int index, QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow), Mode(index) {
    ui->setupUi(this);

    chessBoard = new ChessBoard(ui->ChessBoardWidget);
    chooseMode();
}

MainWindow::~MainWindow() {
    delete ui;
    delete chessBoard;
}


void MainWindow::chooseMode() const {
    switch (Mode) {
        case 0:
            this->chessSelf();
            break;
        case 1:
            this->chessAI();
            break;
        case 2:
            this->chessNet();
            break;
    }
}

void MainWindow::chessSelf() const {

}

void MainWindow::chessAI() const {

}

void MainWindow::chessNet() const {

}
