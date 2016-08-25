#ifndef COLORWIDGET_H
#define COLORWIDGET_H
#include <QPaintEvent>
#include <QWidget>

class ColorWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ColorWidget(QWidget *parent = 0);
	QColor color;

signals:

public slots:

protected:
	void paintEvent(QPaintEvent * event) Q_DECL_OVERRIDE;
};

#endif // COLORWIDGET_H
