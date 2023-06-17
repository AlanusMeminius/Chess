#pragma once
#include <iostream>
#include <tuple>

#include <QListWidgetItem>
#include <QFile>

#include "Strategy.h"
#include "../ui/BaseWindow.h"
#include "Piece.h"

class Application : public QObject 
{
    Q_OBJECT
public:
    enum Mode {
        SigleMode,
        NetworkMode, 
        AiExercise
    };

    enum TipsMode {
        Newer,
        Older
    };

    explicit Application(Mode mode);

    ~Application() override;

    void show_window() const;

    void piece_click_event(int pos) {
        (is_first_step_) ? _check_first_step(pos) : _check_second_step(pos);
    }

    void restore();

    void undo();

private:
    const std::string init_chess_board_ = "rnbakabnr/000000000/0c00000c0/p0p0p0p0p/000000000/"
                                          "000000000/P0P0P0P0P/0C00000C0/000000000/RNBAKABNR/";
    std::map<Camp, std::vector<QString>> piece_pic_{
            {Camp::Red, {":/bk.svg", ":/ba.svg", ":/bb.svg", ":/bn.svg", ":/br.svg", ":/bc.svg", ":/bp.svg"}},
            {Camp::Black,  {":/rk.svg", ":/ra.svg", ":/rb.svg", ":/rn.svg", ":/rr.svg", ":/rc.svg", ":/rp.svg"}},
    };

    [[maybe_unused]] std::array<std::array<QString, 7>, 2> piece_character_{
            {"將", "士", "象", "馬", "車", "砲", "卒",},
            {"帥", "仕", "相", "傌", "俥", "炮", "兵",},
    };

    [[maybe_unused]] std::array<std::array<QString, 9>, 2> _number_string{
            {"1", "2", "3", "4", "5", "6", "7", "8", "9",},
            {"一", "二", "三", "四", "五", "六", "七", "八", "九",},
    };
    
    typedef std::array<TraceUnit, 2> Trace;
    std::vector<Trace> trace_vector_;
    std::vector<QString> kifu_vector_;

private:
    Mode mode_;                                                       // 对战模式
    bool is_first_step_ = true;                                       // 是否是第一步
    int previous_select_ = -1;                                        // 前一步选中
    Camp current_camp_ = Camp::Black;                                 // 当前行走方
    bool is_checkmate_ = false;                                       // 当前是否处于将军状态

private:
    Ui::BaseWindow* ui;                                               // ui界面
    std::vector<char> board_;                                         // 初始化字符
    std::vector<std::shared_ptr<Piece>> pieces_;                      // 逻辑棋子数组
    std::vector<Ui::PieceWidget*> piece_widgets_;                     // 界面棋子
    QListWidget*& step_list = ui->sideBar->subStepHistoryPanel->list; // 初始化顺序未定义

private:

    /*
     * 帮助函数，重用
     * */
    inline bool _check_role(int &pos) const { return (_role(pos) < PieceRole::None); }

    inline bool _check_camp(int &pos) const { return (_camp(pos) == current_camp_); }

    [[nodiscard]] inline Camp _camp(const int &pos) const { return pieces_[pos]->camp_; }

    [[nodiscard]] inline PieceRole _role(const int &pos) const { return pieces_[pos]->role_; }

    inline void _reverse_flag() {
        is_first_step_ = !is_first_step_;
        current_camp_ = !current_camp_;
    }

    inline void _change_info(const Camp& camp, const PieceRole& role, const int& pos) {
        pieces_[pos]->camp_ = camp;
        pieces_[pos]->role_ = role;
    }

    /*初始化*/
    void _init_logic_pieces();

    void _init_ui_pieces();

    void _init_clicked_signal();

    /*
     * 下棋逻辑判断
     * */
    void _check_first_step(int &);

    void _check_second_step(int &);

    bool _check_strategy(int &);
    
    bool _checkmate(const std::vector<std::shared_ptr<Piece>> pieces);
    bool _checkmate(const std::vector<std::shared_ptr<Piece>>& pieces, const int generalPos);

    bool _checkvictory();
    bool _move_piece(std::vector<std::shared_ptr<Piece>>& pieces, const int source, const int target);

    bool _try_kill_checkmates(int checkmate_pos);

    /*
     * ui界面改变
     * */
    void _highlight(int &);

    void _move_pieces(int , int );

    /* 行进历史记录
     * */
    void _step_history(const Trace &);
};
