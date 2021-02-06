
#ifndef CHESS_ENGINE_H
#define CHESS_ENGINE_H

#include <vector>
#include <string>
#include <memory>

class Piece
{
public:
	bool Camp;
	int Role;
	int Pos;

public:
	Piece(char role, bool camp, int pos);
};


class Engine
{
private:
	int Mode;

protected:
	const std::string InitChessBoard = "rnbakabnr/000000000/0c00000c0/p0p0p0p0p/000000000/"
		"000000000/P0P0P0P0P/0C00000C0/000000000/RNBAKABNR/";
public:
	std::vector<char> board;
	std::vector<std::shared_ptr<Piece>> pieces;
	int oldSelect = -1;
	bool currentCamp = true;

private:

	void chessSelf();

	void chessAI();

	void chessNet();

	void updateRepresentation();

public:
	explicit Engine(int select);

	void chooseMode();

	int checkPos(int&);
};


#endif //CHESS_ENGINE_H
