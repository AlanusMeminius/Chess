#ifndef CHESS_CHESSBOARD_H
#define CHESS_CHESSBOARD_H

#include <QWidget>
#include <QResizeEvent>
#include <QPainter>
#include <QPainterPath>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QGridLayout>

#include "PieceWidget.h"


class ChessBoard : public QWidget {
	Q_OBJECT
	private:
		int widthRatio;
		int heightRatio;
	public:
		QBoxLayout* layout;
		QWidget* board;
		QGridLayout* boardLayout;

public:
	ChessBoard() : widthRatio(8), heightRatio(9) {
		layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
		this->setLayout(layout);
		board = new QWidget(this);

		//board->setStyleSheet("background-color:#D8DEE9;");
		layout->addWidget(board);
		boardLayout = new QGridLayout;
		board->setLayout(boardLayout);
		//        this->setLayout(boardLayout);
	}

	void resizeEvent(QResizeEvent* event) override {
		const QSize oldSize = event->size();
		QSize newSize = event->size();

		if (newSize.width() < widthRatio * newSize.height() / heightRatio) {
			newSize.setHeight(heightRatio * newSize.width() / widthRatio);
			board->move(0, (oldSize.height() - newSize.height()) / 2);
		} else {
			newSize.setWidth(widthRatio * newSize.height() / heightRatio);
			board->move((oldSize.width() - newSize.width()) / 2, 0);
		}
		board->resize(newSize);
		}


	void paintEvent(QPaintEvent* event) override {
		QPainter painter(this);

		painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

		const QPoint halfHeightWidth(board->findChild<PieceWidget*>()->width() / 2,
		                             board->findChild<PieceWidget*>()->width() / 2);
		const QList<PieceWidget*> PieceList = board->findChildren<PieceWidget*>();

		for (int i = 0; i < PieceList.size(); i++) {
			if (i % 9 == 0) {
				painter.drawLine(PieceList[i]->pos() + halfHeightWidth, PieceList[i + 8]->pos() + halfHeightWidth);
			}
		}
		for (int j = 0; j < 9; j++) {
			painter.drawLine(PieceList[j]->pos() + halfHeightWidth, PieceList[81 + j]->pos() + halfHeightWidth);
		}
	}
};

#endif //CHESS_CHESSBOARD_H
