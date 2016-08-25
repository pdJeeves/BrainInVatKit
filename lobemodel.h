#ifndef LOBEMODEL_H
#define LOBEMODEL_H

#include "freetures/brain/brain.h"
#include "brainmodel.h"
#include <QObject>
#include <QString>
#include <QPainter>
#include <cstring>
#include <cmath>

class LobeSettings;
class TractSettings;
class TractModel;

class LobeModel : public QObject
{
	Q_OBJECT
public:
	BrainModel	&	brain;

private:
friend class UpdateDataCommand<LobeModel, LobeData>;
friend class MoveCommand;
friend class BrainModel;
friend class TractModel;
	LobeSettings	*	gene;
	TractModel		* tract;
	LobeData		original;
	LobeCell		identity;
	QRect			_box;
	std::vector<uint16_t> highlight;
	int16_t		* predicted;


	enum lobeFlags
	{
		HIDDEN	= 1 << 0
	}				flags;

	QString			prev_name;
public:
	QString			name;


public slots:
	void toggleVisibility();
	void editGene();
	void addTract();
	void remove();

public:
	bool isHidden() const
	{
		return flags & HIDDEN;
	}

	const LobeData & data() const
	{
		return identity.data;
	}

	void clearTract(TractModel *);
	void clearGene(LobeSettings *);
	void cancelTract(TractModel * it);


	static inline
	QSize maxSize()
	{
		return QSize(64, 64);
	}

	inline
	void setName(const char * string)
	{
		name.sprintf("%.16s", string);
	}

	inline
	QColor color() const
	{
		return QColor(identity.data.red, identity.data.green, identity.data.blue, 128);
	}

	inline
	void setColor(QColor color)
	{
		identity.data.red	= color.red();
		identity.data.green = color.green();
		identity.data.blue	= color.blue();
	}

public:
	struct NeuronRange
	{
	private:
		const LobeModel & parent;
		int    cell;

	public:
		explicit NeuronRange(const LobeModel & p, int c)
			: parent(p), cell(c)
		{
		}

		inline
		void popFront()
		{
			++cell;
		}

		inline
		bool empty() const
		{
			return cell >= (parent.width() * parent.height());
		}

		inline
		bool exists() const
		{
			return cell < (parent.identity.data.width * parent.identity.data.height);
		}

		inline
		float excitement() const
		{
			if(!exists()) return 0;
			return parent.identity.excitation[cell] / 255.0;
		}


		float predictive() const
		{
			if(!parent.predicted)
			{
				return 0;
			}



			for(int16_t * ptr = parent.predicted; *ptr != -1; ++ptr)
			{
				if(*ptr / parent.identity.data.depth == cell)
				{
					return 1.0;
				}
			}

			return 0;
		}

		inline
		void setExcitement(float x)
		{
			if(exists()) parent.identity.excitation[cell] = (uint8_t) (x * 255);
		}

		inline
		float inhibition() const
		{
			if(!exists()) return 0;
			return parent.identity.inhibition[cell] / 255.0;
		}

		inline
		float output() const
		{
			if(!exists()) return 0;
			return parent.identity.firing[cell] / 255.0;
		}

		inline
		float prev() const
		{
			if(!exists()) return 0;
			return parent.identity.prev[cell] / 255.0;
		}

		inline
		int activity() const
		{
			if(!exists()) return 0;
			return parent.identity.active_cycle[cell];
		}

		inline
		int number() const
		{
			return cell;
		}

		inline
		QPoint position() const
		{
			return QPoint(x(), y());
		}

		inline
		int x() const
		{
			return cell % parent.width();
		}

		inline
		int y() const
		{
			return cell / parent.width();
		}

		inline
		QRectF box() const
		{
			static const float size   = .5;
			static const float offset = (1 - size)/2;
			static const float scale  = size + offset;

			return QRectF(x() + offset, y() + offset, scale, scale);
		}
	};



public:
	inline
	QPoint	position() const
	{
		return _box.topLeft();
	}

	inline
	int	x() const
	{
		return _box.x();
	}

	inline
	int	y() const
	{
		return _box.y();
	}


	inline
	void setPosition(const QPoint & pos)
	{
		_box = QRect(pos, _box.size());
	}

	inline
	const QRect & box() const
	{
		return _box;
	}

	inline
	void setBox(const QRect & box)
	{
		_box = box;
	}

	inline
	QSize size() const
	{
		return _box.size();
	}

	inline
	int width() const
	{
		return _box.size().width();
	}

	inline
	int height() const
	{
		return _box.size().height();
	}

	inline
	int length() const
	{
		return (_box.width() * _box.height());
	}

	inline
	QPoint cellPositiion(int cell) const
	{
		return QPoint(cell % _box.width(), cell / _box.width());

	}

	int getEdge(QPointF cursorPos, QSizeF pixels);

	static inline
	QPointF neuronDimensions()
	{
		return QPointF(.5, .5);
	}

	static inline
	QPointF neuronOffest()
	{
		return neuronDimensions()/2;
	}

	int getNeuron(QPoint pos)
	{
		return pos.x() + pos.y() * width();
	}

	bool isTemporal() const
	{
		return identity.temporal != 0L;
	}

	NeuronRange neurons() const
	{
		return NeuronRange(*this, 0);
	}

	void commit();

	explicit LobeModel(LobeModel * lobe)
		: LobeModel(lobe->brain, lobe->name, lobe->identity.data)
	{
	}
	explicit LobeModel(BrainModel & brain, const QString & name, const LobeData & data);
	~LobeModel()
	{
		lobe_cell_free(&identity);
	}

	bool hasChanged() const;

	void addVisibilityToggle(QMenu * contextMenu);
	QMenu * getContextMenu(QWidget * widget, const QPointF & pos);

	QString getToolTip(QPointF cursor);
	void draw(QPainter & painter, QPointF cursor, const QRectF  & viewport, const QSizeF & pixels, bool selected, int tick);
	void initialize(const LobeData * data);

	std::vector<uint16_t> incorporateHighlight(std::vector<uint16_t> & );
	void propagateHighlightForward(std::vector<uint16_t> & );
	void propagateHighlightBackward(std::vector<uint16_t> & );

	void onMousePress(QPointF cursor);
	void preRender(QPointF cursor);
	void save(FILE * file);
	void interpolate_tick();
	void process_tick();
	void advance_time();
};

#endif // LOBEMODEL_H
