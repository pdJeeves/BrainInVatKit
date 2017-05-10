#include <cstdio>
#include <genetics.h>
#include <catalogue.h>
#include "lobemodel.h"
#include "tractmodel.h"
#include "lobegene.h"
#include "tractgene.h"
#include "brainmodel.h"
#include <cstring>
#include <QTextStream>
#include <algorithm>

static inline
QPoint __attribute((always_inline)) to_point(const QPointF & x)
{
	return QPoint((int) x.x(), (int) x.y());
}


LobeModel::LobeModel(BrainModel & brain, const QString & name, const LobeData & data)
	:	brain(brain),
		_box(data.position.dimensions.x, data.position.dimensions.y, data.size.dimensions.width, data.size.dimensions.height),
		prev_name(name),
		name(name)
{
	memset(&original, 0, sizeof(original));
	memset(&identity, 0, sizeof(identity));
	lobeConstruct2(&identity, &data, name.toStdString().c_str());
	gene = 0L;
	tract = 0L;
	flags = (lobeFlags) 0L;
	predicted = 0L;
}

void LobeModel::finishLoad()
{
	identity.data.position.dimensions.x		= position().x();
	identity.data.position.dimensions.y		= position().y();

	identity.data.size.dimensions.width		= _box.width();
	identity.data.size.dimensions.height    = _box.height();

	LobeData data = identity.data;

	lobeDestruct(&identity);
	lobeConstruct2(&identity, &data, name.toStdString().c_str());
}

void LobeModel::commit()
{
	finishLoad();

	for(auto i = brain.list<TractModel>().begin(); i != brain.list<TractModel>().end(); ++i)
	{
		if((*i)->isConnected(this))
		{
			(*i)->commit();
		}
	}
}

void LobeModel::save(FILE * file)
{
	memcpy(&original, &identity.data, sizeof(original));
	GeneHeader header;
	memcpy(header.GENE, "GENE", 4);
	memcpy(header.organ, name.toStdString().c_str(), ORGAN_NAME_LENGTH);
	header.bytes = sizeof(original);
	header.type  = gt_Lobe;
	header.switchOnStage = 0;
	header.mutability      = 0;

	ExportGene(file, &header, &original);
}

bool LobeModel::hasChanged() const
{
	return prev_name != name || memcmp(&original, &identity.data, sizeof(identity.data));
}

void LobeModel::toggleVisibility()
{
	flags = static_cast<LobeModel::lobeFlags>(flags ^ HIDDEN);
}

void LobeModel::editGene()
{
	if(!gene)
	{
		gene = new LobeSettings(&brain.window, this);
		gene->show();
	}
}

void LobeModel::addTract()
{
	if(!tract)
	{
		TractData	 data;
		memset(&data	, 0, sizeof(data)	);

		strncpy(data.originLobe, name.toStdString().c_str(), LOBE_NAME_LENGTH);
		data.originLobeLast = length();
		data.minLtw = tw_minWeight + 32;
		data.maxLtw = tw_minWeight;

		tract = new TractModel(brain, QString(""), data);
		if(brain.setNewGene(tract))
		{
			tract->edit_gene(this);
		}
	}
	else
	{
		tract->edit_gene(this);
	}
}

void LobeModel::clearGene(LobeSettings * it)
{
	if(it == gene)
		gene = 0L;
}

void LobeModel::clearTract(TractModel * it)
{
	if(tract == it)
	{
		tract = 0L;
	}
}

void LobeModel::cancelTract(TractModel * it)
{
	if(it == tract)
	{
		tract = 0L;
	}
}

void LobeModel::remove()
{
	brain.remove(this);
}

void LobeModel::addVisibilityToggle(QMenu * contextMenu)
{
	if((flags & HIDDEN) == 0)
	{
		return;
	}

	QString label;
	label.sprintf("Show %s", name.toStdString().c_str());
	QAction * ToggleAction = contextMenu->addAction(label);
	connect(ToggleAction, SIGNAL(triggered()), this, SLOT(toggleVisibility()));
}

QMenu * LobeModel::getContextMenu(QWidget * widget, const QPointF &)
{
	QMenu * contextMenu = new QMenu(widget);

	if(!gene)
	{
		QAction * EditAction = contextMenu->addAction("Edit Gene");
		connect(EditAction, SIGNAL(triggered()), this, SLOT(editGene()));
	}
/*
	if(!graph)
	{
		QAction * GraphAction = contextMenu->addAction("Graph Lobe");
		connect(GraphAction, SIGNAL(triggered()), this, SLOT(graph()));
	}
*/
	QAction * ToggleAction;
	if(flags & HIDDEN)
	{
		ToggleAction = contextMenu->addAction("Show Lobe");
	}
	else
	{
		ToggleAction = contextMenu->addAction("Hide Lobe");
	}

	connect(ToggleAction, SIGNAL(triggered()), this, SLOT(toggleVisibility()));

	QAction * DeleteAction = contextMenu->addAction("Delete Lobe");
	connect(DeleteAction, SIGNAL(triggered()), this, SLOT(remove()));

	contextMenu->addSeparator();

	/*
	for(auto n = neurons(); !n.empty(); n.popFront())
	{
		if(n.box().contains(cursor))
		{

		}
	}
	*/

	if(brain.canAddGene())
	{
		QAction * AddTractAction = contextMenu->addAction("Add Tract");
		connect(AddTractAction, SIGNAL(triggered()), this, SLOT(addTract()));
	}

	for(auto i = brain.list<TractModel>().begin(); i != brain.list<TractModel>().end(); ++i)
	{
		if((*i)->isOriginLobe(this))
		{
			(*i)->addSubmenu(contextMenu->addMenu((*i)->name));
		}
	}

	return contextMenu;
}

QString LobeModel::getToolTip(QPointF cursor)
{
	cursor -= position();
	QString tip;

	int x = cursor.x();
	int y = cursor.y();
	
	float _x = cursor.x() - x;
	float _y = cursor.y() - y;
	
	if(.25 <= _x && _x <= .75
	&& .25 <= _y && _y <= .75)
	{
		QTextStream(&tip) << name << " list";
		tip = (catalogue_get_string(tip.toStdString().c_str(), x + y*width()));
		
		if(tip.isEmpty())
		{
			QTextStream(&tip) << name << " neuron " << x << "x" << y;
		}
	}
	else
	{
		QTextStream(&tip) << name << " " << width() << "x" << height();	
	}
	
	return tip;
}


template<typename T>
T max(T a, T b)
{
	return a > b? a : b;
}

QColor multiplyColor(const QColor & color,
double m0, double m1,  double m2, double m3,
double m4,  double m5, double m6, double m7,
double m8,  double m9, double m10, double m11,
double m12,  double m13, double m14, double m15)
{
	double r = color.red()*m0 + color.green()*m4 + color.blue()*m8 + color.alpha()*m12;
	double g = color.red()*m1 + color.green()*m5 + color.blue()*m9 + color.alpha()*m13;
	double b = color.red()*m2 + color.green()*m6 + color.blue()*m10 + color.alpha()*m14;
	double a = color.red()*m3 + color.green()*m7 + color.blue()*m11 + color.alpha()*m15;

	double max = ::max(::max(r, g), ::max(b, a));

	r = 255 * r / max; r = r < 0? 0 : r;
	b = 255 * b / max; b = b < 0? 0 : b;
	g = 255 * g / max; g = g < 0? 0 : g;
	a = 255 * a / max; a = a < 0? 0 : a;
	return QColor(r, g, b, a);
}

QColor getColor(const QColor & color, double e, double i, double m, double p)
{
#if 0
	return multiplyColor(color,
		1,	p+(e-i)	,i-e, 0,
		m+p,1		,i-e, 0,
		m+p,p+(e-i)	,1	, 0,
		0  ,0		,0	, 1);
#else
	double r = color.redF()   + m + p;
	double g = color.greenF() + e - i + p;
	double b = color.blueF()  + i - e;
	double a = color.alphaF() + m + e + i + p;

	double max = ::max(::max(r, g), ::max(b, a));

	r = 255 * r / max; r = r < 0? 0 : r;
	b = 255 * b / max; b = b < 0? 0 : b;
	g = 255 * g / max; g = g < 0? 0 : g;
	a = 255 * a / max; a = a < 0? 0 : a;
	return QColor(r, g, b, a);
#endif
}

void LobeModel::draw(QPainter & painter, QPointF cursor, const QRectF  & viewport, const QSizeF & pixels, bool selected, int tick)
{
	painter.translate((x() - viewport.left()) * pixels.width(),
					  (y() - viewport.top()) * pixels.height());
	QPen   pen(QBrush(color()), 1, Qt::SolidLine);
	
	if(box().contains(to_point(cursor)))
	{
		pen.setBrush(QBrush(Qt::white));
	}
	else if(flags & HIDDEN)
	{
		return;	
	}

	cursor.setX(cursor.x() - x());
	cursor.setY(cursor.y() - y());

	painter.setPen(QPen(Qt::white));
	if(identity.data.size.dimensions.depth)
	{
		painter.setBrush(QColor(255, 255, 255, 128));
	}
	else
	{
		painter.setBrush(QColor(0, 0, 0, 128));
	}

	QString label;
	QTextStream(&label) << name << " " << width() << "x" << height();
	painter.drawText(0, -2, label);

	if(selected)
	{
		QVector<qreal> dashes;
		int    dash_length = 4;

		dashes << (qreal) dash_length << (qreal) dash_length;

		pen.setDashPattern(dashes);
		pen.setDashOffset(tick % dash_length);
	}

	painter.setPen(pen);
	painter.drawRect(0, 0, pixels.width() * width(), pixels.height() * height());

	if(flags & HIDDEN)
	{
		return;	
	}

	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(color()));

	cursor = QPointF(cursor.x() - x(), cursor.y() - y());

	auto light = highlight.begin();
	for(auto n = neurons(); !n.empty(); n.popFront())
	{
		auto box = n.box();

		if(light != highlight.end() && *light == n.number())
		{
			++light;
			painter.setBrush(QBrush(Qt::white));
		}
		else if(n.prev() == 255)
		{
			painter.setBrush(QBrush(Qt::red));
		}
		else
		{
			painter.setBrush(getColor(color(), n.excitement(), n.inhibition(), n.output(), n.predictive()));
		}
		
		painter.drawRect((int) (box.left  () * pixels.width ()),
						 (int) (box.top   () * pixels.height()),
						 (int) (box.width () * pixels.width ()),
					     (int) (box.height() * pixels.height()));
	}

	highlight.clear();
}

void LobeModel::initialize(const LobeData * data)
{
	lobeConstruct2(&identity, data, name.toStdString().c_str());
}

void LobeModel::onMousePress(QPointF cursor)
{
	cursor -= position();
	int x = cursor.x();
	int y = cursor.y();
	
	float _x = cursor.x() - x;
	float _y = cursor.y() - y;
	
	if(.25 <= _x && _x <= .75
	&& .25 <= _y && _y <= .75)
	{
		NeuronRange(*this, y * width() + x).setExcitement(1.0);		
	}
}

void LobeModel::preRender(QPointF cursor)
{
	cursor -= position();
	int x = cursor.x();
	int y = cursor.y();
	
	float _x = cursor.x() - x;
	float _y = cursor.y() - y;

	if(.25 <= _x && _x <= .75
	&& .25 <= _y && _y <= .75)
	{
		highlight.push_back(y * width() + x);


		for(auto i = brain.list<TractModel>().begin(); i != brain.list<TractModel>().end(); ++i)
		{
			if((*i)->isDataSource(this))
			{
				(*i)->propagateHighlightForward(highlight);
			}
			if((*i)->isOriginLobe(this))
			{
				(*i)->propagateHighlightBackward(highlight);
			}
		}
	}
}


std::vector<uint16_t> LobeModel::incorporateHighlight(std::vector<uint16_t> & light)
{
	std::vector<uint16_t> diff;

	std::sort(light.begin(), light.end());
	std::unique(light.begin(), light.end());

	std::vector<uint16_t> n_h;

	auto i = highlight.begin();
	auto j = light.begin();

	while(i != highlight.end() || j != light.end())
	{
		if(i == highlight.end() || (j != light.end() && *j < *i))
		{
			n_h.push_back(*j);
			diff.push_back(*j);
			++j;
		}
		else if(j == light.end() || (i != highlight.end() && *i < *j))
		{
			n_h.push_back(*i);
			++i;
		}
		else if(*i == *j)
		{
			n_h.push_back(*i);
			++i; ++j;
		}
	}

	highlight = n_h;
	return diff;
}


void LobeModel::propagateHighlightForward(std::vector<uint16_t> & light)
{
	if(light.empty())
	{
		return;
	}

	std::vector<uint16_t> diff = incorporateHighlight(light);

	for(auto i = brain.list<TractModel>().begin(); i != brain.list<TractModel>().end(); ++i)
	{
		if((*i)->isDataSource(this))
		{
			(*i)->propagateHighlightForward(diff);
		}
	}
}

void LobeModel::propagateHighlightBackward(std::vector<uint16_t> & light)
{
	if(light.empty())
	{
		return;
	}

	std::vector<uint16_t> diff = incorporateHighlight(light);

	for(auto i = brain.list<TractModel>().begin(); i != brain.list<TractModel>().end(); ++i)
	{
		if((*i)->isOriginLobe(this))
		{
			(*i)->propagateHighlightBackward(diff);
		}
	}
}


static inline
int __attribute((always_inline)) __attribute((const)) getEdge(int size, float position, float pixels)
{
	int flags = 0;

	position = fabs(position);
	if(position < 1
	&& position * pixels < 5)
	{
		flags |= 0x01;
	}

	position = fabs(size - position);
	if(position < 1
	&& position*pixels < 5)
	{
		flags |= 0x02;
	}

	return flags == 0x03? 0x00 : flags;
}

static inline
int getEdge(const QSize & size, const QPointF & pos, const QPointF & cursorPos, const QSizeF & pixels)
{
	float x = cursorPos.x() - pos.x();
	float y = cursorPos.y() - pos.y();

	if(x < 0			|| y < 0
	|| x > size.width()	|| y > size.height())
	{
		return 0;
	}

	return ::getEdge(size.width(), x, pixels.width()) | (getEdge(size.height(), y, pixels.height()) << 4);
}

int LobeModel::getEdge(QPointF cursorPos, QSizeF pixels)
{
	return ::getEdge(size(), position(), cursorPos, pixels);
}


void LobeModel::interpolate_tick()
{
	lobeInterpolateTick(&identity);
}

void LobeModel::process_tick()
{
	predicted = lobeProcessTick(&identity);
}

void LobeModel::advance_time()
{
	lobeAdvanceTime(&identity, 1);
}
