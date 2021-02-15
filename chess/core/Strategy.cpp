#include "Strategy.h"

/*
 * 检查两个点是否在同一条直线上*/
inline bool is_same_straight_line(int &a, int &b) {
    return a / 9 == b / 9 || a % 9 == b % 9;
}

/*计算两个点在同一条直线上的距离*/
inline int linear_distance(int &a, int &b) {
    return (a / 9 != b / 9) ? abs(a / 9 - b / 9) : abs(a - b);
}

bool GeneralsStrategy::is_movable(int &previous, int &current, std::vector<std::shared_ptr<Piece>> &pieces) {
    if (current / 9 < 3 && 2 < current % 9 && current % 9 < 6)
        return false;
    else {
        if (is_same_straight_line(previous, current)) {
            if (linear_distance(previous, current) < 2)
                return true;
        }
    }
}

bool AdvisorsStrategy::is_movable(int &previous, int &current, std::vector<std::shared_ptr<Piece>> &pieces) {
    std::vector possoble_vector_ = possible_[pieces[previous]->camp_][previous];
    return std::find(possoble_vector_.begin(), possoble_vector_.end(), current) != possoble_vector_.end();
}

bool BishopsStrategy::is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &pieces) {
    return true;
}

bool HorsesStrategy::is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) {
    return true;
}

bool ChariotsStrategy::is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) {
    return true;
}


bool CannonsStrategy::is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) {
    return true;
}

bool SoldiersStrategy::is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) {
    return true;
}
