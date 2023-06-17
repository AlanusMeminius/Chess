#include <QDebug>

#include "Application.h"
#include "../ui/ChessBoard.h"


Application::Application(Mode mode) 
    : mode_(mode)
    , ui(new Ui::BaseWindow) 
{
    _init_logic_pieces();
    _init_ui_pieces();
    _init_clicked_signal();
    qDebug() << mode_;
}

Application::~Application()
{
    delete ui;
}

void Application::show_window() const
{
    ui->showMainWindow();
}

void Application::_init_logic_pieces() 
{
    /*
     * 根据初始棋盘编码得到逻辑棋子vector
     * */
    int index = 0;
    for (const auto& item : init_chess_board_)
    {
        if (!std::ispunct(item))
        {
            board_.emplace_back(item);
            Camp camp = Camp::White;
            if(item == '0')
            {
                camp = Camp::White;
            }
            else if(std::isupper(item))
            {
                camp = Camp::Black;
            }
            else
            {
                camp = Camp::Red;
            }

            pieces_.push_back(std::make_shared<Piece>(item, camp, index));
            pieces_.back()->set_strategy(StrategyCreator::createStrategy(pieces_.back()->role_));
            index++;
        }
    }
}

void Application::_init_ui_pieces() 
{
    /*
     * 根据逻辑棋子vector，初始化得到界面棋子vector
     * */
    for (auto&& piece : pieces_)
    {
        piece_widgets_.push_back(new Ui::PieceWidget(piece));
        Ui::PieceWidget* p = piece_widgets_.back();
        ui->chessBoard->boardLayout->addWidget(p, piece->pos_ / 9, piece->pos_ % 9);
        if (piece->role_ < PieceRole::None)
        {
            p->load(piece_pic_[piece->camp_][int(piece->role_)]);
        }
            
        connect(p, &Ui::PieceWidget::getPos, this, &Application::piece_click_event);
    }
}

void Application::_init_clicked_signal() 
{
    connect(ui->sideBar->subStartPanel->restoreBtn, &QPushButton::clicked, this, &Application::restore);
    connect(ui->sideBar->subStepHistoryPanel->undoBtn, &QPushButton::clicked, this, &Application::undo);
    connect(step_list, &QListWidget::itemDoubleClicked, this, [&] {
        int count = step_list->count() - step_list->currentRow();
        while (count > 0)
        {
            undo();
            count--;
        }
    });
}

void Application::_check_first_step(int& pos) 
{
    if (_check_role(pos))
    {
        if (_check_camp(pos))
        {
            qDebug() << "first" << pos;
            previous_select_ = pos;
            is_first_step_ = !is_first_step_;
            _highlight(pos);
        }
        else
        {
            ui->sendMsg(tr("现在归对方下棋"));
        }
    }
}

void Application::_check_second_step(int& pos) {
    /*如果第二步选中自己的棋子，更改高亮，重新标记第一步的选择*/
    if (_check_role(pos) && _check_camp(pos))
    {
        qDebug() << "first" << pos;
        /*取消高亮和中心加载高亮*/
        piece_widgets_[previous_select_]->load(piece_pic_[_camp(previous_select_)][int(_role(previous_select_))]);
        _highlight(pos);
        previous_select_ = pos;
        /*如果不是自己的棋子，检测棋子的移动策略*/
    }
    else
    {
        if (_check_strategy(pos))
        {
            _move_pieces(previous_select_, pos);
        }
        else
        {
            ui->sendMsg(tr("不能移动"));
        }
    }
}

bool Application::_check_strategy(int& pos) 
{
    std::shared_ptr<Strategy> strategy = StrategyCreator::createStrategy(_role(previous_select_));
    bool is_movable_ = strategy->is_movable(previous_select_, pos, pieces_);
    return is_movable_;
}

bool Application::_checkmate(const std::vector<std::shared_ptr<Piece>> pieces)
{
    // 找到敌方的将军
    int emleGeneral = 0;
    for(const auto piece : pieces)
    {
        if(piece->camp_ == current_camp_ && piece->role_ == PieceRole::Generals)
        {
            emleGeneral = piece->pos_;
            break;
        }
    }

    // 判断可以将军
    for(const auto piece : pieces)
    {
        if(piece->camp_ != current_camp_ && piece->role_ >= PieceRole::Horses && piece->role_ <= PieceRole::Soldiers)
        {
            if(piece->is_movable(emleGeneral, pieces_))
            {
                return true;
            }
        }
    }

    return false;
}

bool Application::_checkmate(const std::vector<std::shared_ptr<Piece>>& pieces, const int generalPos)
{
    // 判断将军状态
    for(const auto piece : pieces)
    {
        if(piece->camp_ != pieces[generalPos]->camp_ && piece->role_ >= PieceRole::Horses && piece->role_ <= PieceRole::Soldiers)
        {
            if(piece->is_movable(generalPos, pieces_))
            {
                return true;
            }
        }
    }

    return false;
}

bool Application::_checkvictory()
{
    // 获取帅的位置
    int emleGeneral = 0;
    for(const auto piece : pieces_)
    {
        if(piece->camp_ == current_camp_ && piece->role_ == PieceRole::Generals)
        {
            emleGeneral = piece->pos_;
            break;
        }
    }

    for (const auto& piece : pieces_)
    {
        if (piece->camp_ == (!current_camp_) && piece->role_ < PieceRole::None)
        {
            auto possible = piece->_strategy->get_possible_pos(*(piece.get()), pieces_);
            for(const auto& pos : possible)
            {
                auto temp = pieces_;
                _move_piece(temp, piece->pos_, pos);
                
                if(!_checkmate(temp, emleGeneral))
                {
                    return false;
                }
            }
        }
    }
    
    return true;

    // // 是否可以移动帅的位置以达到避免将军
    // auto possibles = pieces_[emleGeneral]->_strategy->get_possible_pos((*pieces_[emleGeneral].get()), pieces_);
    // auto temp = pieces_;
    // for (const auto& possible : possibles)
    // {
    //     // 尝试走一步
    //     temp[possible]->role_ = PieceRole::Generals;
    //     temp[possible]->camp_ = current_camp_;
    //     temp[emleGeneral]->role_ = PieceRole::None;

    //     // 看结果
    //     if(!_checkmate(temp))
    //     {
    //         return false;
    //     }
    // }

    // // 是否可以干掉当前将军的子避免将军
    // // 统计将军的棋子
    // std::vector<int> checkmates;
    // for(const auto piece : pieces_)
    // {
    //     if(piece->camp_ != current_camp_ && piece->role_ >= PieceRole::Horses && piece->role_ <= PieceRole::Soldiers)
    //     {
    //         if(piece->is_movable(emleGeneral, pieces_))
    //         {
    //             checkmates.push_back(piece->pos_);
    //         }
    //     }
    // }

    // // 如果有一个，看是否可以干掉当棋子
    // if(checkmates.size() == 1)
    // {
    //     if(_try_kill_checkmates(checkmates[0]))
    //     {
    //         return false;
    //     }
    // }

    // // 是否可以破环当前将军条件
    // checkmates;
    // for (const auto& checkmate : checkmates)
    // {
    //     switch (pieces_[checkmate]->role_)
    //     {
    //     case PieceRole::Horses:
    //         break;
    //     case PieceRole::Chariots:
    //         break;
    //     case PieceRole::Cannons:
    //         break;
    //     case PieceRole::Soldiers:
    //     break;
    //     default:
    //         break;
    //     }
    //     pieces_[checkmate]->role_ = PieceRole::None;
        
    // }
    
    // return true;
}
bool Application::_move_piece(std::vector<std::shared_ptr<Piece>>& pieces, const int source, const int target)
{
    if(source == target)
    {
        return false;
    }

    pieces[target] = pieces[source];
    pieces[target]->pos_ = target;
    pieces[source] = Piece::whitePieceSharedPtr;
    pieces[source]->pos_ = source;
    return true;
}

void Application::_highlight(int& pos) 
{
    QFile file(piece_pic_[_camp(pos)][int(_role(pos))]);
    file.open(QIODevice::ReadOnly);
    QByteArray byteArray = file.readAll();
    file.close();
    // 读取svg文件为一个QString
    QString string = QString(byteArray);
    // 替换颜色
    string.replace(R"(stroke="#000" fill="#fda")", R"(stroke="#9c8c03" fill="#f5d442")");
    QByteArray h_byteArray = string.toUtf8();
    piece_widgets_[pos]->load(h_byteArray);
}

bool Application::_try_kill_checkmates(int checkmate_pos)
{
    // 判断可以将军
    for(const auto piece : pieces_)
    {
        if(piece->camp_ == current_camp_ && piece->role_ >= PieceRole::Horses && piece->role_ <= PieceRole::Soldiers)
        {
            if(piece->is_movable(checkmate_pos, pieces_))
            {
                return true;
            }
        }
    }

    return false;
}

void Application::_move_pieces(int previous, int current) 
{
    // 反转flag
    _reverse_flag();
    ui->campHint->reverse(bool(current_camp_));
    ui->sideBar->subStartPanel->timeRecord->reverse();

    // 记录棋谱
    Trace trace{{{*(pieces_[previous])}, {*(pieces_[current])}}};
    _step_history(trace);

    // 选中位置加载之前选中的棋子
    piece_widgets_[current]->load(piece_pic_[_camp(previous)][int(_role(previous))]);

    // 变更现在位置逻辑棋子的信息
    _change_info(_camp(previous), _role(previous), current);
    pieces_[current]->_strategy = pieces_[previous]->_strategy;

    // 变更之前位置逻辑棋子的信息, 棋子控件加载空白
    pieces_[previous]->camp_ = Camp::White;
    pieces_[previous]->role_ = PieceRole::None;
    pieces_[previous]->set_strategy(nullptr);
    piece_widgets_[previous]->load(QString(":/blank.svg"));

    if(_checkmate(pieces_))
    {
        is_checkmate_ = true;
        qDebug() << "_checkmate";
        if(_checkvictory())
        {
            qDebug() << "victory";
        }
    }
}

void Application::restore() 
{
    for (int i = 0; i < pieces_.size(); i++)
    {
        // 逻辑棋子使用构造函数更新
        pieces_[i] = std::make_shared<Piece>(board_[i], Camp(isupper(board_[i]) != 0), i);
        piece_widgets_[i]->load((pieces_[i]->role_ < PieceRole::None) ? piece_pic_[_camp(i)][int(_role(i))] : ":/blank.svg");
    }
    // flag 重新初始化
    is_first_step_ = true;
    current_camp_ = Camp::Black;
    step_list->clear();
}

// 第一个字表示需要移动的棋子
// 第二个字表示移动的棋子所在的直线编码(红黑方均为由己方底线从右向左数)，红方用汉字一到九，黑方用阿拉伯数字1到9表示。当同一直线上有两个相同的棋子，则采用前、后来区别。如“后车平四”，“前马进7”
// 第三个字表示棋子移动的方向，横走用”平“，向对方底线前进用”进“，向己方底线后退用”退“。
// 第四个字分为两类：棋子在直线上进退时，表示棋子进退的步数;当棋子平走或斜走的时候，表示所到达直线的编号。

void Application::_step_history(const Trace& trace) 
{
    // 1.自己方阵营同类型棋子是否在同一列 -> 前后
    // 2.移动前后位置是否在同一行 -> 平 进退
    // 3.计算距离算进退
    // 4.解析role piece_character_[camp][role]
    // 5.组装该步走法
    QString former_;
    QString new_;

    // 得到相关信息
    Camp camp = trace[0].camp_;
    int column = trace[0].pos_ % 9;
    int column_distance_ = trace[0].pos_ / 9 - trace[1].pos_ / 9;

    // 先组装前半部分
    QString character = piece_character_[int(camp)][int(trace[0].role_)];
    former_ = character + _number_string[int(camp)][bool(camp) ? (8 - column) : (column)];

    // 查找是否分前后
    for (int k = column; k < 90; k += 9)
    {
        if (k == trace[0].pos_)
            continue;
        
        if (_camp(k) == camp && _role(k) == trace[0].role_)
        {
            if (k < trace[0].pos_)
                former_ = tr("前") + character;
            else
                former_ = tr("后") + character;
            break;
        }
    }

    // 后组装后半部分
    int columnAfter = trace[1].pos_ % 9;
    bool isRow = trace[0].pos_ % 9 - trace[1].pos_ % 9;
    if (column_distance_ != 0)
    {
        new_ = (column_distance_ > 0 ? (bool(camp) ? tr("进") : tr("退")) : (bool(camp) ? tr("退") : tr("进"))) + 
               (isRow == 0 ? _number_string[int(camp)][abs(column_distance_) - 1] : _number_string[int(camp)][bool(camp) ? (8 - columnAfter) : (columnAfter)]);
    }   
    else
    {
        new_ = tr("平") + _number_string[int(camp)][bool(camp) ? (8 - columnAfter) : (columnAfter)];
    }
        
        
    // 加入到走法记录里面
    step_list->addItem(former_ + new_);
    trace_vector_.push_back(trace);
}

void Application::undo() 
{
    if(trace_vector_.empty())
    {
        return ;
    }
    
    Trace last = trace_vector_.back();
    _change_info(_camp(last[1].pos_), last[0].role_, last[0].pos_);
    piece_widgets_[last[0].pos_]->load(piece_pic_[_camp(last[1].pos_)][int(last[0].role_)]);
    piece_widgets_[last[1].pos_]->load(
        (last[1].role_ < PieceRole::None) ? piece_pic_[_camp(last[1].pos_)][int(last[1].role_)] : ":/blank.svg"
    );
    _change_info(!_camp(last[1].pos_), last[1].role_, last[1].pos_);
    _reverse_flag();
    previous_select_ = last[0].pos_;
    ui->campHint->reverse(bool(current_camp_));
    step_list->takeItem(step_list->count() - 1);
    trace_vector_.pop_back();
}
