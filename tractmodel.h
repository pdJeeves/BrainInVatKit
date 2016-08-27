#ifndef TRACTMODEL_H
#define TRACTMODEL_H
#include "lobe.h"
#include "tract.h"
#include "brainmodel.h"
#include "lobemodel.h"
#include <QPainter>
#include <QString>
#include <QObject>

class TractSettings;


class TractModel : public QObject
{
	Q_OBJECT
public:
	explicit TractModel(const TractModel * tract)
		: TractModel(tract->brain, tract->name, tract->identity.data)
	{
	}
	explicit TractModel(BrainModel & brain, const QString & name, const TractData & tract);
	~TractModel()
	{
		tract_cell_free(&identity);
	}

private:
	TractModel * mirror;
	void add_mirror(TractModel *);
	void remove_mirror(TractModel *);

friend class UpdateDataCommand<TractModel, TractData>;
friend class BrainModel;
friend class TractSettings;
	std::list<TractModel*> mirror_list;
	BrainModel & brain;
	TractData	 original;
	TractCell	 identity;
	std::vector<uint32_t> highlight;

	TractSettings * gene;
	
	QString prev_name;

	enum tractFlags
	{
		HIDDEN	= 1 << 0
	}				flags;

public slots:
	void toggleVisibility();
	void editGene();
	void edit_gene(LobeModel * it);
	void remove();
	void save(FILE * file);
	void clearGene(TractSettings * it);

public:
	const TractData & data() const
	{
		return identity.data;
	}

	QString name;
	QRect box();
	
	bool isDataSource(const LobeModel * it) const;
	bool isOriginLobe(const LobeModel * it) const;

	bool getLobes(LobeModel *& origin_lobe, LobeModel *& data_source, const QString & origin_lobe_name, const QString & data_source_name) const;
	bool getLobes(LobeModel *& origin_lobe, LobeModel *& data_source, const char origin[16], const char source[16]) const;
	bool getLobes(LobeModel *& origin_lobe, LobeModel *& data_source) const;

	struct Dendrite
	{
	private:
		const TractModel & self;
		LobeModel * origin_lobe;
		LobeModel * data_source;
		int32_t _dendrite;
		int32_t dendrite;
		bool    _mode;

		QPointF cellPos(int cell, const LobeModel * lobe) const;

	public:
		explicit Dendrite(const TractModel & it, int cell = 0, bool mode = false)
			: self(it)
		{
			it.getLobes(origin_lobe, data_source);
			dendrite = cell * self.identity.data.origin_lobe_max_synapses - 1;
			_dendrite = cell * self.identity.data.data_source_max_synapses - 1;

			_mode = mode;
			if(dendrite < 0)
			{
				dendrite = -1;
			}

			if(_dendrite < 0)
			{
				_dendrite = -1;
			}

			popFront();
		}

		inline
		int exists() const
		{
			return dendrite < (int) self.identity.synapses;
		}

		inline
		bool empty() const
		{
			if(!origin_lobe || !data_source)
			{
				return true;
			}

			if(!_mode)
			{
				return !self.identity.data.data_source_max_synapses || dendrite >= origin_lobe_dens(&self.identity);
			}

			return !self.identity.data.origin_lobe_max_synapses || _dendrite >= data_source_dens(&self.identity);
		}

		int dataSource() const;
		int originCell() const;
		int synapse() const;

		inline
		double strength() const
		{
			if(!exists()) return self.identity.data.min_str;
			return self.identity.strength[dendrite] / 255.0;
		}

		inline
		double stw() const
		{
			if(!exists()) return self.identity.data.min_ltw;
			return self.identity.stw[dendrite] / 128.0 - 1.0;
		}

		inline
		double ltw() const
		{
			if(!exists()) return self.identity.data.max_ltw;
			return self.identity.ltw[dendrite] / 128.0 - 1.0;
		}

		inline
		double suscept() const
		{
			if(!exists()) return 0;
			return self.identity.suscept[dendrite / self.identity.data.origin_lobe_max_synapses] / 255.0;
		}


		inline
		double excitation() const
		{
			if(!exists()) return 0;
			return self.identity.excitation[dendrite / self.identity.data.origin_lobe_max_synapses] / 255.0;
		}

		inline
		double inhibition() const
		{
			if(!exists()) return 0;
			return self.identity.inhibition[dendrite / self.identity.data.origin_lobe_max_synapses] / 255.0;
		}

		inline
		double prev() const
		{
			if(!exists()) return 0;
			return self.identity.prev[dendrite / self.identity.data.origin_lobe_max_synapses] / 255.0;
		}

		void popFront();

		inline
		int number() const
		{
			return dendrite;
		}

		inline
		QPointF begin() const
		{
			return cellPos(originCell(), origin_lobe);
		}

		inline
		QPointF end() const
		{
			return cellPos(dataSource(), data_source);
		}
	};

	Dendrite dendrites() const;
	Dendrite getDendrite(const QPointF & cursor, const QSizeF &pixels) const;

	inline
	bool isConnected(LobeModel * it)
	{
		return isOriginLobe(it) || isDataSource(it);
	}

	void commit();

	bool hasChanged() const;


	void addSubmenu(QMenu * addMenu);
	void addVisibilityToggle(QMenu * contextMenu);
	QMenu * getContextMenu(QWidget * widget, const QPointF & cursor);
	QString getToolTip(const QPointF &)
	{
		return QString();
	}
	void draw(QPainter & painter, const QPointF & cursor, const QSizeF & pixels, bool selected, int tick);
	void initialize(const TractData * data);
	void propagateHighlightForward(std::vector<uint16_t> & light);
	void propagateHighlightBackward(std::vector<uint16_t> & light);
	bool preRender(const QPointF & cursor, const QSizeF & pixels);

};

#endif // TRACTMODEL_H
