#include "Strategy.h"

bool GeneralsStrategy::is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) {
    return false;
}

bool AdvisorsStrategy::is_movable(int &previous, int &current, std::vector<std::shared_ptr<Piece>> &pieces) {
    /*
     * 搜寻步骤：
     * 1. 列出所有可移动位置
     * 2. 排除己方棋子占据的位置
     * */
    return false;
}

bool BishopsStrategy::is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &pieces) {
    return false;
}

bool HorsesStrategy::is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) {
    return false;
}

bool ChariotsStrategy::is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) {
    return false;
}


bool CannonsStrategy::is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) {
    return false;
}

bool SoldiersStrategy::is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) {
    return false;
}
