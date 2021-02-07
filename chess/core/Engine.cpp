
#include "Engine.h"
#include <cctype>

Piece::Piece(char role, bool camp, int pos) : camp_(camp), pos_(pos) {
    std::vector<char> types = {'k', 'a', 'b', 'n', 'r', 'c', 'p'};
    auto iter = std::find(types.begin(), types.end(), tolower(role));
    if (iter != types.end())
        role_ = std::distance(std::begin(types), iter);
    else
        role_ = 9;
}


Engine::Engine(int select) : Mode(select) {
    int index = 0;
    for (const auto &item :initChessBoard) {
        if (!(bool) ispunct(item)) {
            board_.emplace_back(item);
            pieces_.push_back(std::make_shared<Piece>(item, isupper(item) != 0, index));
            index++;
        }
    }
}

void Engine::choose_mode() {
    switch (Mode) {
        case 0:
            this->_chess_self();
            break;
        case 1:
            this->_chess_AI();
            break;
        case 2:
            this->_chess_Net();
            break;
    }
}

void Engine::_chess_self() {}

void Engine::_chess_AI() {}

void Engine::_chess_Net() {}


int Engine::check_pos(int &pos) {
    // 如果位置是棋子，下棋方对应
    if (pieces_[pos]->role_ <9 && pieces_[pos]->camp_ == current_camp_) {
        // 第一步检查
        if (old_select_< 0) {
            old_select_ = pos;
            return 2;
        }
        if (pos != old_select_) {
            // 检查移动策略
            // 如果可以移动
            // return 1
            // 如果不能移动
            // return -1

        }
    }
    return 0;
}



