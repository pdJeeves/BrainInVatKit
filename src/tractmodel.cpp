#include "tractmodel.h"
#include "tractgene.h"
#include <cstring>
#include <vector>
#include <algorithm>
#include <catalogue.h>
#include <cstdio>

QPointF operator*(const QPointF & a, const QSizeF & b)
{
	return QPointF((int) (a.x() * b.width()), (int) (a.y() * b.height()));
}

#define FUZZ 2

bool onLine(const QPointF & cursor, const QPointF & a, const QPointF & b)
{
	if( (a.x() < b.x() && !(a.x() - FUZZ <= cursor.x() && cursor.x() <= b.x() + FUZZ ))
	||  (b.x() < a.x() && !(b.x() - FUZZ <= cursor.x() && cursor.x() <= a.x() + FUZZ ))
	||  (a.y() < b.y() && !(a.y() - FUZZ <= cursor.y() && cursor.y() <= b.y() + FUZZ ))
	||  (b.y() < a.y() && !(b.y() - FUZZ <= cursor.y() && cursor.y() <= a.y() + FUZZ )) )
	{
		return false;
	}

	float dxc = cursor.x() - a.x();
	float dyc = cursor.y() - a.y();

	float dx1 = b.x() - a.x();
	float dy1 = b.y() - a.y();


	float cross = dxc * dy1 - dyc * dx1;

	return fabs(cross) < FUZZ;
}

QPointF TractModel::Dendrite::cellPos(int cell, const LobeModel * lobe) const
{
	return QPointF( cell % lobe->width() + lobe->position().x() + .5,
					cell / lobe->width() + lobe->position().y() + .5);
}

TractModel::TractModel(BrainModel & brain, const QString & name, const TractData & tract)
	: brain(brain),
	  original(tract),
	  prev_name(name),
      name(name)
{
	initialize(&tract);
	flags = (tractFlags) 0L;
	gene = 0L;
	mirror = 0L;
}

static inline
int min(int a, int b)
{
	return a < b? a : b;
}

static inline
int max(int a, int b)
{
	return a > b? a : b;
}


QRect TractModel::box()
{
	LobeModel * origin_lobe;
	LobeModel * data_source;

	int x, y, w, h;

	getLobes(origin_lobe, data_source);

	if(origin_lobe && !data_source)
	{
		data_source = origin_lobe;
	}
	else if(!origin_lobe && data_source)
	{
		origin_lobe = data_source;
	}
	else if(!origin_lobe && !data_source)
	{
		return QRect(256, 256, 256, 256);
	}

	x = min(origin_lobe->x(), data_source->x());
	y = min(origin_lobe->y(), data_source->y());
	w = max(origin_lobe->box().right() + 1, data_source->box().right() + 1);
	h = max(origin_lobe->box().bottom() + 1, data_source->box().bottom() + 1);

	return QRect(QPoint(x, y), QSize(w - x, h - y));
}

bool TractModel::isDataSource(const LobeModel * it) const
{
	return 0 == strncmp(identity.data.dataSource, it->name.toStdString().c_str(), LOBE_NAME_LENGTH);
}

bool TractModel::isOriginLobe(const LobeModel * it) const
{
	return 0 == strncmp(identity.data.originLobe, it->name.toStdString().c_str(), LOBE_NAME_LENGTH);
}

int TractModel::Dendrite::dataSource() const
{
	if(!_mode)
	{
		return tractDataSourceCellFromOriginLobeSynapse(
			&self.identity, dendrite / self.identity.data.originLobeMaxSynapses,
			synapse()) + self.identity.data.dataSourceFirst;
	}

	return _dendrite / self.identity.data.dataSourceMaxSynapses + self.identity.data.dataSourceFirst;
}

int TractModel::Dendrite::originCell() const
{
	if(!_mode)
	{
		return dendrite / self.identity.data.originLobeMaxSynapses + self.identity.data.originLobeFirst;
	}

	return tractOriginLobeCellFromDataSourceSynapse(
		&self.identity, _dendrite / self.identity.data.dataSourceMaxSynapses,
		synapse()) + self.identity.data.originLobeFirst;
}


int TractModel::Dendrite::synapse() const
{
	if(!_mode)
	{
		return dendrite % self.identity.data.originLobeMaxSynapses;
	}
	else
	{
		return _dendrite % self.identity.data.dataSourceMaxSynapses;
	}
}


TractModel::Dendrite TractModel::dendrites() const
{
	return Dendrite(*this);
}

void TractModel::Dendrite::popFront()
{
	if(!_mode)
	{
		do {
			++dendrite;
		} while(!empty() && dataSource() == -1);
		return;
	}

	dendrite = -1;

	do{
		++_dendrite;
		dendrite = tractGetSynapseFromDataSource(&self.identity, _dendrite);
	} while(!empty() && dendrite == -1);
}

bool TractModel::hasChanged() const
{
	return memcmp(&original, &identity.data, sizeof(identity.data)) || prev_name != name;
}

void TractModel::toggleVisibility()
{
	flags = static_cast<TractModel::tractFlags>(flags ^ HIDDEN);
}

void TractModel::edit_gene(LobeModel * it)
{
	gene = new TractSettings(&brain.window, this, it);
	gene->show();
}

void TractModel::editGene()
{
	if(!gene)
	{
		gene = new TractSettings(&brain.window, this);
		gene->show();
	}
}

void TractModel::clearGene(TractSettings * it)
{
	gene = 0L;
}


void TractModel::remove()
{
	brain.remove(this);
}

void TractModel::add_mirror(TractModel * it)
{
	mirror_list.push_back(it);
}

void TractModel::remove_mirror(TractModel * it)
{
	mirror_list.remove(it);
}

void TractModel::commit()
{
	LobeModel * origin_lobe;
	LobeModel * data_source;

	if(!getLobes(origin_lobe, data_source))
	{
		return;
	}


/*
	mirror->remove_mirror(this);

	QString label;
	label.sprintf("%.*s", ORGAN_NAME_LENGTH, identity.data.mirror);

	if(!label.isEmpty())
	{
		for(auto i = brain.list<TractModel>().begin(); i != brain.list<TractModel>().end(); ++i)
		{
			if((*i)->name == label)
			{
				mirror = *i;
				(*i)->add_mirror(this);
				break;
			}
		}
	}*/

	TractData data = identity.data;

	tractDestruct(&identity);
	initialize(&data);
	tractSetOriginLobe(&identity, &origin_lobe->identity);
	tractSetDataSource(&identity, &data_source->identity);
/*
	if(mirror)
	{
		tract_cell_set_mirror(&identity, &mirror->identity);
	}*/
	tractInitialize(&identity);
}

void TractModel::save(FILE * file)
{
	memcpy(&original, &identity.data, sizeof(original));
	GeneHeader header;
	memcpy(header.GENE, "GENE", 4);
	const char * _name = name.toStdString().c_str();
	memcpy(header.organ, _name, sizeof(header.organ));
	header.bytes = sizeof(original);
	header.type  = gt_Tract;
	header.switchOnStage = 0;
	header.mutability      = 0;

	ExportGene(file, &header, &original);
}

void TractModel::addVisibilityToggle(QMenu * contextMenu)
{
	if((flags & HIDDEN) == 0)
	{
		return;
	}

	QAction * ToggleAction = contextMenu->addAction(QString("%1").arg("Show ", name));
	connect(ToggleAction, SIGNAL(triggered()), this, SLOT(toggleVisibility()));
}

void TractModel::addSubmenu(QMenu * contextMenu)
{
	if(!gene)
	{
		QAction * EditAction = contextMenu->addAction("Edit Gene");
		connect(EditAction, SIGNAL(triggered()), this, SLOT(editGene()));
	}

/*	if(!graph)
	{
		QAction * GraphAction = contextMenu->addAction("Graph Tract");
		connect(GraphAction, SIGNAL(triggered()), this, SLOT(graph()));
	} */

	QAction * ToggleAction;
	if(flags & HIDDEN)
	{
		ToggleAction = contextMenu->addAction("Show Tract");
	}
	else
	{
		ToggleAction = contextMenu->addAction("Hide Tract");
	}

	connect(ToggleAction, SIGNAL(triggered()), this, SLOT(toggleVisibility()));

	QAction * DeleteAction = contextMenu->addAction("Delete Tract");
	connect(DeleteAction, SIGNAL(triggered()), this, SLOT(remove()));
}

QMenu * TractModel::getContextMenu(QWidget * widget, const QPointF & cursor)
{
	LobeModel * origin_lobe = 0L;
	LobeModel * data_source = 0L;

	if(!getLobes(origin_lobe, data_source))
	{
		return 0L;
	}

	if(origin_lobe == data_source)
	{
		return 0L;
	}


	QMenu * contextMenu = new QMenu(widget);
	addSubmenu(contextMenu);

	return contextMenu;
}

TractModel::Dendrite TractModel::getDendrite(const QPointF & cursor, const QSizeF & pixels) const
{
	auto syn = dendrites();
	for(; !syn.empty(); syn.popFront())
	{
		if(onLine(cursor * pixels, syn.begin() * pixels, syn.end() * pixels))
		{
			break;
		}
	}

	return syn;
}

QString getToolTip(const QPointF & cursor)
{
	return QString();

/*	auto dendrite = getDendrite(cursor);


	for(auto n = neurons(); !n.empty(); n.popFront())
	{
		if(n.box().contains(cursor))
		{
			QTextStream(&tip) << name << " list";
			tip = (catalogue_get_string(tip.toStdString().c_str(), n.number()));

			if(tip.isEmpty())
			{
				QTextStream(&tip) << name << " neuron " << n.x() << "x" << n.y();
			}

			break;
		}
	}

	if(tip.isEmpty())
	{
		QTextStream(&tip) << name << " " << width() << "x" << height();
	}

	return tip;*/
}


bool TractModel::getLobes(LobeModel *& origin_lobe, LobeModel *& data_source, const QString & origin_lobe_name, const QString & data_source_name) const
{
	origin_lobe = 0L;
	data_source = 0L;

	for(auto i = brain.list<LobeModel>().begin(); i != brain.list<LobeModel>().end(); ++i)
	{
		if(origin_lobe_name == (*i)->name)
		{
			origin_lobe = *i;
		}
		if(data_source_name == (*i)->name)
		{
			data_source = *i;
		}
	}

	return data_source != 0L && origin_lobe != 0L;
}

bool TractModel::getLobes(LobeModel *& origin_lobe, LobeModel *& data_source, const char * origin, const char * source) const
{
	QString origin_lobe_name;
	origin_lobe_name.sprintf("%.*s", LOBE_NAME_LENGTH, origin);

	QString data_source_name;
	data_source_name.sprintf("%.*s", LOBE_NAME_LENGTH, source);

	return getLobes(origin_lobe, data_source, origin_lobe_name, data_source_name);
}

bool TractModel::getLobes(LobeModel *& origin_lobe, LobeModel *& data_source) const
{
	return getLobes(origin_lobe, data_source, identity.data.originLobe, identity.data.dataSource);
}

QColor multiplyColor(const QColor & color,
double m0, double m1,  double m2, double m3,
double m4,  double m5, double m6, double m7,
double m8,  double m9, double m10, double m11,
double m12,  double m13, double m14, double m15);
QColor getColor(const QColor & color, double e, double i, double m, double p);

void TractModel::draw(QPainter & painter, const QPointF & cursor, const QSizeF & pixels, bool selected, int tick)
{
	if(identity.data.flags & 0x06)
	{
		return;
	}

	LobeModel * origin_lobe = 0L;
	LobeModel * data_source = 0L;

	if(!getLobes(origin_lobe, data_source))
	{
		return;
	}

	if(origin_lobe == data_source)
	{
		return;
	}

	if(origin_lobe->isHidden() || data_source->isHidden())
	{
		return;
	}

	QPen   pen(QBrush(origin_lobe->color()), 1, Qt::SolidLine);

	painter.setPen(pen);
	auto light = highlight.begin();
	for(auto syn = Dendrite(*this, 0, selected); !syn.empty(); syn.popFront())
	{
		QPointF originCell = syn.begin();
		QPointF dataSource = syn.end();

//highlighted dendrites...
		bool is_selected = light != highlight.end() && *light == syn.number();

		if(is_selected)
		{
			++light;
			painter.setPen(Qt::white);
		}
		else
		{
			painter.setPen(getColor(origin_lobe->color(), syn.excitation(), syn.inhibition(), syn.prev(), 0));
		}

		painter.drawLine(originCell.x() * pixels.width (),
						 originCell.y() * pixels.height(),
						 dataSource.x() * pixels.width (),
						 dataSource.y() * pixels.height());
	}

	highlight.clear();
}

bool TractModel::preRender(const QPointF & cursor, const QSizeF & pixels)
{
	LobeModel * origin_lobe;
	LobeModel * data_source;

	if(!getLobes(origin_lobe, data_source))
	{
		return false;
	}

	auto dendrite = getDendrite(cursor, pixels);

	if(dendrite.empty())
	{
		return false;
	}

	highlight.push_back(dendrite.number());
	std::vector<uint16_t> n_h;

	n_h.push_back(dendrite.originCell());
	origin_lobe->propagateHighlightForward(n_h);
	data_source->propagateHighlightBackward(n_h);

	return true;
}

void TractModel::propagateHighlightForward(std::vector<uint16_t> & light)
{
	if(light.empty() || identity.data.flags & 0x06)
	{
		return;
	}


	LobeModel * origin_lobe;
	LobeModel * data_source;

	if(!getLobes(origin_lobe, data_source))
	{
		return;
	}

	std::vector<uint16_t> n_h;
	std::vector<uint32_t> additional;

	for(auto i = light.begin(); i != light.end(); ++i)
	{
		for(auto syn = Dendrite(*this, *i - identity.data.dataSourceFirst, true); !syn.empty() && syn.dataSource() == *i; syn.popFront())
		{
			additional.push_back(syn.number());
			n_h.push_back(syn.originCell());
		}
	}

	highlight.insert(highlight.end(), additional.begin(), additional.end());
	std::sort(highlight.begin(), highlight.end());
	std::unique(highlight.begin(), highlight.end());

	origin_lobe->propagateHighlightForward(n_h);
}

void TractModel::propagateHighlightBackward(std::vector<uint16_t> & light)
{
	if(light.empty() || identity.data.flags & 0x06)
	{
		return;
	}

	LobeModel * origin_lobe;
	LobeModel * data_source;

	if(!getLobes(origin_lobe, data_source))
	{
		return;
	}

	std::vector<uint16_t> n_h;
	std::vector<uint32_t> additional;

	for(auto i = light.begin(); i != light.end(); ++i)
	{
		for(auto syn = Dendrite(*this, *i - identity.data.originLobeFirst, false); !syn.empty() && syn.originCell() == *i; syn.popFront())
		{
			additional.push_back(syn.number());
			n_h.push_back(syn.dataSource());
		}
	}

	highlight.insert(highlight.end(), additional.begin(), additional.end());
	std::sort(highlight.begin(), highlight.end());
	std::unique(highlight.begin(), highlight.end());

	data_source->propagateHighlightBackward(n_h);
}


void TractModel::initialize(const TractData * data)
{
	memset(&identity, 0, sizeof(identity));
	memcpy(&(identity.data), data, sizeof(*data));
	memcpy(identity.name, name.toStdString().c_str(), std::min(ORGAN_NAME_LENGTH, name.length()));
}
