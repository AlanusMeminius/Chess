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
	/*默认是第一步，检查到是行进方棋子，highlight， reverse flag*/
	if (is_first_step)
	{
		if (engine->check_role_camp(pos))
		{
			pieceWidgets_[pos]->HighLightPiece();
			engine->old_select_ = pos;
			is_first_step = false;
		}
	}
		/*检查第二步*/
	else
	{
		/*如果是行进方棋子，更改高亮*/
		if (engine->check_role_camp(pos))
			this->_change_highlight(engine->old_select_, pos);
			/*如果是其他位置，搜索移动策略*/
		else
		{
			/*如果可以移动，移动棋子*/
			if (engine->check_strategy(pos))
			{
				this->_move_pieces(engine->old_select_, pos);
				is_first_step = true;
			}
				/*如果不可以移动，显示状态栏信息*/
			else
			{
				// status bar msg
			}
		}
	}
}

void Application::_change_highlight(int& old, int& current)
{
	pieceWidgets_[old]->ReverseHighLight();
	pieceWidgets_[current]->HighLightPiece();
}

void Application::_move_pieces(int& old, int& current)
{
	// ...

	engine->update_representation(current);
}
