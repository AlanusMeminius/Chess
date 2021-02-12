#ifndef CHESS_STRATEGY_H
#define CHESS_STRATEGY_H

#include <vector>
#include "Piece.h"

class Strategy {
public:
    virtual ~Strategy() = default;

    virtual bool is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) = 0;
};

class GeneralsStrategy : public Strategy {
public:
    bool is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) override;
};

class AdvisorsStrategy : public Strategy {
private:
    std::pair<std::vector<int>, std::vector<int>> possible_{
            {3,  5,  13, 21, 23},
            {66, 68, 76, 84, 86}};
private:
//    void _take_out(int &pos) {
//        if ()
//    }
public:
    bool is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) override;
};

class BishopsStrategy : public Strategy {
public:
    bool is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) override;
};

class HorsesStrategy : public Strategy {
public:
    bool is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) override;
};

class ChariotsStrategy : public Strategy {
public:
    bool is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) override;
};

class CannonsStrategy : public Strategy {
public:
    bool is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) override;
};

class SoldiersStrategy : public Strategy {
public:
    bool is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) override;
};


class StrategyCreator {
public:
    static Strategy *createStrategy(int type) {
        switch (type) {
            case 0:
                return new GeneralsStrategy();
            case 1:
                return new AdvisorsStrategy();
            case 2:
                return new BishopsStrategy();
            case 3:
                return new HorsesStrategy();
            case 4:
                return new ChariotsStrategy();
            case 5:
                return new CannonsStrategy();
            case 6:
                return new SoldiersStrategy();
            default:
                return nullptr;
        }
    }
};


#endif //CHESS_STRATEGY_H
