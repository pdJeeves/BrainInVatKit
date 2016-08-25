#ifndef BRAINMODEL_H
#define BRAINMODEL_H

#include "freetures/brain/brain.h"
#include "freetures/behavior/behavior.h"

#include "freetures/genetics/genome.h"
#include "instinctmodel.h"
#include "modelcommand.h"
#include "mainwindow.h"
#include <QMenu>
#include <QPainter>
#include <QObject>

class LobeModel;
class TractModel;

class BrainModel : QObject
{
	Q_OBJECT
private:

	MouseCommand * move;

	QPointF		last_pos;
	void * new_gene;
	
	std::list<LobeModel*>  lobes;
	std::list<TractModel*> tracts;
	std::vector<InstinctModel*> instincts;

	std::list<LobeModel*>  copied_lobes;
	std::list<TractModel*> copied_tracts;

	template<class T>
	std::list<T *> select(const QRect & selection) const;

	QPointF convertLocation(const QPoint & pos, const QSize & size);

	template<class T>
	bool has_changed() const;
	template<class T>
	std::list<T *> duplicate(const std::list<T *> & list);
	template<class T>
	QString get_tool_tip(const QPointF & cursor)  const;
	template<class T>
	QMenu * get_context_menu(QWidget * widget, const QPointF & cursor);

	std::list<CommandInterface *>			commands;
	std::list<CommandInterface *>::iterator	position;

	void add_command(CommandInterface * cmd);

	static
	bool contains(QRect box, QPointF point)
	{
		return	box.x() <= point.x() && point.x() <= box.x() + box.width()
			&&	box.y() <= point.y() && point.y() <= box.y() + box.height();
	}

public:
	MainWindow   & window;

	~BrainModel();
	void onMousePress(const QPoint & pos, const QSize & size);

public slots:
	void newLobe();

public:
	void stepEvent();

	bool canAddGene() const
	{
		return new_gene == 0L;
	}

	bool setNewGene(void * it)
	{
		if(!new_gene)
		{
			new_gene = it;
			return true;
		}

		return false;
	}

	template<class T>
	std::list<T *> & list();

	template<class T>
	const std::list<T *> & const_list() const;

	bool doesIntersect(const LobeModel *) const;

	bool hasChanged() const;

	template<class T>
	bool isNameUnique(const T * t, const QString & name) const
	{
		for(auto i = const_list<T>().begin(); i != const_list<T>().end(); ++i)
		{
			if(*i != t && (*i)->name == name)
			{
				return false;
			}
		}

		return true;
	}

	QString getToolTip(const QPoint & pos, const QSize & canvas);

	QMenu * getContextMenu(QWidget * widget, const QPoint & pos, const QSize & canvas);
	void draw(QPainter & painter, const QPoint & pos, const QSize & canvas, bool reverse_tracts);



	template<class S, class T>
	void updateData(S * original, QString string, T & data)
	{
		if(!memcmp(&data, &original->data(), sizeof(T)) && original->name == string)
		{
			return;
		}
		else if((void *) new_gene != (void *) original)
		{
			window.add_command(new UpdateDataCommand<S, T>(original, string, data));
		}
		else
		{
			original->name = string;
			original->initialize(&data);
			new_gene = 0L;
			original->commit();
			window.add_command(new NewCommand<S>(list<S>(), original));
		}
	}
	
	template<class S>
	void cancelUpdate(S * original)
	{
		if(new_gene == original)
		{
			delete (S *) new_gene;
			new_gene = 0L;
		}
	}
	
	

	BrainModel(MainWindow & window);

	QRect viewPort(const std::list<LobeModel*> & lobes) const;
	QRect viewPort() const;

	static inline
	QSize maxSize()
	{
		return QSize(255, 255);
	}

	static inline
	int maxNeurons()
	{
		return 2048;
	}

	int totalNeurons() const;

	void add(LobeGene * gene);
	void add(TractGene * gene);
	void add(InstinctGene * gene);

	void remove(LobeModel *);
	void remove(TractModel *);

//are we over some edge? used for cusor setting
	int overEdge(const QPoint & origin, const QSize & canvas);
	bool beginScale(const QPoint & origin, const QSize & canvas);
	bool beginMove(const QPoint & origin, const QSize & canvas);

	void updateMove(const QPoint & origin, const QSize & canvas);
	void cancelMove();
	void commitMove();
	bool save(QString filename);
};

#include "lobemodel.h"
#include "tractmodel.h"

template<class T>
std::list<T *> BrainModel::select(const QRect & selection) const
{
	std::list<T *> temp;

	for(auto i = (const_list<T>().begin()); i != (const_list<T>().end()); ++i)
	{
		if(selection.intersects((*i)->box()))
		{
			temp.push_back(*i);
		}
	}

	return temp;
}

template<class T>
bool BrainModel::has_changed() const
{
	for(auto i = const_list<T>().begin(); i != const_list<T>().end(); ++i)
	{
		if((*i)->hasChanged())
		{
			return true;
		}
	}

	return false;
}



template<class T>
std::list<T *> BrainModel::duplicate(const std::list<T *> & list)
{
	std::list<T *> temp;

	for(auto i = list.begin(); i != list.end(); ++i)
	{
		temp.push_back(new T(*i));

		auto object = (*temp.rbegin());

		for(int j = 2; j < 255; ++j)
		{
			QString name2;
			name2.arg(object->name, QString(' '), QString(j));

			if(isNameUnique<T>(0L, name2))
			{
				object->name = name2;
				break;
			}
		}
	}

	return temp;
}

template<class T>
QMenu * BrainModel::get_context_menu(QWidget * widget, const QPointF & cursor)
{
	QMenu * menu = 0L;

	for(auto i = const_list<T>().begin(); i != const_list<T>().end(); ++i)
	{
		if(contains((*i)->box(), cursor))
		{
			menu = (*i)->getContextMenu(widget, cursor);

			if(menu)
			{
				break;
			}
		}
	}

	return menu;
}

template<class T>
QString BrainModel::get_tool_tip(const QPointF & cursor) const
{
	for(auto i = const_list<T>().begin(); i != const_list<T>().end(); ++i)
	{
		if(contains((*i)->box(), cursor))
		{
			QString temp = (*i)->getToolTip(cursor);

			if(!temp.isEmpty())
			{
				return temp;
			}
		}
	}

	return QString();
}


#endif // BRAINMODEL_H
