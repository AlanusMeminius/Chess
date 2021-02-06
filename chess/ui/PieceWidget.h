
#ifndef CHESS_PIECEWIDGET_H
#define CHESS_PIECEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QtWidgets/QBoxLayout>
#include "../core/Engine.h"

class PieceWidget : public QWidget
{
	Q_OBJECT
public:
	std::shared_ptr<Piece>& logicPiece;

public:
	explicit PieceWidget(std::shared_ptr<Piece>& piece);
	void HighLightPiece();

signals:
	void getPos(int);	

protected:
	void paintEvent(QPaintEvent* event) override;

	void mousePressEvent(QMouseEvent*) override;
};

#endif //CHESS_PIECEWIDGET_H
