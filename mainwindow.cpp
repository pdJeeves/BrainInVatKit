#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopWidget>
#include "lobemodel.h"
#include "tractmodel.h"
#include "freetures/genetics/gen_range.h"

#include "brainmodel.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->actionNew,		SIGNAL(triggered()), this, SLOT(DocumentNew()));
	connect(ui->actionOpen,		SIGNAL(triggered()), this, SLOT(DocumentOpen()));
	connect(ui->actionSave,		SIGNAL(triggered()), this, SLOT(DocumentSave()));
	connect(ui->actionSaveAs,	SIGNAL(triggered()), this, SLOT(DocumentSaveAs()));
	connect(ui->actionClose,	SIGNAL(triggered()), this, SLOT(DocumentClose()));
	connect(ui->actionUndo,		SIGNAL(triggered()), this, SLOT(EditUndo()));
	connect(ui->actionRedo,		SIGNAL(triggered()), this, SLOT(EditRedo()));
	connect(ui->actionCopy,		SIGNAL(triggered()), this, SLOT(EditCopy()));
	connect(ui->actionCut,		SIGNAL(triggered()), this, SLOT(EditCut()));
	connect(ui->actionPaste,	SIGNAL(triggered()), this, SLOT(EditPaste()));
	connect(ui->actionDelete,	SIGNAL(triggered()), this, SLOT(EditDelete()));

	connect(ui->actionGrab,		SIGNAL(triggered()), this, SLOT(grabKeyEvent()));
	connect(ui->actionSelect,	SIGNAL(triggered()), this, SLOT(selectKeyEvent()));
	connect(ui->actionScale,	SIGNAL(triggered()), this, SLOT(scaleKeyEvent()));
	connect(ui->actionStep,		SIGNAL(triggered()), this, SLOT(stepEvent()));

	ui->actionUndo->setEnabled(false);
	ui->actionRedo->setEnabled(false);
	ui->actionCopy->setEnabled(false);
	ui->actionCut->setEnabled(false);
	ui->actionPaste->setEnabled(false);
	ui->actionDelete->setEnabled(false);

	ui->brainView->setOwner(this);
	position = commands.end();

	brain = 0L;
	state = 0L;

	setGeometry(
	    QStyle::alignedRect(
	        Qt::LeftToRight,
	        Qt::AlignCenter,
	        size(),
	        qApp->desktop()->availableGeometry()
	    )
	);

	reverse_tracts = false;
}

MainWindow::~MainWindow()
{
	delete ui;

}

bool MainWindow::document_close()
{
	if(!brain)
	{
		return true;
	}

	if(brain->hasChanged())
	{
		QMessageBox msgBox;
		msgBox.setText("The genome has been modified.");
		msgBox.setInformativeText("Do you want to save your changes?");
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();

		switch(ret)
		{
		case QMessageBox::Cancel:
			return false;
		case QMessageBox::Save:
			DocumentSave();
			break;
		case QMessageBox::Discard:
			break;
		}
	}

	Filename.clear();
	delete brain;
	brain = 0L;
	for(auto i = commands.begin(); i != commands.end(); ++i)
	{
		delete *i;
	}

	commands.clear();

	return true;
}

void MainWindow::grabKeyEvent()
{
	if(!brain || state != 0) { return; }

	state = 'g';
}

void MainWindow::stepEvent()
{
	if(!brain) return;
	brain->stepEvent();
}

void MainWindow::selectKeyEvent()
{
	if(!brain || state != 0) { return; }

	state = 'b';
	setCursor(Qt::CrossCursor);
	origin = last_pos;
}

void MainWindow::scaleKeyEvent()
{
	if(!brain || state != 0) { return; }

	state = 's';
}


void MainWindow::keyPressEvent		(QKeyEvent *e)
{
	if(!brain) { return; }

	if(e->key() == Qt::Key_Escape && state != 0)
	{
		brain->cancelMove();
		setCursor(Qt::ArrowCursor);
		selection = prev_selection;
		state = 0;
	}

	if(e->key() == Qt::Key_R)
	{
		reverse_tracts = !reverse_tracts;
	}

}

void MainWindow::onMousePress		(const QPoint & pos, const QSize & size, Qt::MouseButton button)
{
	if(!brain)
	{
		return;
	}

	last_pos  = pos;
	last_size = size;

	if(button == Qt::LeftButton)
	{
		if(state == 'b')
		{
			state = 0;
			prev_selection = selection;
		}
		else if(state == 's')
		{
			if(brain->beginScale(last_pos, last_size))
			{
				state = 'S';

			}
		}
		else if(state == 'g')
		{
			if(brain->beginMove(last_pos, last_size))
			{
				state = 'G';
				setCursor(Qt::SizeAllCursor);
			}
		}
		else
		{
			brain->onMousePress(pos, size);
		}
	}

	ui->brainView->repaint();
}

void MainWindow::onMouseRelease		(const QPoint & pos, const QSize & size, Qt::MouseButton button)
{
	if(!brain)
	{
		return;
	}

	last_pos  = pos;
	last_size = size;

	if(state == 'S' || state == 'G')
	{
		setCursor(Qt::ArrowCursor);
		brain->commitMove();
		state = 0;
	}

	ui->brainView->repaint();
}

void MainWindow::onMouseDoubleClick	(const QPoint & pos, const QSize & size, Qt::MouseButton button)
{
}

void MainWindow::onMouseMoveEvent	(const QPoint & pos, const QSize & size, Qt::MouseButton button)
{
	last_pos = pos;
	last_size = size;

	if(!brain)
	{
		return;
	}

	if(state == 'G' || state == 'S')
	{
		brain->updateMove(last_pos, last_size);
	}

	if(state == 's')
	{
		int edge = brain->overEdge(last_pos, last_size);

		switch(edge)
		{
		default:
			setCursor(Qt::ArrowCursor);
			break;
		case 0x01:
		case 0x02:
			setCursor(Qt::SizeHorCursor);
			break;
		case 0x10:
		case 0x20:
			setCursor(Qt::SizeVerCursor);
			break;
		case 0x11:
		case 0x22:
			setCursor(Qt::SizeFDiagCursor);
			break;
		case 0x12:
		case 0x21:
			setCursor(Qt::SizeBDiagCursor);
			break;
		}
	}

	if(state == 'b')
	{
		final = pos;
		int x = origin.x();
		int y = origin.y();
		int w = final.x();
		int h = final.y();

		if(h < y)
		{
			int t = h;
			h = y;
			y = t;
		}

		if(w < x)
		{
			int t = w;
			w = x;
			x = t;
		}

		selection = QRect(QPoint(x, y), QSize(w - x, h - y));
	}

	ui->brainView->repaint();
}

void MainWindow::closeEvent(QCloseEvent * event)
{
	if(document_close())
	{
		super::closeEvent(event);
	}
}


void MainWindow::DocumentNew()
{
	if(document_close())
	{
		brain = new BrainModel(*this);
	}
}


void MainWindow::DocumentOpen()
{
	if(!document_close())
	{
		return;
	}

	brain = new BrainModel(*this);
	QString file = QFileDialog::getOpenFileName(this, tr("Open Genome File..."), "", tr("Genetics Files (*.gno)"));
	if(file.length() == 0)
	{
		return;
	}

	Filename = file;

	struct GeneticHandle handle;
	QByteArray ba = file.toLatin1();
    const char *c_str2 = ba.data();
	if(!genetic_handle_create(&handle, c_str2))
	{
		return;
	}

	ChromosomeRange chromosomes;
	chrm_range_create(&chromosomes, &handle);

	GeneRange genes;

	while(chrm_range_pop_front(&chromosomes))
	{
		gene_range_initialize(&genes, &chromosomes);

		while(gene_range_pop_front(&genes))
		{
			if(genes.header->type == LobeType)
			{
				brain->add((LobeGene *) (genes.data));
			}
			else if(genes.header->type == TractType)
			{
				brain->add((TractGene *) (genes.data));
			}
			else if(genes.header->type == InstinctType)
			{
//				brain->add((InstinctGene *) (genes.data));
			}
		}
	}

	genetic_handle_free(&handle);

	for(auto i = brain->list<LobeModel>().begin(); i != brain->list<LobeModel>().end(); ++i)
	{
		(*i)->commit();
	}

	for(auto i = brain->list<TractModel>().begin(); i != brain->list<TractModel>().end(); ++i)
	{
		(*i)->commit();
	}
}


void MainWindow::DocumentSave()
{
	if(!brain)
	{
		return;
	}

	if(!brain->hasChanged())
	{
		return;
	}

	if(Filename.isEmpty() == 0)
	{
		DocumentSaveAs();
	}
	else
	{
		document_save();
	}
}

bool MainWindow::document_save()
{
	if(!brain || Filename.isEmpty())
		return false;

	return brain->save(Filename);
}

void MainWindow::DocumentSaveAs()
{
	if(!brain)
	{
		return;
	}

	QString file = QFileDialog::getSaveFileName(this, tr("Save Genome As..."), "", tr("Genetics Files (*.gno)"));
	if(file.length() == 0)
	{
		return;
	}
	else
	{
		Filename = file;
		document_save();
	}
}

//slots need to be void
void MainWindow::DocumentClose()
{
	document_close();
}

void MainWindow::EditUndo()
{
	ui->actionUndo->setEnabled(position != commands.begin());
	ui->actionRedo->setEnabled(true);

	(*position)->rollBack();
	--position;
}

void MainWindow::EditRedo()
{
	++position;
	(*position)->rollForward();

	ui->actionUndo->setEnabled(true);
	ui->actionRedo->setEnabled(position != --commands.end());
}


void MainWindow::add_command(CommandInterface * cmd)
{
	if(position != --commands.end())
	{
		for(auto i = ++position; i != commands.end(); ++i)
		{
			delete *i;
		}

		commands.erase(position, commands.end());
	}

	commands.push_back(cmd);
	position = --commands.end();
	(*position)->rollForward();

	ui->actionUndo->setEnabled(true);
	ui->actionRedo->setEnabled(false);
}


void MainWindow::EditCopy()
{
//	if(brain) brain->copy(selection, ui->brainView->getSize());
}

void MainWindow::EditCut()
{
	EditCopy();
	EditDelete();
}

void MainWindow::EditPaste()
{
//	if(brain) brain->paste(ui->brainView->getPos(), ui->brainView->getSize());
}

void MainWindow::EditDelete()
{
//	if(brain) brain->remove(selection, ui->brainView->getSize());
}


void	MainWindow::draw		(QPainter & painter, const QPoint & pos, const QSize & size)
{
	last_pos	= pos;
	last_size	= size;

	if(brain)
	{
		brain->draw(painter, pos, size, reverse_tracts);
	}
}

QString	MainWindow::getToolTip	(const QPoint &pos, QSize size)
{
	if(brain)
		return brain->getToolTip(pos, size);

	return "";
}

QMenu * MainWindow::showContextMenu	(QWidget * widget, const QPoint & pos, const QSize & size)
{
	if(brain)
		return brain->getContextMenu(widget, pos, size);

	return 0L;
}
