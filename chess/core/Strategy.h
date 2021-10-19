#ifndef CHESS_STRATEGY_H
#define CHESS_STRATEGY_H
#pragma once
#pragma execution_character_set("utf-8") 

#include <map>
#include <vector>
#include "Piece.h"

class Strategy {
public:
    virtual ~Strategy() = default;

    virtual bool is_movable(int&, int&, std::vector<std::shared_ptr<Piece>>&) = 0;
};

class GeneralsStrategy : public Strategy {
private:
    std::map<Camp, std::vector<int>> possible_{
            {Camp::Red,  {3,  4,  5,  12, 13, 14, 21, 22, 23}},
            {Camp::Black, {66, 67, 68, 75, 76, 78, 84, 85, 86}}
    };
public:
    bool is_movable(int&, int&, std::vector<std::shared_ptr<Piece>>&) override;
};

class AdvisorsStrategy : public Strategy {
private:
    std::map<Camp, std::map<int, std::vector<int>>> possible_{
            {Camp::Red, {
                            {3,  {13}},
                            {5,  {13}},
                            {13, {3,  5,  21, 23}},
                            {21, {13}},
                            {23, {13}}
                    },
            },
            {Camp::Black,  {
                            {66, {76}},
                            {68, {76}},
                            {76, {66, 68, 84, 86}},
                            {84, {76}},
                            {86, {76}}
                    },
            }
    };
public:
    bool is_movable(int&, int&, std::vector<std::shared_ptr<Piece>>& ) override;
};

class BishopsStrategy : public Strategy {
    std::map<Camp, std::vector<int>> possible_{
            {Camp::Red, {2,  6,  18, 22, 26, 38, 42}},
            {Camp::Black,  {47, 51, 63, 67, 71, 83, 87}}
    };
public:
    bool is_movable(int&, int&, std::vector<std::shared_ptr<Piece>>&) override;
};

class HorsesStrategy : public Strategy {
public:
    bool is_movable(int&, int&, std::vector<std::shared_ptr<Piece>>&) override;
};

class ChariotsStrategy : public Strategy {
public:
    bool is_movable(int&, int&, std::vector<std::shared_ptr<Piece>>&) override;
};

class CannonsStrategy : public Strategy {
public:
    bool is_movable(int&, int&, std::vector<std::shared_ptr<Piece>>&) override;
};

class SoldiersStrategy : public Strategy {
public:
    bool is_movable(int&, int&, std::vector<std::shared_ptr<Piece>>&) override;
};

class StrategyCreator {
public:
    static Strategy* createStrategy(PieceRole role) {
        switch (role) {
            case PieceRole::Generals:
                return new GeneralsStrategy();
            case PieceRole::Advisors:
                return new AdvisorsStrategy();
            case PieceRole::Bishops:
                return new BishopsStrategy();
            case PieceRole::Horses:
                return new HorsesStrategy();
            case PieceRole::Chariots:
                return new ChariotsStrategy();
            case PieceRole::Cannons:
                return new CannonsStrategy();
            case PieceRole::Soldiers:
                return new SoldiersStrategy();
            default:
                return nullptr;
        }
    }
};

#endif //CHESS_STRATEGY_H
