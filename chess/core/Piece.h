//
// Created by Uniqu on 2/10/2021.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <vector>
#include <string>
#include <memory>

class Piece {
public:
    bool camp_;
    int role_;
    int pos_;

public:
    Piece(char role, bool camp, int pos);
};


#endif //CHESS_PIECE_H
