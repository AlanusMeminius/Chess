//
// Created by Uniqu on 2/10/2021.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#pragma once
#pragma execution_character_set("utf-8") 

#include <vector>
#include <string>
#include <memory>

enum class PieceRole {
    Generals,     // 将
    Advisors,     // 士
    Bishops,      // 象
    Horses,       // 马
    Chariots,     // 车
    Cannons,      // 炮
    Soldiers,     // 兵
};

enum class Camp {
    Red,
    Blue,
};

class Piece {
public:
    bool camp_;
    int role_;
    int pos_;

public:
    Piece(char role, bool camp, int pos);
};

#endif //CHESS_PIECE_H
