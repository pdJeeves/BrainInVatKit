#include <QColorDialog>
#include "lobe.h"
#include "lobegene.h"
#include "ui_lobegene.h"
#include <QDesktopWidget>

LobeSettings::LobeSettings(MainWindow * _ownr, LobeModel * data) :
	QMainWindow(_ownr),
	ui(new Ui::LobeSettings)
{
	ui->setupUi(this);

	ownr     = _ownr;
	original = data;

	ui->ColorDisplay->color.setRgb(original->data().red, original->data().green, original->data().blue);

	ui->lineEdit->setText(original->name);
	ui->depth->setValue(original->data().depth);
	ui->depthVal->setNum(original->data().depth);

	ui->duty_cycle->setValue(original->data().duty_cycle.activity);
	ui->dutyVal->setNum(original->data().duty_cycle.activity);
	ui->period->setValue(original->data().duty_cycle.period);
	ui->periodVal->setNum(original->data().duty_cycle.period);

	ui->activity->setMaximum(original->data().width * original->data().height);

	ui->activity->setValue(original->data().activity);
	ui->activityVal->setNum(original->data().activity);
	ui->max_boost->setValue(original->data().max_boost);
	ui->boostVal->setNum(original->data().max_boost);

	ui->threshold->setValue(original->data().threshold);
	ui->threshVal->setNum(original->data().threshold);
	ui->relax_state->setValue(original->data().relax_state);
	ui->relax_memory->setValue(original->data().relax_prev);

	QObject::connect(ui->CloseButton, SIGNAL(clicked()), this, SLOT(onClosePushed()));
	QObject::connect(ui->SetColor, SIGNAL(clicked()), this, SLOT(onSelectColor()));
	QObject::connect(ui->lineEdit, SIGNAL(editingFinished()), this, SLOT(onTextEdited()));

	QObject::connect(ui->relax_memory,	SIGNAL(sliderMoved(int)), this, SLOT(onRelaxPrev (int)));
	QObject::connect(ui->relax_state,	SIGNAL(sliderMoved(int)), this, SLOT(onRelaxState(int)));

	ui->CloseButton->setEnabled(can_close());

	onRelaxPrev(0);
	onRelaxState(0);


	setGeometry(
	    QStyle::alignedRect(
	        Qt::LeftToRight,
	        Qt::AlignCenter,
	        size(),
	        qApp->desktop()->availableGeometry()
	    )
	);
}

LobeSettings::~LobeSettings()
{
	delete ui;
}

void LobeSettings::onClosePushed()
{
	LobeData gene;

	gene.posx				= original->data().posx;
	gene.posy				= original->data().posy;
	
	gene.red				= ui->ColorDisplay->color.red();
	gene.green				= ui->ColorDisplay->color.green();
	gene.blue				= ui->ColorDisplay->color.blue();

	gene.width				= original->data().width;
	gene.height				= original->data().height;
	gene.depth				= ui->depth->value();
	
	gene.duty_cycle.activity= ui->duty_cycle->value();
	gene.duty_cycle.period	= ui->period->value();
	gene.activity			= ui->activity->value();
	gene.max_boost			= ui->max_boost->value();

	gene.threshold			= ui->threshold->value();
	gene.relax_state		= ui->relax_state->value();
	gene.relax_prev			= ui->relax_memory->value();
	
	original->clearGene(this);
	original->brain.updateData(original, ui->lineEdit->text(), gene);
	close();
}

void LobeSettings::closeEvent(QCloseEvent * event)
{
	original->clearGene(this);
	original->brain.cancelUpdate(original);
	super::closeEvent(event);
}

bool LobeSettings::can_close() const
{
	return ui->ColorDisplay->color != Qt::black && 	ui->ColorDisplay->color != Qt::white && !ui->lineEdit->text().isEmpty() && original->brain.isNameUnique(original, ui->lineEdit->text());

}

void LobeSettings::onTextEdited()
{
	ui->CloseButton->setEnabled(can_close());
}

void LobeSettings::onSelectColor()
{
	QColor b = QColorDialog::getColor(ui->ColorDisplay->color, this, "Select Lobe Color");

	if(b.isValid())
	{
		ui->ColorDisplay->color = b;
		ui->ColorDisplay->repaint();

		ui->CloseButton->setEnabled(can_close());
	}
}

static inline
int __attribute((const)) getRelaxRate(int rate)
{
	double ratio = rate / (rate + 1.0);

	uint8_t max = 255;
	int i = 0;
	while(max != 0)
	{
		max *= ratio;
		++i;
	}

	return i;
}

void LobeSettings::onRelaxPrev(int)
{
	ui->prevVal->setNum(getRelaxRate(ui->relax_memory->value()));
}

void LobeSettings::onRelaxState(int)
{
	ui->stateVal->setNum(getRelaxRate(ui->relax_state->value()));
}
