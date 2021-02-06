
#ifndef CHESS_ENTRY_H
#define CHESS_ENTRY_H

#include <QObject>
#include <memory>

#include "Engine.h"
#include "../ui/BaseWindow.h"
#include "../ui/PieceWidget.h"

class Entry : public QObject
{
Q_OBJECT
private:
	std::vector<PieceWidget*> pieceWidgets;

private:
	BaseWindow* ui;
	Engine* engine;

private slots:

	void piecePressEvent(int pos);

private:
	void initPieces();

public:
	explicit Entry(int index);

	~Entry() override;

void showWindow() const;
};

#endif //CHESS_ENTRY_H
