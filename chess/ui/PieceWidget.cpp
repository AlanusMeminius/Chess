#include "PieceWidget.h"


PieceWidget::PieceWidget(std::shared_ptr<Piece> &piece) :
        logicPiece(piece) {
}

void PieceWidget::HighLightPiece() {

}

void PieceWidget::ReverseHighLight() {
}

void PieceWidget::paintEvent(QPaintEvent *event) {

    if (logicPiece->role_ < 9) {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        painter.setFont(QFont("Microsoft YaHei", 20, 50, false));
        painter.setPen(Qt::white);
        if (logicPiece->camp_) {
            painter.setBrush(QColor(255, 0, 0));
        } else {
            painter.setBrush(QColor(56, 72, 99));
        }
        painter.drawEllipse(QPoint(width() / 2, height() / 2), width() / 2, height() / 2);
        painter.drawText(QRect(0, 0, width(), height()),
                         Qt::AlignCenter,
                         QString::fromStdString(types[logicPiece->role_]));
        painter.end();

    }
    //painter.drawPixmap(QPoint(0, 0), pixmap);
}

void PieceWidget::mousePressEvent(QMouseEvent *) {
    emit getPos(logicPiece->pos_);
}
