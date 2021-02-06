
#include "Engine.h"
#include <cctype>

Piece::Piece(char role, bool camp, int pos) : Camp(camp), Pos(pos) {
    std::vector<char> types = {'k', 'a', 'b', 'n', 'r', 'c', 'p'};
    auto iter = std::find(types.begin(), types.end(), tolower(role));
    if (iter != types.end())
        Role = std::distance(std::begin(types), iter);
    else
        Role = 9;
}


Engine::Engine(int select) : Mode(select) {
    int index = 0;
    for (const auto &item :InitChessBoard) {
        if (!(bool) ispunct(item)) {
            board.emplace_back(item);
            pieces.push_back(std::make_shared<Piece>(item, isupper(item) != 0, index));
            index++;
        }
    }
}

void Engine::chooseMode() {
    switch (Mode) {
        case 0:
            this->chessSelf();
            break;
        case 1:
            this->chessAI();
            break;
        case 2:
            this->chessNet();
            break;
    }
}

void Engine::chessSelf() {}

void Engine::chessAI() {}

void Engine::chessNet() {}


int Engine::checkPos(int &pos) {
    // 如果位置是棋子，下棋方对应
    if (pieces[pos]->Role <9 && pieces[pos]->Camp == currentCamp) {
        // 第一步检查
        if (oldSelect < 0) {
            oldSelect = pos;
            return 2;
        }
        if (pos != oldSelect) {
            // 检查移动策略
            // 如果可以移动
            // return 1
            // 如果不能移动
            // return -1

        }
    }
    return 0;
}



