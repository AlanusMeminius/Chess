#include "Application.h"


Application::Application(int index) : ui(new Ui::BaseWindow), mode_(index) {
    _init_pieces();
    qDebug() << mode_;
}

Application::~Application() {
    delete ui;
}

void Application::show_window() const {
    ui->showMainWindow();
}

void Application::_init_pieces() {
    /*
     * 根据初始棋盘编码得到逻辑棋子vector
     * */
    int index = 0;
    for (const auto &item : init_chess_board_) {
        if (!ispunct(item)) {
            board_.emplace_back(item);
            pieces_.push_back(std::make_shared<Piece>(item, isupper(item) != 0, index));
            index++;
        }
    }
    /*
     * 根据逻辑棋子vector，初始化得到界面棋子vector
     * */
    for (auto &piece : pieces_) {
        piece_widgets_.push_back(new Ui::PieceWidget(piece));
        Ui::PieceWidget *p = piece_widgets_.back();
        ui->chessBoard->boardLayout->addWidget(p, piece->pos_ / 9, piece->pos_ % 9);
        if (piece->role_ < 9) {
            if (!piece->camp_)
                p->load(black_camp_[piece->role_]);
            else
                p->load(red_camp_[piece->role_]);
        }
    }
}

bool Application::_check_role(int &pos) const {
    return (pieces_[pos]->role_ < 9);
}

bool Application::_check_camp(int &pos) const {
    return (pieces_[pos]->camp_ == current_camp_);
}

