#include "Strategy.h"
#include <algorithm>

inline int v_coordinate(int& a) { return a / 9; }

inline int h_coordinate(int& a) { return a % 9; }

/*计算纵向的距离*/
inline int v_distance(int& a, int& b) { return abs(v_coordinate(a) - v_coordinate(b)); }

/*计算横向的距离*/
inline int h_distance(int& a, int& b) { return abs(h_coordinate(a) - h_coordinate(b)); }

/*检查两个点是否在同一条直线上*/
inline bool is_same_straight_line(int& a, int& b) {
    return (v_distance(a, b) < 1 || h_distance(a, b) < 1);
}

/*计算两个点在同一条直线上的距离*/
inline int linear_distance(int& a, int& b) {
    return (v_distance(a, b) > 0) ? v_distance(a, b) : abs(a - b);
}

bool GeneralsStrategy::is_movable(int& previous, int& current, std::vector<std::shared_ptr<Piece>>& pieces) {
    std::vector possible_vector_ = possible_[pieces[previous]->camp_];
    if (std::find(possible_vector_.begin(), possible_vector_.end(), current) != possible_vector_.end())
        /*如果在横线或者竖线上，而且距离小于2 */
        return is_same_straight_line(previous, current) && linear_distance(previous, current) < 2;
    else
        return false;
}

bool AdvisorsStrategy::is_movable(int& previous, int& current, std::vector<std::shared_ptr<Piece>>& pieces) {
    std::vector possible_vector_ = possible_[pieces[previous]->camp_][previous];
    return std::find(possible_vector_.begin(), possible_vector_.end(), current) != possible_vector_.end();
}

bool BishopsStrategy::is_movable(int& previous, int& current, std::vector<std::shared_ptr<Piece>>& pieces) {
    std::vector possible_vector_ = possible_[pieces[previous]->camp_];
    if (std::find(possible_vector_.begin(), possible_vector_.end(), current) != possible_vector_.end())
    {
        /*田字中间是空格*/
        return (pieces[(previous + current) / 2]->role_ > 6);
    }
    else
    {
        return false;
    }
}

bool HorsesStrategy::is_movable(int& previous, int& current, std::vector<std::shared_ptr<Piece>>& pieces) {
    /*如果横向距离为1，竖直距离为2*/
    if (v_distance(previous, current) == 1 && h_distance(previous, current) == 2)
    {
        return (previous % 9 > current % 9) ? pieces[previous - 1]->role_ > 6 : pieces[previous + 1]->role_ > 6;
        /*如果横向距离为2，竖直距离为1*/
    }
    else if (v_distance(previous, current) == 2 && h_distance(previous, current) == 1)
    {
        return (previous / 9 > current / 9) ? pieces[previous - 9]->role_ > 6 : pieces[previous + 9]->role_ > 6;
    }
    else
    {
        return false;
    }
}

bool ChariotsStrategy::is_movable(int& previous, int& current, std::vector<std::shared_ptr<Piece>>& pieces) {
    if (is_same_straight_line(previous, current))
    {
        int distance = abs(current - previous) < 9 ? 1 : 9;
        for (int i = std::min(previous, current) + distance; i < std::max(previous, current); i += distance)
        {
            if (pieces[i]->role_ < 7)
                return false;
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool CannonsStrategy::is_movable(int& previous, int& current, std::vector<std::shared_ptr<Piece>>& pieces) {
    if (is_same_straight_line(previous, current))
    {
        int distance = abs(current - previous) < 9 ? 1 : 9;
        int count = 0;
        for (int i = std::min(previous, current) + distance; i < std::max(previous, current); i += distance)
        {
            if (pieces[i]->role_ < 7)
                count++;
        }
        if (pieces[current]->role_ < 7 && pieces[current]->camp_ != pieces[previous]->camp_)
            return count == 1;
        return count == 0;
    }
    else
    {
        return false;
    }
}

bool SoldiersStrategy::is_movable(int& previous, int& current, std::vector<std::shared_ptr<Piece>>& pieces) {
    if (pieces[previous]->camp_ ? (previous / 9) > 4 : (previous / 9) < 5)
        return current - previous == (pieces[previous]->camp_ ? -9 : 9);
    else if (v_distance(previous, current) < 1)
        return h_distance(previous, current) == 1;
    else if (h_distance(previous, current) < 1)
        return v_coordinate(previous) - v_coordinate(current) == (pieces[previous]->camp_ ? 1 : -1);
    else
        return false;
}
