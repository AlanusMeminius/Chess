//
// Created by Uniqu on 2/10/2021.
//

#include "Piece.h"

Piece::Piece(char role, bool camp, int pos) : camp_(camp), pos_(pos) {
    /*
     * 将初始化棋盘编码字母所代表的类型转化为int和类型
     * */
    std::vector<char> types = {'k', 'a', 'b', 'n', 'r', 'c', 'p'};
    const auto iter = std::find(types.begin(), types.end(), tolower(role));
    if (iter != types.end())
        role_ = std::distance(std::begin(types), iter); // NOLINT(clang-diagnostic-shorten-64-to-32)
    else
        role_ = 7;
}