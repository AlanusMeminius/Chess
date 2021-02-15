#include "Strategy.h"

/*计算横向的距离*/
inline int horizontal_distance(int &a, int &b) { return abs(a / 9 - b / 9); }

/*计算纵向的距离*/
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
        /*如果在横线或者竖线上，而且距离小于2 */
        return is_same_straight_line(previous, current) && linear_distance(previous, current) < 2;
    else
        return false;
}

bool AdvisorsStrategy::is_movable(int &previous, int &current, std::vector<std::shared_ptr<Piece>> &pieces) {
    std::vector possible_vector_ = possible_[pieces[previous]->camp_][previous];
    return std::find(possible_vector_.begin(), possible_vector_.end(), current) != possible_vector_.end();
}

bool BishopsStrategy::is_movable(int &previous, int &current, std::vector<std::shared_ptr<Piece>> &pieces) {
    std::vector possible_vector_ = possible_[pieces[previous]->camp_];
    if (std::find(possible_vector_.begin(), possible_vector_.end(), current) != possible_vector_.end()) {
        /*田字中间是空格*/
        return (pieces[(previous + current) / 2]->role_ > 6);
    } else {
        return false;
    }
}

bool HorsesStrategy::is_movable(int &previous, int &current, std::vector<std::shared_ptr<Piece>> &pieces) {
    /*如果横向距离为1，竖直距离为2*/
    if (horizontal_distance(previous, current) == 1 && vertical_distance(previous, current) == 2) {
        return (previous % 9 > current % 9) ? pieces[previous - 1]->role_ > 6 : pieces[previous + 1]->role_ > 6;
        /*如果横向距离为2，竖直距离为1*/
    } else if (horizontal_distance(previous, current) == 2 && vertical_distance(previous, current) == 1) {
        return (previous / 9 > current / 9) ? pieces[previous - 9]->role_ > 6 : pieces[previous + 9]->role_ > 6;
    } else {
        return false;
    }
}

bool ChariotsStrategy::is_movable(int &previous, int &current, std::vector<std::shared_ptr<Piece>> &pieces) {
    if (is_same_straight_line(previous, current)) {
        for (int i = std::min(previous, current) + 1;
             i < std::max(previous, current); i += (abs(current - previous) < 9) ? 1 : 9) {
            if (pieces[i]->role_ < 7)
                return false;
        }
        return true;
    } else {
        return false;
    }
}

bool CannonsStrategy::is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) {
    return true;
}

bool SoldiersStrategy::is_movable(int &previous, int &current, std::vector<std::shared_ptr<Piece>> &pieces) {
//    if (current / 9)
    return true;
}
