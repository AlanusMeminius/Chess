#ifndef CHESS_APPLICATION_H
#define CHESS_APPLICATION_H

#include <QObject>

#include "Engine.h"
#include "../ui/BaseWindow.h"
#include "../ui/PieceWidget.h"

class Application : public QObject {
Q_OBJECT
	std::vector<PieceWidget*> pieceWidgets_;
bool is_first_step = true;
int previous_select_ = -1;
bool current_camp_ = true;

BaseWindow* ui;
	Engine* engine;

private slots:

void piece_click_event(int pos);

private:
void _init_pieces();
bool _check_role(int&) const;
bool _check_camp(int&) const;
void _check_first_step(int&);
void _check_second_step(int&);
void _change_highlight(int&, int&);
void _move_pieces(int&, int&);

public:
	explicit Application(int index);

	~Application() override;

void show_window() const;
};

#endif //CHESS_ENTRY_H
