
#include "PieceWidget.h"

PieceWidget::PieceWidget(std::shared_ptr<Piece>& piece) : logicPiece(piece)
{
}

void PieceWidget::paintEvent(QPaintEvent* event)
{
	if (logicPiece->role_ > 8)
	{
	}
	else
	{
		QPainter painter(this);
		painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
		painter.setPen(Qt::black);
		painter.drawEllipse(QPoint(width() / 2, height() / 2), width() / 2, width() / 2);
	}
}

void PieceWidget::mousePressEvent(QMouseEvent*)
{
	emit getPos(logicPiece->pos_);
}

//void PieceWidget::getPos(std::pair<int, int>) {
//
//}
