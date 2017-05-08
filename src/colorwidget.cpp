#include <QPainter>
#include "colorwidget.h"

ColorWidget::ColorWidget(QWidget *parent) : QWidget(parent)
{
	color = Qt::black;
}

void ColorWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
	QBrush background = QBrush(color);
	painter.fillRect(event->rect(), background);
    painter.end();
}
