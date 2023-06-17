#ifndef CHESS_STRATEGY_H
#define CHESS_STRATEGY_H
#pragma once
 

#include <map>
#include <vector>
#include <memory>

#include "Piece.h"

class Strategy 
{
public:
    virtual ~Strategy() = default;

    virtual bool is_movable(int&, int&, const std::vector<std::shared_ptr<Piece>>&) = 0;
    virtual std::vector<int> get_possible_pos(const Piece& piece, const std::vector<std::shared_ptr<Piece>>& pieces) { return {}; }
};

class GeneralsStrategy : public Strategy 
{
private:
    static std::map<Camp, std::vector<int>> possible_;
public:
    bool is_movable(int&, int&, const std::vector<std::shared_ptr<Piece>>&) override;
    std::vector<int> get_possible_pos(const Piece& piece, const std::vector<std::shared_ptr<Piece>>& pieces) override;
};

class AdvisorsStrategy : public Strategy 
{
private:
    static std::map<Camp, std::map<int, std::vector<int>>> possible_;
public:
    bool is_movable(int&, int&, const std::vector<std::shared_ptr<Piece>>& ) override;
    std::vector<int> get_possible_pos(const Piece& piece, const std::vector<std::shared_ptr<Piece>>& pieces) override;
};

class BishopsStrategy : public Strategy 
{
    static std::map<Camp, std::map<int, std::vector<int>>> possible_;
public:
    bool is_movable(int&, int&, const std::vector<std::shared_ptr<Piece>>&) override;
    std::vector<int> get_possible_pos(const Piece& piece, const std::vector<std::shared_ptr<Piece>>& pieces) override;
};

class HorsesStrategy : public Strategy 
{
public:
    bool is_movable(int&, int&, const std::vector<std::shared_ptr<Piece>>&) override;
    std::vector<int> get_possible_pos(const Piece& piece, const std::vector<std::shared_ptr<Piece>>& pieces) override;
};

class ChariotsStrategy : public Strategy 
{
public:
    bool is_movable(int&, int&, const std::vector<std::shared_ptr<Piece>>&) override;
    std::vector<int> get_possible_pos(const Piece& piece, const std::vector<std::shared_ptr<Piece>>& pieces) override;
};

class CannonsStrategy : public Strategy 
{
public:
    bool is_movable(int&, int&, const std::vector<std::shared_ptr<Piece>>&) override;
    std::vector<int> get_possible_pos(const Piece& piece, const std::vector<std::shared_ptr<Piece>>& pieces) override;
};

class SoldiersStrategy : public Strategy 
{
public:
    bool is_movable(int&, int&, const std::vector<std::shared_ptr<Piece>>&) override;
    std::vector<int> get_possible_pos(const Piece& piece, const std::vector<std::shared_ptr<Piece>>& pieces) override;
};

class StrategyCreator 
{
public:
    static std::shared_ptr<Strategy> createStrategy(PieceRole role) {
        switch (role) {
            case PieceRole::Generals:
                return std::make_shared<GeneralsStrategy>();
            case PieceRole::Advisors:
                return std::make_shared<AdvisorsStrategy>();
            case PieceRole::Bishops:
                return std::make_shared<BishopsStrategy>();
            case PieceRole::Horses:
                return std::make_shared<HorsesStrategy>();
            case PieceRole::Chariots:
                return std::make_shared<ChariotsStrategy>();
            case PieceRole::Cannons:
                return std::make_shared<CannonsStrategy>();
            case PieceRole::Soldiers:
                return std::make_shared<SoldiersStrategy>();
            default:
                return {};
        }
    }
};

#endif //CHESS_STRATEGY_H
