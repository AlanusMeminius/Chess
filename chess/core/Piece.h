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
#include <array>

// template<typename A, typename B,
// 	std::enable_if_t<std::is_integral<A>::value || std::is_enum<A>::value> * = nullptr,
// 	std::enable_if_t<std::is_enum<B>::value || std::is_integral<B>::value> * = nullptr>
// bool operator==(A a, B b)
// {
// 	return a == A(b);
// }

// template<typename A, typename B,
// 	std::enable_if_t<std::is_integral<A>::value || std::is_enum<A>::value> * = nullptr,
// 	std::enable_if_t<std::is_enum<B>::value || std::is_integral<B>::value> * = nullptr>
// bool operator>(A a, B b)
// {
// 	return a > A(b);
// }

// template<typename A, typename B,
// 	std::enable_if_t<std::is_integral<A>::value || std::is_enum<A>::value> * = nullptr,
// 	std::enable_if_t<std::is_enum<B>::value || std::is_integral<B>::value> * = nullptr>
// bool operator>=(A a, B b)
// {
// 	return a >= A(b);
// }

// template<typename A, typename B,
// 	std::enable_if_t<std::is_integral<A>::value || std::is_enum<A>::value> * = nullptr,
// 	std::enable_if_t<std::is_enum<B>::value || std::is_integral<B>::value> * = nullptr>
// bool operator<(A a, B b)
// {
// 	return a < A(b);
// }

// template<typename A, typename B,
// 	std::enable_if_t<std::is_integral<A>::value || std::is_enum<A>::value> * = nullptr,
// 	std::enable_if_t<std::is_enum<B>::value || std::is_integral<B>::value> * = nullptr>
// bool operator<=(A a, B b)
// {
// 	return a <= A(b);
// }

// template<typename A, typename B,
// 	std::enable_if_t<std::is_integral<A>::value || std::is_enum<A>::value> * = nullptr,
// 	std::enable_if_t<std::is_enum<B>::value || std::is_integral<B>::value> * = nullptr>
// bool operator!=(A a, B b)
// {
// 	return a != A(b);
// }

class Strategy;

enum class PieceRole {
    Generals,     // 将
    Advisors,     // 士
    Bishops,      // 象
    Horses,       // 马
    Chariots,     // 车
    Cannons,      // 炮
    Soldiers,     // 兵
    None,         // 空
};

// // 枚举值角色的比较
// inline bool operator<(const PieceRole& lhs, const PieceRole& rhs) noexcept
// {
//     return int(lhs) < int(rhs);
// }

// inline bool operator<(const PieceRole& lhs, const int& rhs) noexcept
// {
//     return int(lhs) < rhs;
// }



enum class Camp {
    Red,
    Black,
    White,
};

struct TraceUnit
{
    int pos;
    PieceRole role;
};

inline Camp operator!(const Camp& camp) noexcept
{
    return (camp == Camp::Red) ? Camp::Black : Camp::Red;
}

class Piece 
{
public:
    Camp camp_;
    PieceRole role_;
    int pos_;

public:
    Piece(char role, Camp camp, int pos);
    void set_strategy(const std::shared_ptr<Strategy>& strategy) { _strategy = strategy; }
    bool is_movable(int, const std::vector<std::shared_ptr<Piece>>& );

private:
    static const std::array<char, 7> _roleChar;
    std::shared_ptr<Strategy> _strategy;
};

#endif //CHESS_PIECE_H
