
#ifndef CHESS_ENGINE_H
#define CHESS_ENGINE_H

#include <vector>
#include <string>
#include <memory>

class Piece
{
public:
	bool camp_;
	int role_;
	int pos_;

public:
	Piece(char role, bool camp, int pos);
};


class Engine
{
private:
	int Mode;

protected:
	const std::string initChessBoard = "rnbakabnr/000000000/0c00000c0/p0p0p0p0p/000000000/"
		"000000000/P0P0P0P0P/0C00000C0/000000000/RNBAKABNR/";
public:
	std::vector<char> board_;
	std::vector<std::shared_ptr<Piece>> pieces_;
	int old_select_ = -1;
	bool current_camp_ = true;

private:

	void _chess_self();

	// ReSharper disable once CppInconsistentNaming
	void _chess_AI();

	void _chess_Net();

	void _update_representation();

public:
	explicit Engine(int select);

	void choose_mode();

	int check_pos(int&);
};


#endif //CHESS_ENGINE_H
