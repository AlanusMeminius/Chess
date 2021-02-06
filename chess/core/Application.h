
#ifndef CHESS_APPLICATION_H
#define CHESS_APPLICATION_H

#include <QObject>
#include <memory>

#include "Engine.h"
#include "../ui/BaseWindow.h"
#include "../ui/PieceWidget.h"

class Application : public QObject
{
Q_OBJECT
private:
	std::vector<PieceWidget*> pieceWidgets_;

private:
	BaseWindow* ui;
	Engine* engine;

private slots:

	void piece_press_event(int pos);

private:
	void _init_pieces();

public:
	explicit Application(int index);

	~Application() override;

void show_window() const;
};

#endif //CHESS_ENTRY_H
