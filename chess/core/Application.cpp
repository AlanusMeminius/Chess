#include "Application.h"


Application::Application(int index) : ui(new Ui::BaseWindow), mode_(index) {
//    _init_pieces();
    _init_logic_pieces();
    _init_ui_pieces();
    _init_btn_signal();
    qDebug() << mode_;
}

Application::~Application() {
    delete ui;
}

void Application::show_window() const {
    ui->showMainWindow();
}


void Application::_init_logic_pieces() {
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
}

void Application::_init_ui_pieces() {
    /*
     * 根据逻辑棋子vector，初始化得到界面棋子vector
     * */
    for (auto &piece : pieces_) {
        piece_widgets_.push_back(new Ui::PieceWidget(piece));
        Ui::PieceWidget *p = piece_widgets_.back();
        ui->chessBoard->boardLayout->addWidget(p, piece->pos_ / 9, piece->pos_ % 9);
        if (piece->role_ < 7)
            p->load(piece_pic_[piece->camp_][piece->role_]);
        connect(p, &Ui::PieceWidget::getPos, this, &Application::piece_click_event);
    }
}

void Application::_check_first_step(int &pos) {
    if (_check_role(pos)) {
        if (_check_camp(pos)) {
            qDebug() << "first" << pos;
            previous_select_ = pos;
            is_first_step_ = !is_first_step_;
            _highlight(pos);
        } else {
            ui->sendMsg(tr("现在归对方下棋"));
        }
    }
}

void Application::_check_second_step(int &pos) {
    /*如果第二步选中自己的棋子，更改高亮，重新标记第一步的选择*/
    if (_check_role(pos) && _check_camp(pos)) {
        qDebug() << "first" << pos;
        /*取消高亮和中心加载高亮*/
        piece_widgets_[previous_select_]->load(piece_pic_[_camp(previous_select_)][_role(previous_select_)]);
        _highlight(pos);
        previous_select_ = pos;
        /*如果不是自己的棋子，检测棋子的移动策略*/
    } else {
        if (_check_strategy(pos)) {
            _move_pieces(previous_select_, pos);
        } else {
            ui->sendMsg(tr("不能移动"));
        }
    }
}

bool Application::_check_strategy(int &pos) {
    Strategy *strategy = StrategyCreator::createStrategy(_role(previous_select_));
    bool is_movable_ = strategy->is_movable(previous_select_, pos, pieces_);
    delete strategy;
    return is_movable_;
}

void Application::_highlight(int &pos) {
    QFile file(piece_pic_[_camp(pos)][_role(pos)]);
    file.open(QIODevice::ReadOnly);
    QByteArray byteArray = file.readAll();
    // 读取svg文件为一个Qstring
    QString string = QString(byteArray);
    // 替换颜色
    string.replace(R"(stroke="#000" fill="#fda")", R"(stroke="#9c8c03" fill="#f5d442")");
    QByteArray h_byteArray = string.toUtf8();
    piece_widgets_[pos]->load(h_byteArray);
}

void Application::_move_pieces(int &previous, int &current) {
    // 反转flag
    is_first_step_ = !is_first_step_;
    current_camp_ = !current_camp_;
    ui->campHint->reverse_hint(current_camp_);
    // 选中位置加载之前选中的棋子
    piece_widgets_[current]->load(piece_pic_[_camp(previous)][_role(previous)]);

    // 变更现在位置逻辑棋子的信息
    pieces_[current]->role_ = _role(previous);
    pieces_[current]->camp_ = _camp(previous);

    // 变更之前位置逻辑棋子的信息, 棋子控件加载空白
    pieces_[previous]->role_ = 7;
    piece_widgets_[previous]->load(QString(":/blank.svg"));
}

void Application::_init_btn_signal() {
    connect(ui->sideBar->btnList["restoreBtn"], &QPushButton::clicked, this, &Application::restore_board);

}

void Application::restore_board() {
    for (int i = 0; i < piece_widgets_.size(); i++) {
        pieces_[i] = std::make_shared<Piece>(board_[i], isupper(board_[i]) != 0, i);
        piece_widgets_[i]->logicPiece = pieces_[i];
        if (pieces_[i]->role_ < 7)
            piece_widgets_[i]->load(piece_pic_[pieces_[i]->camp_][pieces_[i]->role_]);
        else
            piece_widgets_[i]->load(QString(":/blank.svg"));
    }
    is_first_step_ = true;
    current_camp_ = true;
}


