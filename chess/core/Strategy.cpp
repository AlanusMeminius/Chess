#include "Strategy.h"

/*计算横向距离*/
inline int horizontal_distance(int &a, int &b) { return abs(a / 9 - b / 9); }

/*计算纵向距离*/
inline int vertical_distance(int &a, int &b) { return abs(a % 9 - b % 9); }

/*检查两个点是否在同一条直线上*/
inline bool is_same_straight_line(int &a, int &b) {
    return (horizontal_distance(a, b) < 1 || vertical_distance(a, b) < 1);
}

/*计算两个点在同一条直线上的距离*/
inline int linear_distance(int &a, int &b) {
    return (horizontal_distance(a, b) > 0) ? horizontal_distance(a, b) : abs(a - b);
}

bool GeneralsStrategy::is_movable(int &previous, int &current, std::vector<std::shared_ptr<Piece>> &pieces) {
    std::vector possible_vector_ = possible_[pieces[previous]->camp_];
    if (std::find(possible_vector_.begin(), possible_vector_.end(), current) != possible_vector_.end())
        return is_same_straight_line(previous, current) && linear_distance(previous, current) < 2;
    else
        return false;
}

bool AdvisorsStrategy::is_movable(int &previous, int &current, std::vector<std::shared_ptr<Piece>> &pieces) {
    std::vector possible_vector_ = possible_[pieces[previous]->camp_][previous];
    return std::find(possible_vector_.begin(), possible_vector_.end(), current) != possible_vector_.end();
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
