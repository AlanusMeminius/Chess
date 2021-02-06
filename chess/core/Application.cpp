#pragma execution_character_set("utf-8")
#include "Application.h"

Application::Application(int index) : ui(new BaseWindow), engine(new Engine(index))
{
	engine->choose_mode();
	_init_pieces();
}

void Application::show_window() const
{
	ui->show();
}

Application::~Application()
{
	delete ui;
	delete engine;
}

void Application::_init_pieces()
{
	for (auto& piece : engine->pieces_)
	{
		pieceWidgets_.push_back(new PieceWidget(piece));
		PieceWidget* p = pieceWidgets_.back();
		ui->chessBoard->boardLayout->addWidget(p, piece->pos_ / 9, piece->pos_ % 9);
		connect(p, &PieceWidget::getPos, this, &Application::piece_press_event);
	}
}

/*
 * case1: 不是棋子位置 -> pass
 * case2: 开局第一次选中棋子 -> highlight
 * case3: 没有选中己方棋子的情况下，选中对方棋子 -> pass
 * case3：选中己方棋子，再选择位置可行 -> 移动棋子(更改控件)
 * case4：选中己方棋子，再选择位置不可行 -> msg
 * // 第一次选棋子
 * - 不是棋子位置 或是对方棋子-> pass
 * - 是我方棋子 -> highlight, flag
 *
 * // 第二次选要走的位置
 * - 是我方棋子 -> 更改高亮
 * - 其他位置，搜索移动策略，检查可行性
 *      - 可以移动，移动棋子，flag
 *      - 不可移动，status bar-msg
 * */

void Application::piece_press_event(int pos)
{
	// 先检查位置是不是棋子, 检查轮走棋方和选中棋子是否对应
	// 记录棋子位置, 改棋子样式
	// 检查是否已经选中一枚己方棋子
	// 根据棋子类型获取移动规则
	// 获取可移动位置 checked

	qDebug() << pos;
	switch (engine->check_pos(pos))
	{
	default:
		break;
	case 2:
		//pieceWidgets[pos]->HighLightPiece();
		break;
	case 1:
		// 移动棋子
		break;
		//
	}
}
