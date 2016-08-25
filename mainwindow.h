#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "modelcommand.h"
#include <QMouseEvent>
#include <QMainWindow>
#include <QMenu>

class BrainModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
typedef QMainWindow super;

	Q_OBJECT

	bool reverse_tracts;
	BrainModel * brain;
	int state;

	QRect prev_selection;
	QRect selection;
	QPoint last_pos;
	QSize  last_size;

	QPoint origin;
	QPoint final;

	std::list<CommandInterface *>			commands;
	std::list<CommandInterface *>::iterator	position;

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void add_command(CommandInterface * cmd);

public slots:
	void closeEvent(QCloseEvent * event);

	void DocumentNew();
	void DocumentOpen();
	void DocumentSave();
	void DocumentSaveAs();
	void DocumentClose();

	void EditUndo();
	void EditRedo();

	void EditCopy();
	void EditCut();
	void EditPaste();
	void EditDelete();

	void grabKeyEvent();
	void selectKeyEvent();
	void scaleKeyEvent();
	void stepEvent();

//recieved from Brain View;
public:
	void keyPressEvent		(QKeyEvent *e);

	void onMousePress		(const QPoint & pos, const QSize & size, Qt::MouseButton button);
	void onMouseRelease		(const QPoint & pos, const QSize & size, Qt::MouseButton button);
	void onMouseDoubleClick	(const QPoint & pos, const QSize & size, Qt::MouseButton button);
	void onMouseMoveEvent	(const QPoint & pos, const QSize & size, Qt::MouseButton button);

	void draw				(QPainter & painter, const QPoint & pos, const QSize & size);
	QString getToolTip		(const QPoint & pos, QSize size);
	QMenu * showContextMenu	(QWidget * widget, const QPoint & pos, const QSize & size);

private:
	bool document_save();
	bool document_close();

	QString	Filename;

	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
