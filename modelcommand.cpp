#include "modelcommand.h"
#include "brainmodel.h"
#include "lobemodel.h"
#include "tractmodel.h"

CommandInterface::~CommandInterface() { }

InsertionCommand::InsertionCommand(BrainModel * brain, const std::list<LobeModel *> & ins_lobes, const std::list<TractModel *> & ins_tracts)
	: lobes(brain->list<LobeModel>()),
	  tracts(brain->list<TractModel>()),
	  ins_lobes(ins_lobes),
	  ins_tracts(ins_tracts) { }

void InsertionCommand::rollBack()
{
	for(auto i = ins_lobes.begin(); i != ins_lobes.end(); ++i)
	{
		lobes.remove(*i);
	}

	for(auto i = ins_tracts.begin(); i != ins_tracts.end(); ++i)
	{
		tracts.remove(*i);
	}
}

void InsertionCommand::rollForward()
{
	for(auto i = ins_lobes.begin(); i != ins_lobes.end(); ++i)
	{
		lobes.push_back(*i);
	}

	for(auto i = ins_tracts.begin(); i != ins_tracts.end(); ++i)
	{
		tracts.push_back(*i);
	}
}

DeletionCommand::DeletionCommand(BrainModel * brain, const std::list<LobeModel *> & del_lobes, const std::list<TractModel *> & del_tracts)
	: lobes(brain->list<LobeModel>()),
	  tracts(brain->list<TractModel>()),
	  del_lobes(del_lobes),
	  del_tract(del_tracts) { }

void DeletionCommand::rollBack()
{
	for(auto i = del_lobes.begin(); i != del_lobes.end(); ++i)
	{
		lobes.push_back(*i);
	}

	for(auto i = del_tract.begin(); i != del_tract.end(); ++i)
	{
		tracts.push_back(*i);
	}
}

void DeletionCommand::rollForward()
{
	for(auto i = del_lobes.begin(); i != del_lobes.end(); ++i)
	{
		lobes.remove(*i);
	}

	for(auto i = del_tract.begin(); i != del_tract.end(); ++i)
	{
		tracts.remove(*i);
	}
}

MouseCommand::~MouseCommand() { }

static inline
int cap(int a, int b, int c)
{
	return a < 0? 0 : a + b < c? a : c - b;
}

static inline
QPoint cap(const QPoint & a, const QSize & b, const  QSize & c)
{
	return QPoint(cap(a.x(), b.width(), c.width()), cap(a.y(), b.height(), c.height()));
}

static inline
int cap(int delta, int pos, int size, int max)
{
	return pos + delta < 0? -pos : pos + size + delta < max? delta : max - (pos + size);
}

static inline
QPoint cap(const QPoint & a, const QRect & b, const  QSize & c)
{
	return QPoint(cap(a.x(), b.x(), b.width(), c.width()), cap(a.y(), b.y(), b.height(), c.height()));
}

MoveCommand::MoveCommand(LobeModel *it, const QPointF & pos)
	: cursor_start((int) pos.x(), (int) pos.y()),
	  new_pos(0, 0)
{
	prev_pos = it->position();
	lobes = it;
}

void MoveCommand::update(const QPointF & pos)
{
	QPointF n_pos = (pos - cursor_start);
	new_pos = QPoint((int) n_pos.x(), (int) n_pos.y());

		new_pos = cap(new_pos,
			QRect(	lobes->identity.data.posx,
					lobes->identity.data.posy,
					lobes->identity.data.width,
					lobes->identity.data.height),
			BrainModel::maxSize());

	new_pos = new_pos + prev_pos;
	lobes->setPosition(new_pos);
}

bool MoveCommand::valid()
{
	return new_pos != QPoint(0, 0) && !lobes->brain.doesIntersect(lobes);
}

void MoveCommand::cancel()
{
	lobes->setPosition(prev_pos);
}

void MoveCommand::rollBack()
{
	lobes->setPosition(prev_pos);
	lobes->commit();
}

void MoveCommand::rollForward()
{
	lobes->setPosition(new_pos);
	lobes->commit();
}

ScaleCommand::ScaleCommand(LobeModel * _lobe, const QPointF & pos, int _flags)
{
	lobe		= _lobe;
	cursor_start= pos;
	original	= lobe->box();
	new_scale	= lobe->box();
	flags		= _flags;

}

void ScaleCommand::update(const QPointF & pos)
{
	int x = original.x();
	int y = original.y();
	int w = original.width();
	int h = original.height();

	int mw = LobeModel::maxSize().width();
	int mh = LobeModel::maxSize().height();

	QPoint d = (pos - cursor_start).toPoint();

	int max_neurons = BrainModel::maxNeurons() - lobe->brain.totalNeurons() - lobe->length();

	if(flags & 0x01)
	{
		x = original.x() + d.x();
		w = original.width() - d.x();

		if(x >= (original.x() + original.width()))
		{
			x = original.x() + original.width() - 1;
		}

		if(w > mw)
		{
			x += (w - mw);
		}
	}
//left edge
	else if(flags & 0x02)
	{
		w = d.x() + original.width();
	}

	if(flags & 0x10)
	{
		y  = original.y() + d.y();
		h  = original.height() - d.y();

		if(y >= (original.y() + original.height()))
		{
			y = original.y() + original.height() - 1;
		}

		if(h > mh)
		{
			y += (h - mh);
		}
	}
	else if(flags & 0x20)
	{
		h = d.y() + original.height();
	}


	if(w * h > max_neurons)
	{
		return;
	}

	w = w < 1? 1 : w < mw? w : mw;
	h = h < 1? 1 : h < mh? h : mh;

	QSize  size(w, h);

	new_scale = QRect(cap(QPoint(x, y), size, BrainModel::maxSize()), size);
	lobe->setBox(new_scale);
}

bool ScaleCommand::valid()
{
	return original != new_scale && !lobe->brain.doesIntersect(lobe);
}

void ScaleCommand::cancel()
{
	lobe->setBox(original);
}


void ScaleCommand::rollBack()
{
	lobe->setBox(original);
	lobe->commit();
}

void ScaleCommand::rollForward()
{
	lobe->setBox(new_scale);
	lobe->commit();
}

