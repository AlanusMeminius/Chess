#include "Application.h"

Application::Application(int index) : ui(new BaseWindow), engine(new Engine(index)) {
	engine->choose_mode();
	_init_pieces();
}

void Application::show_window() const {
	ui->show();
}

Application::~Application() {
	delete ui;
	delete engine;
}

void Application::_init_pieces() {
	for (auto& piece : engine->pieces_) {
		pieceWidgets_.push_back(new PieceWidget(piece));
		PieceWidget* p = pieceWidgets_.back();
		ui->chessBoard->boardLayout->addWidget(p, piece->pos_ / 9, piece->pos_ % 9);
		connect(p, &PieceWidget::getPos, this, &Application::piece_click_event);
	}
}

bool Application::_check_role(int& pos) const {
	return (engine->pieces_[pos]->role_ < 9) ? true : false;
}

bool Application::_check_camp(int& pos) const {
	return (engine->pieces_[pos]->camp_ == current_camp_) ? true : false;
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

void Application::_check_first_step(int& pos) {
	if (_check_role(pos)) {
		if (_check_camp(pos)) {
			qDebug() << "current camp: " << current_camp_ << ", select: " << pos;
			pieceWidgets_[pos]->HighLightPiece();
			previous_select_ = pos;
			is_first_step = !is_first_step;
		} else {
			qDebug() << "Now turn to other side";
		}
	}
}

void Application::_check_second_step(int& pos) {
	if (_check_role(pos)) {
		if (_check_camp(pos)) {
			qDebug() << "change: " << previous_select_ << " to " << pos;
			this->_change_highlight(previous_select_, pos);
		} else {
			qDebug() << "!!!";
		}
	} else {
		if (engine->check_strategy(pos)) {
			qDebug() << "move: " << previous_select_ << " to " << pos;
			this->_move_pieces(previous_select_, pos);
			is_first_step = !is_first_step;
			current_camp_ = !current_camp_;
		} else {
			qDebug() << "can not move!";
		}
	}
}


void Application::piece_click_event(int pos) {
	if (is_first_step) {
		_check_first_step(pos);
	} else {
		_check_second_step(pos);
	}
}

void Application::_change_highlight(int& previous, int& current) {
	pieceWidgets_[previous]->ReverseHighLight();
	pieceWidgets_[current]->HighLightPiece();
}

void Application::_move_pieces(int& previous, int& current) {
	// ...

	//engine->update_representation(current);
}
