//
// Created by Uniqu on 1/31/2021.
//

#ifndef CHESS_MAINWINDOW_H
#define CHESS_MAINWINDOW_H

#include <QMainWindow>
#include "Chessboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT
private:
    int Mode;
public:
    explicit MainWindow(int index, QWidget *parent = nullptr);

    ~MainWindow() override;

    void chooseMode() const;

    void chessSelf() const;

    void chessAI() const;

    void chessNet() const;

private:
    Ui::MainWindow *ui;
    ChessBoard *chessBoard;
};

#endif //CHESS_MAINWINDOW_H
