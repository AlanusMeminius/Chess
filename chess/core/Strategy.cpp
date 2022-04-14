#pragma execution_character_set("utf-8") 

#include "Strategy.h"
#include <algorithm>
namespace {

inline int v_coordinate(int a) { return a / 9; }

inline int h_coordinate(int a) { return a % 9; }

/*计算纵向的距离*/
inline int v_distance(int a, int b) { return abs(v_coordinate(a) - v_coordinate(b)); }

/*计算横向的距离*/
inline int h_distance(int a, int b) { return abs(h_coordinate(a) - h_coordinate(b)); }

/*检查两个点是否在同一条直线上*/
inline bool is_same_straight_line(int a, int b) 
{
    return (v_distance(a, b) < 1 || h_distance(a, b) < 1);
}

/*计算两个点在同一条直线上的距离*/
inline int linear_distance(int a, int b) 
{
    return (v_distance(a, b) > 0) ? v_distance(a, b) : abs(a - b);
}

inline int point_to_pos(int row, int col) { return row*9 + col; }

} // 匿名空间

std::map<Camp, std::vector<int>> GeneralsStrategy::possible_{
        {Camp::Red,  {3,  4,  5,  12, 13, 14, 21, 22, 23}},
        {Camp::Black, {66, 67, 68, 75, 76, 78, 84, 85, 86}}
};

bool GeneralsStrategy::is_movable(int& previous, int& current, const std::vector<std::shared_ptr<Piece>>& pieces) 
{
    std::vector possible_vector_ = possible_[pieces[previous]->camp_];
    if (std::find(possible_vector_.begin(), possible_vector_.end(), current) != possible_vector_.end())
        /*如果在横线或者竖线上，而且距离小于2 */
        return is_same_straight_line(previous, current) && linear_distance(previous, current) < 2;
    else
        return false;
}

std::vector<int> GeneralsStrategy::get_possible_pos(const Piece& piece, const std::vector<std::shared_ptr<Piece>>& pieces) 
{
    if(piece.role_ == PieceRole::None)
    {
        return {};
    }

    std::vector possible_vector = possible_[piece.camp_];
    for (auto iter = possible_vector.begin(); iter < possible_vector.end(); ++iter)
    {
        if(pieces[(*iter)]->camp_ == piece.camp_)
        {
            possible_vector.erase(iter);
            iter--;
        }

        if(!(is_same_straight_line(piece.pos_, *iter) && linear_distance(piece.pos_, *iter) < 2))
        {
            possible_vector.erase(iter);
            iter--;
        }
    }
    
    return possible_vector;
}

std::map<Camp, std::map<int, std::vector<int>>> AdvisorsStrategy::possible_{
    {Camp::Red, {
                    {3,  {13}},
                    {5,  {13}},
                    {13, {3,  5,  21, 23}},
                    {21, {13}},
                    {23, {13}}
                },
    },
    {Camp::Black,   {
                        {66, {76}},
                        {68, {76}},
                        {76, {66, 68, 84, 86}},
                        {84, {76}},
                        {86, {76}}
                    },
    }
};

bool AdvisorsStrategy::is_movable(int& previous, int& current, const std::vector<std::shared_ptr<Piece>>& pieces) 
{
    std::vector possible_vector_ = possible_[pieces[previous]->camp_][previous];
    return std::find(possible_vector_.begin(), possible_vector_.end(), current) != possible_vector_.end();
}

std::vector<int> AdvisorsStrategy::get_possible_pos(const Piece& piece, const std::vector<std::shared_ptr<Piece>>& pieces) 
{
    if(piece.role_ == PieceRole::None)
    {
        return {};
    }

    std::vector possible_vector = possible_[piece.camp_][piece.pos_];
    for (auto iter = possible_vector.begin(); iter < possible_vector.end(); ++iter)
    {
        if(pieces[(*iter)]->camp_ == piece.camp_)
        {
            possible_vector.erase(iter);
            iter--;
        }
    }

    return possible_vector;
}

std::map<Camp, std::map<int, std::vector<int>>> BishopsStrategy::possible_{
            {Camp::Red, {
                    {2, {18, 22}},
                    {6, {22, 26}},
                    {18, {2, 38}},
                    {22, {2, 5, 38, 42}},
                    {26, {6, 42}},
                    {38, {18, 22}},
                    {42, {22, 26}},
                },
            },
            {Camp::Black, {
                    {47, {63, 67}},
                    {51, {67, 71}},
                    {63, {47, 83}},
                    {67, {47, 51, 83, 87}},
                    {71, {51, 87}},
                    {83, {63, 67}},
                    {87, {67, 71}},
                },
            },
};

bool BishopsStrategy::is_movable(int& previous, int& current, const std::vector<std::shared_ptr<Piece>>& pieces) 
{
    std::vector possible_vector_ = possible_[pieces[previous]->camp_][pieces[previous]->pos_];
    if (std::find(possible_vector_.begin(), possible_vector_.end(), current) != possible_vector_.end())
    {
        /*田字中间是空格*/
        return (pieces[(previous + current) / 2]->role_ == PieceRole::None);
    }
    else
    {
        return false;
    }
}

std::vector<int> BishopsStrategy::get_possible_pos(const Piece& piece, const std::vector<std::shared_ptr<Piece>>& pieces) 
{
    if(piece.role_ == PieceRole::None)
    {
        return {};
    }

    std::vector possible_vector = possible_[piece.camp_][piece.pos_];
    for (auto iter = possible_vector.begin(); iter < possible_vector.end(); ++iter)
    {
        if(pieces[(*iter)]->camp_ == piece.camp_)
        {
            possible_vector.erase(iter);
            iter--;
        }

        if(pieces[(piece.pos_ + (*iter)) / 2]->role_ != PieceRole::None)
        {
            possible_vector.erase(iter);
            iter--;
        }
    }
    return possible_vector;
}

bool HorsesStrategy::is_movable(int& previous, int& current, const std::vector<std::shared_ptr<Piece>>& pieces) 
{
    /*如果横向距离为1，竖直距离为2*/
    if (v_distance(previous, current) == 1 && h_distance(previous, current) == 2)
    {
        return (previous % 9 > current % 9) ? pieces[previous - 1]->role_ >= PieceRole::None : pieces[previous + 1]->role_ >= PieceRole::None;
        /*如果横向距离为2，竖直距离为1*/
    }
    else if (v_distance(previous, current) == 2 && h_distance(previous, current) == 1)
    {
        return (previous / 9 > current / 9) ? pieces[previous - 9]->role_ >= PieceRole::None : pieces[previous + 9]->role_ >= PieceRole::None;
    }
    else
    {
        return false;
    }
}

std::vector<int> HorsesStrategy::get_possible_pos(const Piece& piece, const std::vector<std::shared_ptr<Piece>>& pieces) 
{
    if(piece.role_ == PieceRole::None)
    {
        return {};
    }

    std::vector<int> possible_vector;
    int col = piece.pos_ % 9;
    int row = piece.pos_ / 9;

    if(col + 1 <= 8)
    {
        if(row + 2 <= 9)
        {
            possible_vector.emplace_back(point_to_pos(row + 2, col + 1));
        }

        if(row - 2 >= 0)
        {
            possible_vector.emplace_back(point_to_pos(row - 2, col + 1));
        }

        if(col + 2 <= 8)
        {
            if(row + 1 <= 9)
            {
                possible_vector.emplace_back(point_to_pos(row + 1, col + 2));
            }

            if(row - 1 >= 0)
            {
                possible_vector.emplace_back(point_to_pos(row - 1, col + 2));
            }
        }
    }
    else if (col - 1 > 0)
    {
        if(row + 2 <= 9)
        {
            possible_vector.emplace_back(point_to_pos(row + 2, col - 1));
        }

        if(row - 2 >= 0)
        {
            possible_vector.emplace_back(point_to_pos(row - 2, col - 1));
        }

        if(col - 2 >= 0)
        {
            if(row + 1 <= 9)
            {
                possible_vector.emplace_back(point_to_pos(row + 1, col - 2));
            }

            if(row - 1 >= 0)
            {
                possible_vector.emplace_back(point_to_pos(row - 1, col - 2));
            }
        }
    }
    
    for (auto iter = possible_vector.begin(); iter < possible_vector.end(); ++iter)
    {
        if(pieces[(*iter)]->camp_ == piece.camp_)
        {
            possible_vector.erase(iter);
            iter--;
        }

        int pos = piece.pos_;
        if(!is_movable(pos, *iter, pieces))
        {
            possible_vector.erase(iter);
            iter--;
        }
    }

    return possible_vector;
}

bool ChariotsStrategy::is_movable(int& previous, int& current, const std::vector<std::shared_ptr<Piece>>& pieces) 
{
    if (is_same_straight_line(previous, current))
    {
        int distance = abs(current - previous) < 9 ? 1 : 9;
        for (int i = std::min(previous, current) + distance; i < std::max(previous, current); i += distance)
        {
            if (pieces[i]->role_ < PieceRole::None)
                return false;
        }
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<int> ChariotsStrategy::get_possible_pos(const Piece& piece, const std::vector<std::shared_ptr<Piece>>& pieces) 
{
    if(piece.role_ == PieceRole::None)
    {
        return {};
    }

    std::vector<int> possible_vector;
    int col = piece.pos_ % 9;
    int row = piece.pos_ / 9;

    for(int ccol = col + 1; ccol <= 9; ++ccol)
    {
        if(pieces[point_to_pos(row, ccol)]->role_ == PieceRole::None)
        {
            possible_vector.emplace_back(point_to_pos(row, ccol));
        }

        if(pieces[point_to_pos(row, ccol)]->role_ != PieceRole::None)
        {
            if(pieces[point_to_pos(row, ccol)]->camp_ == !(piece.camp_))
            {
                possible_vector.emplace_back(point_to_pos(row, ccol));
            }
            break;
        }
    }

    for(int ccol = col - 1; ccol >= 0; --ccol)
    {
        if(pieces[point_to_pos(row, ccol)]->role_ == PieceRole::None)
        {
            possible_vector.emplace_back(point_to_pos(row, ccol));
        }

        if(pieces[point_to_pos(row, ccol)]->role_ != PieceRole::None)
        {
            if(pieces[point_to_pos(row, ccol)]->camp_ == !(piece.camp_))
            {
                possible_vector.emplace_back(point_to_pos(row, ccol));
            }
            break;
        }
    }

    for(int crow = row + 1; crow <= 10; ++crow)
    {
        if(pieces[point_to_pos(crow, col)]->role_ == PieceRole::None)
        {
            possible_vector.emplace_back(point_to_pos(crow, col));
        }

        if(pieces[point_to_pos(crow, col)]->role_ != PieceRole::None)
        {
            if(pieces[point_to_pos(crow, col)]->camp_ == !(piece.camp_))
            {
                possible_vector.emplace_back(point_to_pos(crow, col));
            }
            break;
        }
    }

    for(int crow = row - 1; crow >= 0; --crow)
    {
        if(pieces[point_to_pos(crow, col)]->role_ == PieceRole::None)
        {
            possible_vector.emplace_back(point_to_pos(crow, col));
        }

        if(pieces[point_to_pos(crow, col)]->role_ != PieceRole::None)
        {
            if(pieces[point_to_pos(crow, col)]->camp_ == !(piece.camp_))
            {
                possible_vector.emplace_back(point_to_pos(crow, col));
            }
            break;
        }
    }

    return possible_vector;
}

bool CannonsStrategy::is_movable(int& previous, int& current, const std::vector<std::shared_ptr<Piece>>& pieces) 
{
    if (is_same_straight_line(previous, current))
    {
        int distance = abs(current - previous) < 9 ? 1 : 9;
        int count = 0;
        for (int i = std::min(previous, current) + distance; i < std::max(previous, current); i += distance)
        {
            if (pieces[i]->role_ < PieceRole::None)
                count++;
        }
        if (pieces[current]->role_ < PieceRole::None && pieces[current]->camp_ != pieces[previous]->camp_)
            return count == 1;
        return count == 0;
    }
    else
    {
        return false;
    }
}

std::vector<int> CannonsStrategy::get_possible_pos(const Piece& piece, const std::vector<std::shared_ptr<Piece>>& pieces) 
{
    if(piece.role_ == PieceRole::None)
    {
        return {};
    }

    std::vector<int> possible_vector;

    int col = piece.pos_ % 9;
    int row = piece.pos_ / 9;

    for(int ccol = col + 1; ccol <= 9; ++ccol)
    {
        if(pieces[point_to_pos(row, ccol)]->role_ == PieceRole::None)
        {
            possible_vector.emplace_back(point_to_pos(row, ccol));
        }

        if(pieces[point_to_pos(row, ccol)]->role_ != PieceRole::None)
        {
            for(int pccol = ccol + 1; pccol <= 9; ++pccol)
            {
                if(pieces[point_to_pos(row, pccol)]->role_ != PieceRole::None && 
                   pieces[point_to_pos(row, pccol)]->camp_ != !(piece.camp_))
                {
                    possible_vector.emplace_back(point_to_pos(row, pccol));
                    break;
                }
            }
            break;
        }
    }

    for(int ccol = col - 1; ccol >= 0; --ccol)
    {
        if(pieces[point_to_pos(row, ccol)]->role_ == PieceRole::None)
        {
            possible_vector.emplace_back(point_to_pos(row, ccol));
        }

        if(pieces[point_to_pos(row, ccol)]->role_ != PieceRole::None)
        {
            for(int pccol = ccol - 1; pccol >= 0; --pccol)
            {
                if(pieces[point_to_pos(row, pccol)]->role_ != PieceRole::None && 
                   pieces[point_to_pos(row, pccol)]->camp_ != !(piece.camp_))
                {
                    possible_vector.emplace_back(point_to_pos(row, pccol));
                    break;
                }
            }
            break;
        }
    }

    for(int crow = row + 1; crow <= 10; ++crow)
    {
        if(pieces[point_to_pos(crow, col)]->role_ == PieceRole::None)
        {
            possible_vector.emplace_back(point_to_pos(crow, col));
        }

        if(pieces[point_to_pos(crow, col)]->role_ != PieceRole::None)
        {
            for(int pcrow = crow + 1; pcrow <= 10; ++pcrow)
            {
                if(pieces[point_to_pos(pcrow, col)]->role_ != PieceRole::None && 
                   pieces[point_to_pos(pcrow, col)]->camp_ != !(piece.camp_))
                {
                    possible_vector.emplace_back(point_to_pos(pcrow, col));
                    break;
                }
            }
            break;
        }
    }

    for(int crow = row - 1; crow >= 0; --crow)
    {
        if(pieces[point_to_pos(crow, col)]->role_ == PieceRole::None)
        {
            possible_vector.emplace_back(point_to_pos(crow, col));
        }

        if(pieces[point_to_pos(crow, col)]->role_ != PieceRole::None)
        {
            for(int pcrow = crow - 1; pcrow >= 0; ++pcrow)
            {
                if(pieces[point_to_pos(pcrow, col)]->role_ != PieceRole::None && 
                   pieces[point_to_pos(pcrow, col)]->camp_ != !(piece.camp_))
                {
                    possible_vector.emplace_back(point_to_pos(pcrow, col));
                    break;
                }
            }
            break;
        }
    }

    return possible_vector;
}

bool SoldiersStrategy::is_movable(int& previous, int& current, const std::vector<std::shared_ptr<Piece>>& pieces) 
{
    if (bool(pieces[previous]->camp_ )? (previous / 9) > 4 : (previous / 9) < 5)
        return current - previous == (bool(pieces[previous]->camp_) ? -9 : 9);
    else if (v_distance(previous, current) < 1)
        return h_distance(previous, current) == 1;
    else if (h_distance(previous, current) < 1)
        return v_coordinate(previous) - v_coordinate(current) == (bool(pieces[previous]->camp_) ? 1 : -1);
    else
        return false;
}

std::vector<int> SoldiersStrategy::get_possible_pos(const Piece& piece, const std::vector<std::shared_ptr<Piece>>& pieces) 
{
    if(piece.role_ == PieceRole::None)
    {
        return {};
    }

    std::vector<int> possible_vector;
    int col = piece.pos_ % 9;
    int row = piece.pos_ / 9;

    if(piece.camp_ == Camp::Black)
    {
        if(row > 4)
        {
            if(piece.camp_ != pieces[point_to_pos(row - 1, col)]->camp_)
            {
                possible_vector.push_back(point_to_pos(row - 1, col));
            }
        }
        else
        {
            if(row - 1 >= 0)
            {
                if(piece.camp_ != pieces[point_to_pos(row - 1, col)]->camp_)
                {
                    possible_vector.push_back(point_to_pos(row - 1, col));
                }
            }

            if(col - 1 >= 0)
            {
                if(piece.camp_ != pieces[point_to_pos(row, col - 1)]->camp_)
                {
                    possible_vector.push_back(point_to_pos(row, col - 1));
                }
            }

            if(col + 1 <= 8)
            {
                if(piece.camp_ != pieces[point_to_pos(row, col + 1)]->camp_)
                {
                    possible_vector.push_back(point_to_pos(row, col + 1));
                }
            }
        }
    }
    else if(piece.camp_ == Camp::Red)
    {
        if(row < 5)
        {
            if(piece.camp_ != pieces[point_to_pos(row + 1, col)]->camp_)
            {
                possible_vector.push_back(point_to_pos(row + 1, col));
            }
        }
        else
        {
            if(row + 1 <= 9)
            {
                if(piece.camp_ != pieces[point_to_pos(row + 1, col)]->camp_)
                {
                    possible_vector.push_back(point_to_pos(row + 1, col));
                }
            }

            if(col - 1 >= 0)
            {
                if(piece.camp_ != pieces[point_to_pos(row, col - 1)]->camp_)
                {
                    possible_vector.push_back(point_to_pos(row, col - 1));
                }
            }

            if(col + 1 <= 8)
            {
                if(piece.camp_ != pieces[point_to_pos(row, col + 1)]->camp_)
                {
                    possible_vector.push_back(point_to_pos(row, col + 1));
                }
            }
        }
    }
    
    return possible_vector;
}
