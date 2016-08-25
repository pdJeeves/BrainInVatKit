#include "brainmodel.h"
#include "catalogue/catalogue_interface.h"

template<>
std::list<LobeModel *> & BrainModel::list<LobeModel>() { return lobes; }
template<>
std::list<TractModel *> & BrainModel::list<TractModel>() { return tracts; }

template<>
const std::list<LobeModel *> & BrainModel::const_list<LobeModel>() const { return lobes; }
template<>
const std::list<TractModel *> & BrainModel::const_list<TractModel>() const { return tracts; }

BrainModel::BrainModel(MainWindow & window)
	: window(window)
{
	new_gene = 0L;
	move     = 0L;
}

bool BrainModel::doesIntersect(const LobeModel * it) const
{
	for(auto i = const_list<LobeModel>().begin(); i != const_list<LobeModel>().end(); ++i)
	{
		if(it != *i && it->box().intersects((*i)->box()))
		{
			return true;
		}
	}

	return false;
}

int BrainModel::totalNeurons() const
{
	int total = 0;
	for(auto i = const_list<LobeModel>().begin(); i != const_list<LobeModel>().end(); ++i)
	{
		total += (*i)->length();
	}

	return total;
}

BrainModel::~BrainModel()
{
	for(auto i = list<TractModel>().begin(); i != list<TractModel>().end(); ++i)
	{
		delete *i;
	}

	for(auto i = list<LobeModel>().begin(); i != list<LobeModel>().end(); ++i)
	{
		delete *i;
	}
}

QPointF BrainModel::convertLocation(const QPoint & pos, const QSize & size)
{
	QRect port = viewPort();
	QSizeF pixels((double) size.width()/port.width(), (double) size.height()/port.height());

	last_pos = QPointF(
		port.x() + pos.x() / pixels.width(),
		port.y() + pos.y() / pixels.height());
	return last_pos;
}

#if 0
QRectF BrainModel::convertSelection(const QRect & rect, const QSize & size) const
{
	QRect port = viewPort();
	QSizeF pixels((double) size.width()/port.width(), (double) size.height()/port.height());

	return QRectF(
		port.x() + rect.x() / pixels.width(),
		port.y() + rect.y() / pixels.height(),
		rect.width() / pixels.width(),
		rect.height()/ pixels.height());
}
#endif

void BrainModel::newLobe()
{
	LobeData data;
	memset(&data, 0, sizeof(data));
	data.posx		= last_pos.x();
	data.posy		= last_pos.y();
	data.width		= 1;
	data.height		= 1;
	data.threshold  = 64;
	data.duty_cycle.period     = 10000;
	data.relax_state = 128;
	data.relax_prev  = 255;
	data.max_boost  = 2;
	auto lobe = new LobeModel(*this, QString(), data);
	new_gene = lobe;
	lobe->editGene();
}

bool BrainModel::hasChanged() const
{
	return has_changed<LobeModel>() && has_changed<TractModel>();
}


QRect BrainModel::viewPort(const std::list<LobeModel*> & lobes) const
{
#if 1
	static const int margin = 2;
	static const int min = 32;
	int min_x = 255;
	int min_y = 255;
	int max_x = 0;
	int max_y = 0;

	for(auto i = lobes.begin(); i != lobes.end(); ++i)
	{
		if((*i)->box().left() < min_x)
		{
			min_x = (*i)->box().left();
		}

		if((*i)->box().right() + 1 > max_x)
		{
			max_x = (*i)->box().right() + 1;
		}

		if((*i)->box().top() < min_y)
		{
			min_y = (*i)->box().top();
		}

		if((*i)->box().bottom() + 1 > max_y)
		{
			max_y = (*i)->box().bottom() + 1;
		}
	}

	if(min_x > max_x)
	{
		min_x = maxSize().width() / 2 - min / 2;
		max_x = min_x + min;
	}
	else if(max_x - min_x < min)
	{
		int diff = min - (max_x - min_x);

		min_x = min_x - diff/2 <   0?	0 : min_x - diff/2;
		max_x = min_x + min    > 255? 255 : min_x + min;
	}

	if(min_y > max_y)
	{
		min_y = maxSize().height() / 2 - min/2;
		max_y = min_y + min;
	}
	else if(max_y - min_y < min)
	{
		int diff = min - (max_y - min_y);

		min_y = min_y - diff/2 <   0?   0 :	min_y - diff/2;
		max_y = min_y + min    > 255? 255 : min_y + min;
	}

	return QRect(min_x - margin, min_y - margin, (max_x - min_x) + margin*2, (max_y - min_y) + margin*2);
#else
	return QRect(0, 0, 72, 72);
#endif
}


QRect BrainModel::viewPort() const
{
	return viewPort(lobes);
}


void BrainModel::add(LobeGene * gene)
{
	list<LobeModel>().push_back(new LobeModel(*this, QString(gene->header.organ), gene->data));
}

void BrainModel::add(TractGene * gene)
{
	list<TractModel>().push_back(new TractModel(*this, QString(gene->header.organ), gene->data));
}

void BrainModel::remove(LobeModel * it)
{
	std::list<LobeModel *> lobes;
	std::list<TractModel *> tracts;

	lobes.push_back(it);

	window.add_command(new DeletionCommand(this, lobes, tracts));
}

void BrainModel::remove(TractModel * it)
{
	std::list<LobeModel *> lobes;
	std::list<TractModel *> tracts;

	tracts.push_back(it);

	window.add_command(new DeletionCommand(this, lobes, tracts));
}


bool BrainModel::beginMove(const QPoint & origin, const QSize & canvas)
{
	if(move)
	{
		return false;
	}

	auto cursor = convertLocation(origin, canvas);
	QPoint pos((int) cursor.x(), (int) cursor.y());

	for(auto i = list<LobeModel>().begin(); i != list<LobeModel>().end(); ++i)
	{
		if((*i)->box().contains(pos))
		{
			move = new MoveCommand(*i, pos);
			return true;
		}
	}

	return false;
}

void BrainModel::updateMove(const QPoint & origin, const QSize & canvas)
{
	if(move)
	{
		auto cursor = convertLocation(origin, canvas);
		move->update(cursor);
	}
}

void BrainModel::cancelMove()
{
	if(move)
	{
		move->cancel();
		delete move;
		move = 0L;
	}
}

void BrainModel::commitMove()
{
	if(move)
	{
		if(move->valid())
		{
			window.add_command(move);
		}
		else
		{
			move->cancel();
			delete move;
		}
	}

	move = 0L;
}

bool BrainModel::save(QString filename)
{
	FILE * file = fopen(filename.toStdString().c_str(), "w");
	if(!file)
	{
		return false;
	}

	fprintf(file, "<%s>\n",
		catalogue_get_string("genome symbols", GENOME));

	ExportMoniker(file, "brain",
		"0000" "0000" "0000" "CAIN",
		"0000" "0000" "0000" "ADAM",
		"0000" "0000" "0000" "0EVE");

	fprintf(file, "\t<%s %s='a'>\n",
		catalogue_get_string("genome symbols", CHROMOSOME),
		catalogue_get_string("genome symbols", ID));

	for(auto i = list<LobeModel>().begin(); i != list<LobeModel>().end(); ++i)
	{
		(*i)->save(file);
	}

	for(auto i = list<TractModel>().begin(); i != list<TractModel>().end(); ++i)
	{
		(*i)->save(file);
	}

	fprintf(file, "\t</%s>\n",
		catalogue_get_string("genome symbols", CHROMOSOME));

	fprintf(file, "</%s>\n",
		catalogue_get_string("genome symbols", GENOME));

	fclose(file);

	return true;
}

//are we over some edge? used for cusor setting
int BrainModel::overEdge(const QPoint & origin, const QSize & canvas)
{
	auto port = viewPort();
	auto pixels = QSizeF(
		(double) canvas.width () / port.width (),
		(double) canvas.height() / port.height());

	auto cursor = convertLocation(origin, canvas);

	for(auto i = list<LobeModel>().begin(); i != list<LobeModel>().end(); ++i)
	{
		int edge = (*i)->getEdge(cursor, pixels);

		if(edge != 0)
		{
			return edge;
		}
	}

	return 0;
}

bool BrainModel::beginScale(const QPoint & origin, const QSize & canvas)
{
	auto port = viewPort();
	auto pixels = QSizeF(
		(double) canvas.width () / port.width (),
		(double) canvas.height() / port.height());
	auto cursor = convertLocation(origin, canvas);

	for(auto i = list<LobeModel>().begin(); i != list<LobeModel>().end(); ++i)
	{
		int edge = (*i)->getEdge(cursor, pixels);

		if(edge != 0)
		{
			move = new ScaleCommand(*i, cursor, edge);
			return true;
		}
	}

	return false;
}


QMenu * BrainModel::getContextMenu(QWidget * widget, const QPoint & pos, const QSize & canvas)
{
	QPointF  cursor = convertLocation(pos, canvas);
	QMenu * menu = get_context_menu<LobeModel>(widget, cursor);

	if(!menu)
	{
		get_context_menu<TractModel>(widget, cursor);
	}

	if(menu)
	{
		return menu;
	}

	menu = new QMenu("", widget);

	if(!new_gene)
	{
		QAction * action = menu->addAction("Insert Lobe");
		connect(action, SIGNAL(triggered()), this, SLOT(newLobe()));

		menu->addSeparator();
	}

	for(auto i = list<LobeModel>().begin(); i != list<LobeModel>().end(); ++i)
	{
		(*i)->addVisibilityToggle(menu);
	}

	menu->addSeparator();

	for(auto i = list<TractModel>().begin(); i != list<TractModel>().end(); ++i)
	{
		(*i)->addVisibilityToggle(menu);
	}


	return menu;
}

QString BrainModel::getToolTip(const QPoint & pos, const QSize & canvas)
{
	QPointF  cursor(convertLocation(pos, canvas));
	QString tip = get_tool_tip<LobeModel>(cursor);

	if(tip.isEmpty())
	{
		tip = get_tool_tip<TractModel>(cursor);
	}

	return tip;
}

void BrainModel::onMousePress(const QPoint & pos, const QSize & canvas)
{
	auto cursor = convertLocation(pos, canvas);

	for(auto i = list<LobeModel>().begin(); i != list<LobeModel>().end(); ++i)
	{
		if(contains((*i)->box(), cursor))
		{
			(*i)->onMousePress(cursor);
			return;
		}
	}
}

void BrainModel::stepEvent()
{
	for(auto i = list<LobeModel>().begin(); i != list<LobeModel>().end(); ++i)
	{
		(*i)->interpolate_tick();
	}

	for(auto i = list<LobeModel>().begin(); i != list<LobeModel>().end(); ++i)
	{
		(*i)->process_tick();
	}

	for(auto i = list<LobeModel>().begin(); i != list<LobeModel>().end(); ++i)
	{
		(*i)->advance_time();
	}
}

void BrainModel::draw(QPainter & painter, const QPoint & pos, const QSize & canvas, bool reverse_tracts)
{
	auto port	= viewPort();
	auto cursor = convertLocation(pos, canvas);

	QSizeF pixels((double) canvas.width() / port.width(), (double) canvas.height() / port.height());

	for(auto i = list<LobeModel>().begin(); i != list<LobeModel>().end(); ++i)
	{
		if(contains((*i)->box(), cursor))
		{
			(*i)->preRender(cursor);
			goto render;
		}
	}

	for(auto i = list<TractModel>().begin(); i != list<TractModel>().end(); ++i)
	{
		if(contains((*i)->box(), cursor))
		{
			if((*i)->preRender(cursor, pixels))
			{
				break;
			}
		}
	}

render:

	painter.save();
	painter.translate(-port.left() * pixels.width (),
					  -port.top () * pixels.height());

	for(auto i = const_list<TractModel>().begin(); i != list<TractModel>().end(); ++i)
	{
		if(port.intersects((*i)->box()))
		{
			painter.save();
			(*i)->draw(painter, cursor, pixels, reverse_tracts, 1);
			painter.restore();
		}
	}
	painter.restore();

	for(auto i = list<LobeModel>().begin(); i != list<LobeModel>().end(); ++i)
	{
		if(port.intersects((*i)->box()))
		{
			painter.save();
			(*i)->draw(painter, cursor, port, pixels, false, 1);
			painter.restore();
		}
	}

#if 0
	painter.setPen(QPen(Qt::red));
	painter.drawRect((int) cursor.x() * pixels.width(),
					 (int) cursor.y() * pixels.height(),
					 pixels.width(),
					 pixels.height());
#endif

}
