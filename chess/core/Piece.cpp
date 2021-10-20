//
// Created by Uniqu on 2/10/2021.
//
#pragma execution_character_set("utf-8") 

#include "Piece.h"
#include <algorithm>

const std::array<char, 7> Piece::_roleChar{ 'k', 'a', 'b', 'n', 'r', 'c', 'p' };

Piece::Piece (char role, Camp camp, int pos) 
    : camp_(camp)
    , pos_(pos) 
{
    /*
     * 将初始化棋盘编码字母所代表的类型转化为int和类型
     * */
    const auto iter = std::find(_roleChar.begin (), _roleChar.end (), tolower(role));

    if (iter != _roleChar.end ())
    {
        auto role_index = std::distance(std::begin(_roleChar), iter); // NOLINT(clang-diagnostic-shorten-64-to-32)
        role_ = PieceRole(role_index);
    }  
    else
    {
        role_ = PieceRole::None;
    }
        
}