#include "Application.h"


Application::Application(int index) : ui(new Ui::BaseWindow), mode_(index) {
    _init_logic_pieces();
    _init_ui_pieces();
    _init_clicked_signal();
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

void Application::_init_clicked_signal() {
    connect(ui->sideBar->btnList["restoreBtn"], &QPushButton::clicked, this, &Application::restore);
    connect(ui->sideBar->undoBtn, &QPushButton::clicked, this, &Application::undo);
    connect(step_list, &QListWidget::itemDoubleClicked, this, [this] {
        int cout = step_list->count() - step_list->currentRow();
        while (cout > 0) {
            undo();
            cout--;
        }
    });
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
    // 读取svg文件为一个QString
    QString string = QString(byteArray);
    // 替换颜色
    string.replace(R"(stroke="#000" fill="#fda")", R"(stroke="#9c8c03" fill="#f5d442")");
    QByteArray h_byteArray = string.toUtf8();
    piece_widgets_[pos]->load(h_byteArray);
}

void Application::_move_pieces(int &previous, int &current) {
    // 反转flag
    _reverse_flag();
    ui->campHint->reverse(current_camp_);
    ui->sideBar->timeRecord->reverse();

    Trace trace{previous, _role(previous), current, _role(current)};
    _step_history(trace);

    // 选中位置加载之前选中的棋子
    piece_widgets_[current]->load(piece_pic_[_camp(previous)][_role(previous)]);

    // 变更现在位置逻辑棋子的信息
    _change_nfo(_camp(previous), _role(previous), current);

    // 变更之前位置逻辑棋子的信息, 棋子控件加载空白
    pieces_[previous]->role_ = 7;
    piece_widgets_[previous]->load(QString(":/blank.svg"));
}

void Application::restore() {
    for (int i = 0; i < pieces_.size(); i++) {
        // 逻辑棋子使用构造函数更新
        pieces_[i] = std::make_shared<Piece>(board_[i], isupper(board_[i]) != 0, i);
        piece_widgets_[i]->load((pieces_[i]->role_ < 7) ? piece_pic_[_camp(i)][_role(i)] : ":/blank.svg");
    }
    // flag 重新初始化
    is_first_step_ = true;
    current_camp_ = true;
    step_list->clear();
}

void Application::_step_history(const Trace &trace) {
    // 1.自己方阵营同类型棋子是否在同一列 -> 前后
    // 2.移动前后位置是否在同一行 -> 平 进退
    // 3.计算距离算进退
    // 4.解析role piece_character_[camp][role]
    // 5.组装该步走法
    QString former_;
    QString new_;

    bool camp = _camp(trace[0]);
    int colume = trace[0] % 9;
    int column_distance_ = trace[0] / 9 - trace[2] / 9;

    for (int k = colume; k < 90; k += 9) {
        if (k == trace[0])
            continue;
        QString character = piece_character_[camp][trace[1]];
        if (_camp(k) == camp && _role(k) == trace[1]) {
            if (k < trace[0])
                former_ = tr("前") + character;
            else
                former_ = tr("后") + character;
        } else {
            former_ = character + _number_string[camp][camp ? (8 - colume) : (colume)];
        }
    }

    if (column_distance_ != 0)
        new_ = (column_distance_ > 0 ? (camp ? tr("进") : tr("退")) : (camp ? tr("退") : tr("进")))
               + _number_string[camp][abs(column_distance_) - 1];
    else
        new_ = tr("平") + _number_string[camp][camp ? (10 - colume) : (colume)];
    step_list->addItem(former_ + new_);
    trace_vector_.push_back(trace);
}

void Application::undo() {
    Trace last = trace_vector_.back();
    _change_nfo(_camp(last[2]), last[1], last[0]);
    piece_widgets_[last[0]]->load(piece_pic_[_camp(last[2])][last[1]]);
    piece_widgets_[last[2]]->load(
            (last[3] < 7) ? piece_pic_[_camp(last[2])][last[2]] : ":/blank.svg"
    );
    _change_nfo(!_camp(last[2]), last[3], last[2]);
    _reverse_flag();
    previous_select_ = last[0];
    ui->campHint->reverse(current_camp_);
    step_list->takeItem(step_list->count() - 1);
    trace_vector_.pop_back();
}