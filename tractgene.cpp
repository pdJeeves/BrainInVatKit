#include "tractgene.h"
#include "ui_tractgene.h"
#include "biochemistry/biochemistry.h"
#include <QDesktopWidget>

int get_cycles_for_rate(int x)
{
	double rate = get_leakage_rate(x);

	int cycles = 0;
	uint8_t max = 255;

	while(max *= rate) { ++cycles; }

	return cycles;
}

TractSettings::TractSettings(MainWindow * parent, TractModel * tract, LobeModel * _l) :
QMainWindow(parent),
ui(new Ui::TractSettings)
{
	ui->setupUi(this);

	ownr		= parent;
	original	= tract;
	lobe		= _l;

	LobeModel * origin_lobe;
	LobeModel * data_source;

	tract->getLobes(origin_lobe, data_source);

	ui->tract_name->setText(original->name);

	ui->origin_lobe_first->setValue(original->data().origin_lobe_first);
	ui->min_origin_lobe->setNum(original->data().origin_lobe_first);
	ui->origin_lobe_last->setValue(original->data().origin_lobe_last);
	ui->max_origin_lobe->setNum(original->data().origin_lobe_last);

	ui->origin_lobe_max->setValue(original->data().origin_lobe_max_synapses);
	ui->min_data_source->setNum(original->data().data_source_first);
	ui->data_source_max->setValue(original->data().data_source_max_synapses);
	ui->max_data_source->setNum(original->data().data_source_last);

	if(origin_lobe)
	{
		reset_origin_lobe(original->data().origin_lobe_first, original->data().origin_lobe_last, origin_lobe->length());
	}
	if(data_source)
	{
		reset_data_source(original->data().data_source_first, original->data().data_source_last, data_source->length());
	}

//ignore standard
	if(original->data().flags & 0x10)
	{
		ui->predictivefiring->setChecked(true);
	}
	else if(original->data().flags & 0x08)
	{
		ui->standardfiring->setChecked(true);
	}
	else
	{
		ui->allfiring->setChecked(true);
	}

	ui->origin_lobe_temporal->setChecked(original->data().flags & 0x02);
	ui->data_source_temporal->setChecked(original->data().flags & 0x04);

	ui->min_add->setValue(original->data().min_add);
	ui->min_addVal->setNum(original->data().min_add);
	ui->max_add->setValue(original->data().max_add);
	ui->max_addVal->setNum(original->data().max_add);
	ui->flat->setChecked(original->data().flags & 0x01? Qt::Checked : Qt::Unchecked);

	FlatChecked(original->data().flags & 0x01);


	ui->min_str->setValue(original->data().min_str);
	ui->min_strVal->setNum(original->data().min_str);
	ui->max_str->setValue(original->data().max_str);
	ui->min_strVal->setNum(original->data().max_str);
	ui->gain   ->setValue(original->data().gain);
	ui->gainVal->setNum(original->data().gain);
	ui->lose   ->setValue(original->data().lose);
	ui->loseVal->setNum(original->data().lose);

	ui->min_ltw->setValue(original->data().min_ltw);
	ui->min_ltwVal->setNum(original->data().min_ltw);
	ui->max_ltw->setValue(original->data().max_ltw);
	ui->max_ltwVal->setNum(original->data().max_ltw);
	ui->threshold->setValue(original->data().threshold);
	ui->threshVal->setNum(original->data().threshold);

	ui->relax_suscept->setValue(original->data().relax_suscept);
	ui->relax_state->setValue(original->data().relax_state);
	ui->relax_stw->setValue(original->data().relax_stw);
	ui->relax_ltw->setValue(original->data().relax_ltw);
	ui->relax_str->setValue(original->data().relax_str);

	ui->spread->setValue(original->data().spread);
	ui->spread_val->setNum(original->data().spread);

	QObject::connect(ui->origin_lobe_max, SIGNAL(sliderMoved(int)), this, SLOT(SynapsesChanged(int)));
	QObject::connect(ui->data_source_max, SIGNAL(sliderMoved(int)), this, SLOT(SynapsesChanged(int)));

	QObject::connect(ui->min_add, SIGNAL(sliderMoved(int)), this, SLOT(MinAddChanged(int)));
	QObject::connect(ui->max_add, SIGNAL(sliderMoved(int)), this, SLOT(MaxAddChanged(int)));
	MinAddChanged(0);
	MaxAddChanged(0);

	QObject::connect(ui->min_str, SIGNAL(sliderMoved(int)), this, SLOT(MinStrChanged(int)));
	QObject::connect(ui->max_str, SIGNAL(sliderMoved(int)), this, SLOT(MaxStrChanged(int)));
	MinStrChanged(0);
	MaxStrChanged(0);

	QObject::connect(ui->min_add, SIGNAL(sliderMoved(int)), this, SLOT(MinAddChanged(int)));
	QObject::connect(ui->max_add, SIGNAL(sliderMoved(int)), this, SLOT(MaxAddChanged(int)));
	MinAddChanged(0);
	MaxAddChanged(0);

	QObject::connect(ui->min_ltw, SIGNAL(sliderMoved(int)), this, SLOT(MinLtwChanged(int)));
	QObject::connect(ui->max_ltw, SIGNAL(sliderMoved(int)), this, SLOT(MaxLtwChanged(int)));
	MinLtwChanged(0);
	MaxLtwChanged(0);

	QObject::connect(ui->relax_ltw, SIGNAL(sliderMoved(int)), this, SLOT(RelaxLtwChanged(int)));
	QObject::connect(ui->relax_stw, SIGNAL(sliderMoved(int)), this, SLOT(RelaxStwChanged(int)));
	RelaxLtwChanged(0);
	RelaxStwChanged(0);

	QObject::connect(ui->relax_state, SIGNAL(sliderMoved(int)), this, SLOT(RelaxStateChanged(int)));
	QObject::connect(ui->relax_suscept, SIGNAL(sliderMoved(int)), this, SLOT(RelaxSusceptChanged(int)));
	QObject::connect(ui->relax_str, SIGNAL(sliderMoved(int)), this, SLOT(RelaxStrChanged(int)));
	RelaxStateChanged(0);
	RelaxSusceptChanged(0);
	RelaxStrChanged(0);

	QObject::connect(ui->origin_lobe_first, SIGNAL(sliderMoved(int)), this, SLOT(FirstSourceChanged(int)));
	QObject::connect(ui->origin_lobe_last , SIGNAL(sliderMoved(int)), this, SLOT( LastSourceChanged(int)));
	QObject::connect(ui->data_source_first, SIGNAL(sliderMoved(int)), this, SLOT(FirstDestChanged(int)));
	QObject::connect(ui->data_source_last , SIGNAL(sliderMoved(int)), this, SLOT (LastDestChanged(int)));

	QObject::connect(ui->flat, SIGNAL(toggled(bool)), this, SLOT(FlatChecked(bool)));

	QObject::connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(onClosePushed()));
	QObject::connect(ui->tract_name, SIGNAL(editingFinished()), this, SLOT(onTextEdited()));

	{
	QString origin_lobe = QString().sprintf("%.16s", original->identity.data.origin_lobe);
	QString data_source = QString().sprintf("%.16s", original->identity.data.data_source);

	QStringList lobe_list;

	int src_index = 0;
	int dest_index = 0;
	lobe_list << "<nothing>";

	int j = 1;
	for(auto i = original->brain.list<LobeModel>().begin(); i != original->brain.list<LobeModel>().end(); ++i, ++j)
	{
		if((*i)->name == origin_lobe)
		{
			if(ui->origin_lobe_temporal->isChecked())
			{
				ui->origin_lobe_temporal->setChecked((*i)->isTemporal());
			}
			src_index = j;
		}
		if((*i)->name == data_source)
		{
			if(ui->data_source_temporal->isChecked())
			{
				ui->data_source_temporal->setChecked((*i)->isTemporal());
			}

			setFiring(*i);
			dest_index = j;
		}
		lobe_list << (*i)->name;
	}

	ui->origin_lobe->clear();
	ui->origin_lobe->addItems(lobe_list);
	ui->origin_lobe->setCurrentIndex(src_index);

	ui->data_source->clear();
	ui->data_source->addItems(lobe_list);
	ui->data_source->setCurrentIndex(dest_index);

	ui->closeButton->setEnabled(can_close());
	}

	setGeometry(
	    QStyle::alignedRect(
	        Qt::LeftToRight,
	        Qt::AlignCenter,
	        size(),
	        qApp->desktop()->availableGeometry()
	    )
	);

	QObject::connect(ui->origin_lobe, SIGNAL(currentIndexChanged(int)), this, SLOT(onOriginLobeSelected(int)));
	QObject::connect(ui->data_source, SIGNAL(currentIndexChanged(int)), this, SLOT(onDataSourceSelected(int)));

	tract_list_updated();
}

TractSettings::~TractSettings()
{
	delete ui;
}

void reset_lobe(QSlider * a, QSlider * b, int min, int max, int length)
{
	a->setMinimum(0);

	a->setMaximum(max - 1);

	a->setValue(min);

	b->setMinimum(min + 1);

	b->setMaximum(length);

	b->setValue(max);
}

void TractSettings::reset_origin_lobe(int min, int max, int length)
{
	reset_lobe(ui->origin_lobe_first, ui->origin_lobe_last, min, max, length);
}

void TractSettings::reset_data_source(int min, int max, int length)
{
	reset_lobe(ui->data_source_first, ui->data_source_last, min, max, length);
}

void TractSettings::onOriginLobeSelected(int)
{
	LobeModel * origin_lobe;
	LobeModel * data_source;

	original->getLobes(origin_lobe, data_source, ui->origin_lobe->currentText(), ui->data_source->currentText());

	if(origin_lobe)
	{
		if(ui->origin_lobe_temporal->isChecked())
		{
			ui->origin_lobe_temporal->setChecked(origin_lobe->isTemporal());
		}

		reset_origin_lobe(0, origin_lobe->length(), origin_lobe->length());
	}
	else
	{
		reset_origin_lobe(0, 1, 1);
	}

	ui->closeButton->setEnabled(can_close());
}


void TractSettings::setFiring(LobeModel * it)
{
	bool enable = it->isTemporal();

	if(!enable)
	{
		ui->data_source_standard->setChecked(true);
		ui->standardfiring->setChecked(true);
	}

	ui->data_source_standard->setEnabled(enable);
	ui->data_source_temporal->setEnabled(enable);
	ui->predictivefiring->setEnabled(enable);
	ui->standardfiring->setEnabled(enable);
	ui->allfiring->setEnabled(enable);
}

void TractSettings::onDataSourceSelected(int)
{
	LobeModel * origin_lobe;
	LobeModel * data_source;

	original->getLobes(origin_lobe, data_source, ui->origin_lobe->currentText(), ui->data_source->currentText());

	if(data_source)
	{
		if(ui->data_source_temporal->isChecked())
		{
			ui->data_source_temporal->setChecked(data_source->isTemporal());
		}
		setFiring(data_source);

		reset_data_source(0, data_source->length(), data_source->length());
	}
	else
	{
		reset_data_source(0, 1, 1);
	}

	ui->closeButton->setEnabled(can_close());
}

TractData TractSettings::getData()
{
	TractData gene = original->identity.data;

	const char * temp = ui->origin_lobe->currentText().toStdString().c_str();
	strncpy(gene.origin_lobe, temp, 16);
	temp = ui->data_source->currentText().toStdString().c_str();
	strncpy(gene.data_source, temp, 16);
	temp = ui->mirror->currentText().toStdString().c_str();
	strncpy(gene.mirror,	  temp, 16);

	gene.origin_lobe_first = ui->origin_lobe_first->value();
	gene.origin_lobe_last  = ui->origin_lobe_last->value();
	gene.data_source_first = ui->data_source_first->value();
	gene.data_source_last  = ui->data_source_last->value();

	gene.flags		 	= 0;

	if(ui->flat->isChecked())
	{
		gene.flags |= 0x01;
	}
	if(ui->origin_lobe_temporal->isChecked())
	{
		gene.flags |= 0x02;
	}
	if(ui->data_source_temporal->isChecked())
	{
		gene.flags |= 0x04;
	}
	if(ui->predictivefiring->isChecked())
	{
		gene.flags |= 0x08;
	}
	else if(ui->standardfiring->isChecked())
	{
		gene.flags |= 0x10;
	}

	gene.origin_lobe_max_synapses= ui->origin_lobe_max->value();
	gene.data_source_max_synapses= ui->data_source_max->value();

	gene.min_add 		= ui->min_add->value();
	gene.max_add 		= ui->max_add->value();

	gene.min_str 		= ui->min_str->value();
	gene.max_str 		= ui->max_str->value();
	gene.gain			= ui->gain   ->value();
	gene.lose			= ui->lose   ->value();

	gene.min_ltw 		= ui->min_ltw->value();
	gene.max_ltw 		= ui->max_ltw->value();
	gene.threshold		= ui->threshold->value();

	gene.relax_suscept	= ui->relax_suscept->value();
	gene.relax_state 	= ui->relax_state->value();
	gene.relax_stw		= ui->relax_stw->value();
	gene.relax_ltw		= ui->relax_ltw->value();
	gene.relax_str      = ui->relax_str->value();
	gene.spread			= ui->spread->value();

	return gene;
}

void TractSettings::onClosePushed()
{

	TractData gene = getData();
	original->clearGene(this);
	original->brain.updateData(original, ui->tract_name->text(), gene);

	close();
}

void TractSettings::closeEvent(QCloseEvent * event)
{
	original->clearGene(this);
	original->brain.cancelUpdate(original);
	if(lobe)
	{
		lobe->cancelTract(original);
	}
	super::closeEvent(event);
}


bool TractSettings::can_close() const
{
	LobeModel * origin_lobe;
	LobeModel * data_source;

	original->getLobes(origin_lobe, data_source, ui->origin_lobe->currentText(), ui->data_source->currentText());

	return	origin_lobe
		&&	data_source
		&& !ui->tract_name->text().isEmpty()
		&& original->brain.isNameUnique(original, ui->tract_name->text());
}

void TractSettings::onTextEdited()
{
	ui->closeButton->setEnabled(can_close());
}


static inline
void min_changed(const QSlider * a, QSlider * b)
{
	int min = a->value();
	int max = b->value();
	int value = max;

	if(min > max)
	{
		value = min + 1;
	}
	
	b->setMinimum(min+1);
	b->setValue(value);
}

static inline
void max_changed(QSlider * a, const QSlider * b)
{
	int min = a->value();
	int max = b->value();
	int value = min;

	if(min > max)
	{
		value = max - 1;
	}
	
	a->setMaximum(max - 1);
	a->setValue(value);
}

void TractSettings::FlatChecked(bool enabled)
{
	enabled = !enabled;

	ui->origin_lobe_max->setEnabled(enabled);
	ui->data_source_max->setEnabled(enabled);
	ui->min_add->setEnabled(enabled);
	ui->max_add->setEnabled(enabled);
	ui->max_str->setEnabled(enabled);
	ui->min_str->setEnabled(enabled);
	ui->gain->setEnabled(enabled);
	ui->lose->setEnabled(enabled);
}

void TractSettings::tract_list_updated()
{
	QStringList tract_list;

	TractData gene = getData();

	int mirror_index = 0;
	tract_list << "<nothing>";

	int j = 1;
	for(auto i = original->brain.list<TractModel>().begin(); i != original->brain.list<TractModel>().end(); ++i, ++j)
	{
		if((*i)->name == ui->mirror->currentText())
		{
			mirror_index = j;
		}
		tract_list << (*i)->name;
	}

	ui->mirror->clear();
	ui->mirror->addItems(tract_list);
	ui->mirror->setCurrentIndex(mirror_index);
}

void TractSettings::lobe_list_updated()
{
	LobeModel * origin_lobe;
	LobeModel * data_source;

	original->getLobes(origin_lobe, data_source);

	if(origin_lobe)
	{
		if(ui->origin_lobe_last->value() > origin_lobe->length())
		{
			ui->origin_lobe_last->setValue(origin_lobe->length() - 1);
		}

		ui->origin_lobe_last->setMaximum(origin_lobe->length() - 1);
	}

	if(data_source)
	{
		if(ui->data_source_last->value() > data_source->length())
		{
			ui->data_source_last->setValue(data_source->length());
		}

		ui->data_source_last->setMaximum(data_source->length());
	}

	QStringList lobe_list;

	int src_index = 0;
	int dest_index = 0;
	lobe_list << "<nothing>";

	int j = 1;
	for(auto i = original->brain.list<LobeModel>().begin(); i != original->brain.list<LobeModel>().end(); ++i, ++j)
	{
		if((*i)->name == ui->origin_lobe->currentText())
		{
			if(ui->origin_lobe_temporal->isChecked())
			{
				ui->origin_lobe_temporal->setChecked((*i)->isTemporal());
			}

			dest_index = j;
		}
		if((*i)->name == ui->data_source->currentText())
		{
			if(ui->data_source_temporal->isChecked())
			{
				ui->data_source_temporal->setChecked((*i)->isTemporal());
			}

			setFiring(*i);
			src_index = j;
		}
		lobe_list << (*i)->name;
	}

	ui->origin_lobe->clear();
	ui->origin_lobe->addItems(lobe_list);
	ui->origin_lobe->setCurrentIndex(src_index);

	ui->data_source->clear();
	ui->data_source->addItems(lobe_list);
	ui->data_source->setCurrentIndex(dest_index);
}

void TractSettings::MinAddChanged(int)
{
	min_changed(ui->min_add, ui->max_add);
}

void TractSettings::MaxAddChanged(int)
{
	max_changed(ui->min_add, ui->max_add);
}

void TractSettings::MinStrChanged(int)
{
	min_changed(ui->min_str, ui->max_str); 
}

void TractSettings::MaxStrChanged(int)
{
	max_changed(ui->min_str, ui->max_str);
}

void TractSettings::MinLtwChanged(int)
{
	min_changed(ui->min_ltw, ui->max_ltw);
}

void TractSettings::MaxLtwChanged(int)
{
	max_changed(ui->min_ltw, ui->max_ltw);
}

void TractSettings::RelaxLtwChanged(int)
{
	max_changed(ui->relax_stw, ui->relax_ltw);
	ui->rate_ltw->setNum(get_cycles_for_rate(ui->relax_ltw->value()));
}

void TractSettings::RelaxStwChanged(int)
{
	min_changed(ui->relax_stw, ui->relax_ltw);
	ui->rate_stw->setNum(get_cycles_for_rate(ui->relax_stw->value()));
}

void TractSettings::RelaxStateChanged(int)
{
	ui->rate_state->setNum(get_cycles_for_rate(ui->relax_state->value()));
}

void TractSettings::RelaxSusceptChanged(int)
{
	ui->rate_suscept->setNum(get_cycles_for_rate(ui->relax_suscept->value()));
}

void TractSettings::RelaxStrChanged(int)
{
	ui->rate_str->setNum(get_cycles_for_rate(ui->relax_str->value()));
}

void TractSettings::FirstSourceChanged(int)
{
	min_changed(ui->origin_lobe_first, ui->origin_lobe_last);
#ifdef _tract_list_
	tract_list_updated();
#endif
}

void TractSettings::LastSourceChanged(int)
{
	max_changed(ui->origin_lobe_first, ui->origin_lobe_last);
#ifdef _tract_list_
	tract_list_updated();
#endif
}

void TractSettings::FirstDestChanged(int)
{
	min_changed(ui->data_source_first, ui->data_source_last);
#ifdef _tract_list_
	tract_list_updated();
#endif
}

void TractSettings::LastDestChanged(int)
{
	max_changed(ui->data_source_first, ui->data_source_last);
#ifdef _tract_list_
	tract_list_updated();
#endif
}

void TractSettings::SynapsesChanged(int)
{
#ifdef _tract_list_
	tract_list_updated();
#endif
}



