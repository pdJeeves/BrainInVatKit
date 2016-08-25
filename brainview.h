#ifndef BRAINVIEW_H
#define BRAINVIEW_H
#include "mainwindow.h"
#include <QPainter>
#include <QHelpEvent>
#include <QWidget>
#include <QTime>

class BrainView : public QWidget
{
typedef QWidget super;

	Q_OBJECT

	QPoint last_pos;
	MainWindow * ownr;
	QTime	 time;

public:
	explicit BrainView(QWidget *parent = 0);

	void setOwner(MainWindow * o);

	void mousePressEvent		(QMouseEvent * event)	Q_DECL_OVERRIDE;
	void mouseReleaseEvent		(QMouseEvent * event)	Q_DECL_OVERRIDE;
	void mouseDoubleClickEvent	(QMouseEvent * event)	Q_DECL_OVERRIDE;
	void mouseMoveEvent			(QMouseEvent * event)	Q_DECL_OVERRIDE;

	bool event					(QEvent *event)			Q_DECL_OVERRIDE;
	void paintEvent				(QPaintEvent * event)	Q_DECL_OVERRIDE;

public slots:
	void ShowContextMenu		(const QPoint & pos);
};

#endif // BRAINVIEW_H
