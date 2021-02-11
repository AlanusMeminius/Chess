#ifndef CHESS_APPLICATION_H
#define CHESS_APPLICATION_H

#include "../ui/BaseWindow.h"

class Application : public QObject {
    Q_OBJECT
private:
    int mode_;
    const std::string init_chess_board_ = "rnbakabnr/000000000/0c00000c0/p0p0p0p0p/000000000/"
                                          "000000000/P0P0P0P0P/0C00000C0/000000000/RNBAKABNR/";

    bool is_first_step_ = true;
    int previous_select_ = -1;
    bool current_camp_ = true;
private:
    Ui::BaseWindow *ui;

    std::vector<QString> black_camp_ = {":/bk.svg", ":/ba.svg", ":/bb.svg", ":/bn.svg", ":/br.svg", ":/bc.svg",
                                        ":/bp.svg"};
    std::vector<QString> red_camp_ = {":/rk.svg", ":/ra.svg", ":/rb.svg", ":/rn.svg", ":/rr.svg", ":/rc.svg",
                                      ":/rp.svg"};
    std::vector<Ui::PieceWidget *> piece_widgets_;

    std::vector<char> board_;
    std::vector<std::shared_ptr<Piece>> pieces_;

public:
    explicit Application(int index);

    ~Application() override;

    void show_window() const;

private:
    void _init_pieces();

    bool _check_role(int &) const;

    bool _check_camp(int &) const;
};


#endif //CHESS_APPLICATION_H
