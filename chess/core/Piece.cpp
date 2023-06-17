//
// Created by Uniqu on 2/10/2021.
//
 

#include "Piece.h"
#include "Strategy.h"
#include <algorithm>

const std::array<char, 7> Piece::_roleChar{ 'k', 'a', 'b', 'n', 'r', 'c', 'p' };
const Piece Piece::whitePiece = Piece('0', Camp::White, -1);
const std::shared_ptr<Piece> Piece::whitePieceSharedPtr = std::make_shared<Piece>(Piece::whitePiece);

Piece::Piece(char role, Camp camp, int pos) 
    : camp_(camp)
    , pos_(pos) 
{
    const auto iter = std::find(_roleChar.begin(), _roleChar.end(), tolower(role));

    if (iter != _roleChar.end())
    {
        auto role_index = std::distance(std::begin(_roleChar), iter);
        role_ = PieceRole(role_index);
        _strategy = std::move(StrategyCreator::createStrategy(role_));
    }  
    else
    {
        role_ = PieceRole::None;
    }
}

Piece::Piece(PieceRole role, Camp camp, int pos)
    : camp_(camp)
    , pos_(pos)
    , role_(role)
{
    _strategy = std::move(StrategyCreator::createStrategy(role_));
}

bool Piece::is_movable(int destion, const std::vector<std::shared_ptr<Piece>>& pieces)
{
    if(_strategy.get() == nullptr)
    {
        return false;
    }

    return _strategy->is_movable(pos_, destion, pieces);
}