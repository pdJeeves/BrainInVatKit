#ifndef MODELCOMMAND_H
#define MODELCOMMAND_H
#include <QString>
#include <QRect>
#include <list>
#include <cstring>

class BrainModel;
class LobeModel;
class TractModel;

struct CommandInterface
{
	virtual ~CommandInterface();
	virtual void rollBack()		= 0;
	virtual void rollForward()	= 0;
};

class InsertionCommand : public CommandInterface
{
	std::list<LobeModel  *> & lobes;
	std::list<TractModel *> & tracts;

	std::list<LobeModel  *>  ins_lobes;
	std::list<TractModel *>  ins_tracts;

public:
	explicit InsertionCommand(BrainModel * brain, const std::list<LobeModel *> &, const std::list<TractModel *> &);

	void rollBack();
	void rollForward();
};

template<class T>
class NewCommand : public CommandInterface
{
	std::list<T *> & list;
	T			 * gene;

public:
	explicit NewCommand(std::list<T *> & list, T * _gene)
		: list(list)
	{
		gene = _gene;
	}

	void rollBack()
	{
		list.remove(gene);
	}
	void rollForward()
	{
		list.push_back(gene);
	}
};

class DeletionCommand : public CommandInterface
{
	std::list<LobeModel  *> & lobes;
	std::list<TractModel *> & tracts;

	std::list<LobeModel  *>  del_lobes;
	std::list<TractModel *>  del_tract;

public:
	DeletionCommand(BrainModel * brain, const std::list<LobeModel *> & del_lobes, const std::list<TractModel *> & del_tracts);

	void rollBack();
	void rollForward();
};

struct MouseCommand : public CommandInterface
{
	virtual bool valid() = 0;
	virtual void cancel() = 0;
	virtual void update(const QPointF & pos) = 0;
	virtual ~MouseCommand();
};

class MoveCommand : public MouseCommand
{
	LobeModel * lobes;

	QPoint cursor_start;
	QPoint prev_pos;
	QPoint new_pos;

public:
	MoveCommand(LobeModel *it, const QPointF & pos);

	void update(const QPointF & pos);
	bool valid();
	void cancel();

	void rollBack();
	void rollForward();
};

class ScaleCommand : public MouseCommand
{
	LobeModel * lobe;

	QPointF cursor_start;
	QRect original;
	QRect new_scale;
	int   flags;

public:
	ScaleCommand(LobeModel * lobe, const QPointF & pos, int flags);

	void update(const QPointF & pos);
	bool valid();
	void cancel();

	void rollBack();
	void rollForward();
};

template<class S, class T>
class UpdateDataCommand : public CommandInterface
{
	S * gene;

	QString prev_name;
	QString next_name;

	T prev_data;
	T next_data;

public:
	UpdateDataCommand(S * _gene, QString name, T & data) :
			prev_name(_gene->name),
			next_name(name)
	{
		gene = _gene;

		memcpy(&prev_data, &gene->identity.data, sizeof(T));
		memcpy(&next_data, &data, sizeof(T));
	}

	void rollBack()
	{
		gene->name = prev_name;
		memcpy(&gene->identity.data, &prev_data, sizeof(T));
		gene->commit();
	}

	void rollForward()
	{
		gene->name = next_name;
		memcpy(&gene->identity.data, &next_data, sizeof(T));
		gene->commit();
	}
};


#endif // MODELCOMMAND_H
