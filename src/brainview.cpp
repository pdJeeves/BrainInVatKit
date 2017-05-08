#include "brainview.h"
#include <QToolTip>
#include <QMenu>

BrainView::BrainView(QWidget *parent) :
QWidget(parent)
{
	setMouseTracking(true);
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
	        this, SLOT(ShowContextMenu(const QPoint &)));
	time.start();
}

static inline
QPoint margin()
{
	return QPoint(0, 00);
}

static inline
QSize operator-(const QSize & a, const QPoint & b)
{
	return QSize(a.width() - b.x(), a.height() - b.y());
}


void BrainView::setOwner(MainWindow * o)
{
	ownr = o;
}

void BrainView::mousePressEvent(QMouseEvent * event)
{
	last_pos = event->pos() - ::margin();
	ownr->onMousePress(last_pos, size() - ::margin() * 2, event->button());
}

void BrainView::mouseReleaseEvent(QMouseEvent * event)
{
	last_pos = event->pos() - ::margin();
	ownr->onMouseRelease(last_pos, size() - ::margin() * 2, event->button());
}

void BrainView::mouseDoubleClickEvent(QMouseEvent * event)
{
	last_pos = event->pos() - ::margin();
	ownr->onMouseDoubleClick(last_pos, size() - ::margin() * 2, event->button());
}

void BrainView::mouseMoveEvent(QMouseEvent * event)
{
	last_pos = event->pos() - ::margin();

	if(time.elapsed() < 32)
	{
		return;
	}

	time.restart();
	ownr->onMouseMoveEvent(last_pos, size() - ::margin() * 2, event->button());
}

void BrainView::ShowContextMenu(const QPoint & pos)
{
	last_pos = pos - ::margin();
	QMenu * menu = ownr->showContextMenu(this, last_pos, size() - ::margin() * 2);

	if(menu)
	{
		 menu->popup(mapToGlobal(pos));
	}
}

void BrainView::paintEvent(QPaintEvent * event)
{
static QBrush background(Qt::black);
	QPainter painter;
	painter.begin(this);
	painter.fillRect(event->rect(), background);
	painter.translate(::margin());
	ownr->draw(painter, last_pos, size());
	painter.end();
}

bool BrainView::event(QEvent *event)
{
	if (event->type() == QEvent::ToolTip)
	{
	   QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
	   last_pos = helpEvent->pos() - ::margin();

	   QString string = ownr->getToolTip(last_pos, size() - ::margin() * 2);

	   if(!string.isEmpty())
	   {
		   QToolTip::showText(helpEvent->globalPos(), string);
	   }
	   else
	   {
		   QToolTip::hideText();
		   event->ignore();
	   }

	   return true;
   }
   return super::event(event);
}


