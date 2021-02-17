#ifndef CHESS_APPLICATION_H
#define CHESS_APPLICATION_H

#include <QFile>
#include "Strategy.h"
#include "../ui/BaseWindow.h"

class Application : public QObject {
Q_OBJECT
private:
    const std::string init_chess_board_ = "rnbakabnr/000000000/0c00000c0/p0p0p0p0p/000000000/"
                                          "000000000/P0P0P0P0P/0C00000C0/000000000/RNBAKABNR/";
    std::map<bool, std::vector<QString>> piece_pic_{
            {false, {":/bk.svg", ":/ba.svg", ":/bb.svg", ":/bn.svg", ":/br.svg", ":/bc.svg", ":/bp.svg"}},
            {true,  {":/rk.svg", ":/ra.svg", ":/rb.svg", ":/rn.svg", ":/rr.svg", ":/rc.svg", ":/rp.svg"}},
    };
    [[maybe_unused]] std::map<bool, std::vector<QString>> piece_character_{
            {false, {"將", "士", "象", "馬", "車", "砲", "卒", "空白"}},
            {true,  {"帥", "仕", "相", "傌", "俥", "炮", "兵", "空白"}}
    };

private:
    int mode_;
    bool is_first_step_ = true;
    int previous_select_ = -1;
    bool current_camp_ = true;

private:
    Ui::BaseWindow *ui;
    std::vector<char> board_;
    std::vector<std::shared_ptr<Piece>> pieces_;
    std::vector<Ui::PieceWidget *> piece_widgets_;

private slots:

    void piece_click_event(int pos) {
        (is_first_step_) ? _check_first_step(pos) : _check_second_step(pos);
    }

    void restore_board();

public:

    explicit Application(int index);

    ~Application() override;

    void show_window() const;

private:

    /*
     * 帮助函数，重用
     * */
    inline bool _check_role(int &pos) const { return (_role(pos) < 7); }

    inline bool _check_camp(int &pos) const { return (_camp(pos) == current_camp_); }

    inline bool _camp(int &pos) const { return pieces_[pos]->camp_; }

    inline int _role(int &pos) const { return pieces_[pos]->role_; }

private:

    /*初始化*/
    void _init_logic_pieces();

    void _init_ui_pieces();

    void _init_btn_signal();

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
};


#endif //CHESS_APPLICATION_H
