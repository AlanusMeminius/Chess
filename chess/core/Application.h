#ifndef CHESS_APPLICATION_H
#define CHESS_APPLICATION_H
#pragma once
#pragma execution_character_set("utf-8")
 
#include <QFile>
#include <iostream>
#include <tuple>
#include <QListWidgetItem>
#include "Strategy.h"
#include "../ui/BaseWindow.h"
#include "Piece.h"

class Application : public QObject {
    Q_OBJECT
private:
    const std::string init_chess_board_ = "rnbakabnr/000000000/0c00000c0/p0p0p0p0p/000000000/"
                                          "000000000/P0P0P0P0P/0C00000C0/000000000/RNBAKABNR/";
    std::map<Camp, std::vector<QString>> piece_pic_{
            {Camp::Red, {":/bk.svg", ":/ba.svg", ":/bb.svg", ":/bn.svg", ":/br.svg", ":/bc.svg", ":/bp.svg"}},
            {Camp::Black,  {":/rk.svg", ":/ra.svg", ":/rb.svg", ":/rn.svg", ":/rr.svg", ":/rc.svg", ":/rp.svg"}},
    };
    [[maybe_unused]] std::array<std::array<QString, 7>, 2> piece_character_{
            "將", "士", "象", "馬", "車", "砲", "卒",
            "帥", "仕", "相", "傌", "俥", "炮", "兵",
    };

    [[maybe_unused]] std::array<std::array<QString, 9>, 2> _number_string{
            "1", "2", "3", "4", "5", "6", "7", "8", "9",
            "一", "二", "三", "四", "五", "六", "七", "八", "九"
    };
    
    typedef std::array<TraceUnit, 2> Trace;
    std::vector<Trace> trace_vector_;
    std::vector<QString> kifu_vector_;

private:
    int mode_;
    bool is_first_step_ = true;
    int previous_select_ = -1;
    Camp current_camp_ = Camp::Black;

private:
    Ui::BaseWindow* ui;
    std::vector<char> board_;
    std::vector<std::shared_ptr<Piece>> pieces_;
    std::vector<Ui::PieceWidget*> piece_widgets_;
    QListWidget*& step_list = ui->sideBar->subStepHistoryPanel->list; // 初始化顺序未定义

public:
    explicit Application(int index);

    ~Application() override;

    void show_window() const;

    void piece_click_event(int pos) {
        (is_first_step_) ? _check_first_step(pos) : _check_second_step(pos);
    }

    void restore();

    void undo();

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

    inline void _change_nfo(const Camp& camp, const PieceRole& role, const int& pos) {
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

    /*
     * ui界面改变
     * */
    void _highlight(int &);

    void _move_pieces(int &, int &);

    /* 行进历史记录
     * */
    void _step_history(const Trace &);
};


#endif //CHESS_APPLICATION_H