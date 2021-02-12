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
        if (piece->role_ < 7)
            p->load(piece_pic_[piece->camp_][piece->role_]);
//            _load_piece_svg(p, piece);
        connect(p, &Ui::PieceWidget::getPos, this, &Application::piece_click_event);
    }
}

void Application::_check_first_step(int &pos) {
    if (_check_role(pos)) {
        if (_check_camp(pos)) {
            qDebug() << pos;
            previous_select_ = pos;
            /*TODO 标记棋子，改变棋子外观*/
            is_first_step_ = !is_first_step_;
        } else {
            ui->sendMsg(tr("现在归对方下棋"));
        }
    }
}

void Application::_check_second_step(int &pos) {
    if (_check_role(pos) && _check_camp(pos)) {
        /*TODO 更改棋子高亮*/
    } else {
        if (_check_strategy(pos)) {
            _move_pieces(previous_select_, pos);
        } else {
            ui->sendMsg(tr("不能移动"));
        }
    }
}

bool Application::_check_strategy(int &pos) {
    Strategy *strategy = StrategyCreator::createStrategy(pieces_[previous_select_]->role_);
    bool is_movable_ = strategy->is_movable(previous_select_, pos, pieces_);
    delete strategy;
    return is_movable_;
}

void Application::_move_pieces(int &previous, int &current) {
    is_first_step_ = !is_first_step_;
    current_camp_ = !current_camp_;

    piece_widgets_[current]->load(piece_pic_[_camp(previous)][_role(previous)]);

    pieces_[current]->role_ = _camp(previous);
    pieces_[current]->camp_ = _role(previous);

    pieces_[previous]->role_ = 7;
    piece_widgets_[previous]->load(QString(":/blank.svg"));
}

