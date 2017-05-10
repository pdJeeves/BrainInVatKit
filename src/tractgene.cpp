#include "tractgene.h"
#include "ui_tractsettings.h"
#include <QDesktopWidget>
#include <iostream>

int get_cycles_for_rate(int x)
{
	return std::log(1/256.0) / std::log(x / (x + 1.0));
}

void TractSettings::rangeChanged(QSlider * a, QSlider * b, int width)
{
	float avg = (a->value() + b->value())/2.0;
	a->setFixedWidth(avg * width / b->maximum());
	a->setMaximum(avg + (a->value()+1 == b->value()));
	b->setMinimum(avg);
}



TractSettings::TractSettings(MainWindow * parent, TractModel * original, LobeModel * lobe) :
QMainWindow(parent),
lobe(lobe),
ownr(parent),
original(original),
ui(new Ui::TractSettings)
{
	ui->setupUi(this);

	setLabelWidths();


	ui->tract_name->setMaxLength(ORGAN_NAME_LENGTH);

#define configureMinMaxRange(min, max, sizer) \
	QObject::connect(min, &QSlider::valueChanged, this, [this](int) { rangeChanged(min, max, sizer->width()); });\
	QObject::connect(max, &QSlider::valueChanged, this, [this](int) { rangeChanged(min, max, sizer->width()); });

#define configureRelaxRate(it, label)\
	QObject::connect(it, &QSlider::valueChanged, this, [this](int) { label->setNum(get_cycles_for_rate(it->value())); });\
	label->setNum(get_cycles_for_rate(it->value()));

	configureMinMaxRange(ui->origin_lobe_first, ui->origin_lobe_last, ui->origin_lobe_max);
	configureMinMaxRange(ui->data_source_first, ui->data_source_last, ui->data_source_max);

	configureMinMaxRange(ui->min_add, ui->max_add, ui->spread);
	configureMinMaxRange(ui->min_str, ui->max_str, ui->spread);
	configureMinMaxRange(ui->min_ltw, ui->max_ltw, ui->spread);

	configureMinMaxRange(ui->relax_ltw, ui->relax_stw, ui->relax_str);
	configureRelaxRate(ui->relax_ltw, ui->rate_ltw);
	configureRelaxRate(ui->relax_stw, ui->rate_stw);

	configureRelaxRate(ui->relax_state, ui->rate_state);
	configureRelaxRate(ui->relax_suscept, ui->rate_suscept);
	configureRelaxRate(ui->relax_str, ui->rate_str);

#undef configureMinMaxRange
#undef configureRelaxRate

	QObject::connect(ui->tabs, &QTabWidget::currentChanged, this, &TractSettings::updateSliders);

	LobeModel * origin_lobe;
	LobeModel * data_source;

	original->getLobes(origin_lobe, data_source);

	ui->tract_name->setText(original->name);

	ui->origin_lobe_max->setValue(original->data().originLobeMaxSynapses);
	ui->data_source_max->setValue(original->data().dataSourceMaxSynapses);

	if(origin_lobe)
	{
		reset_origin_lobe(original->data().originLobeFirst, original->data().originLobeLast, origin_lobe->length());
	}
	if(data_source)
	{
		reset_data_source(original->data().dataSourceFirst, original->data().dataSourceLast, data_source->length());
	}

//ignore standard
	if(original->data().flags & tf_SourcePredictive)
	{
		ui->predictivefiring->setChecked(true);
	}
	else if(original->data().flags & tf_SourceStandard)
	{
		ui->standardfiring->setChecked(true);
	}
	else
	{
		ui->allfiring->setChecked(true);
	}

	ui->origin_lobe_temporal->setChecked(original->data().flags & tf_OriginTemporal);
	ui->data_source_temporal->setChecked(original->data().flags & tf_SourceTemporal);

	ui->min_add->setValue(original->data().minAdd);
	ui->max_add->setValue(original->data().maxAdd);
	ui->flat->setChecked(original->data().flags & 0x01? Qt::Checked : Qt::Unchecked);

	FlatChecked(original->data().flags & tf_Flat);


	ui->min_str->setValue(original->data().minStr);
	ui->max_str->setValue(original->data().maxStr);
	ui->gain   ->setValue(original->data().gain);
	ui->lose   ->setValue(original->data().lose);

	ui->min_ltw->setValue(original->data().minLtw);
	ui->max_ltw->setValue(original->data().maxLtw);
	ui->threshold->setValue(original->data().threshold);

	ui->relax_suscept->setValue(original->data().relaxSuscept);
	ui->relax_state->setValue(original->data().relaxState);
	ui->relax_stw->setValue(original->data().relaxStw);
	ui->relax_ltw->setValue(original->data().relaxLtw);
	ui->relax_str->setValue(original->data().relaxStr);

	ui->spread->setValue(original->data().spread);

	QObject::connect(ui->flat, &QRadioButton::toggled, this, &TractSettings::FlatChecked);

	QObject::connect(ui->closeButton, &QPushButton::clicked, this, &TractSettings::onClosePushed);
	QObject::connect(ui->tract_name, &QLineEdit::editingFinished, this, &TractSettings::onTextEdited);

	{
	QString origin_lobe = QString().sprintf("%.*s", LOBE_NAME_LENGTH, original->identity.data.originLobe);
	QString data_source = QString().sprintf("%.*s", LOBE_NAME_LENGTH, original->identity.data.dataSource);

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

void TractSettings::updateSliders(int i)
{
	switch(i)
	{
	case 0:
		rangeChanged(ui->origin_lobe_first, ui->origin_lobe_last, ui->origin_lobe_max->width());
		rangeChanged(ui->data_source_first, ui->data_source_last, ui->data_source_max->width());
		break;
	case 1:
		rangeChanged(ui->min_add, ui->max_add, ui->spread->width());
		rangeChanged(ui->min_str, ui->max_str, ui->spread->width());
		rangeChanged(ui->min_ltw, ui->max_ltw, ui->spread->width());
		break;
	case 2:
		rangeChanged(ui->relax_ltw, ui->relax_stw, ui->rate_state->width());
		break;
	}
}

void TractSettings::setLabelWidths()
{
	QFont font;
	QFontMetrics fm(font);
	int width = fm.width("000");

	ui->min_addVal->setFixedWidth(width);
	ui->max_addVal->setFixedWidth(width);
	ui->threshVal->setFixedWidth(width);

	width = fm.width("0000");

	ui->rate_stw->setFixedWidth(width);
	ui->rate_ltw->setFixedWidth(width);
}

void reset_lobe(QSlider * a, QSlider * b, int min, int max, int length)
{
	a->setMinimum(0);
	a->setMaximum(length-1);
	b->setMinimum(0);
	b->setMaximum(length-1);

	a->setValue(min);
	b->setValue(max-1);

	a->setEnabled(length > 1);
	b->setEnabled(length > 1);
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
		ui->data_source_temporal->setChecked(false);
		ui->standardfiring->setChecked(true);
	}

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

void copyTractString(char * dst, const QString & src, int length)
{
	if(src == "<nothing>")
	{
		memset(dst, 0, length);
	}
	else
	{
		strncpy(dst, src.toStdString().c_str(), length);
	}
}

TractData TractSettings::getData()
{
	TractData gene = original->identity.data;

	copyTractString(gene.originLobe, ui->origin_lobe->currentText(), LOBE_NAME_LENGTH);
	copyTractString(gene.dataSource, ui->data_source->currentText(), LOBE_NAME_LENGTH);
	copyTractString(gene.mirror    , ui->mirror     ->currentText(), ORGAN_NAME_LENGTH);

	gene.originLobeFirst = ui->origin_lobe_first->value();
	gene.originLobeLast  = ui->origin_lobe_last->value()+1;
	gene.dataSourceFirst = ui->data_source_first->value();
	gene.dataSourceLast  = ui->data_source_last->value()+1;

	gene.flags		 	= 0;

	if(ui->flat->isChecked())
	{
		gene.flags |= tf_Flat;
	}
	if(ui->origin_lobe_temporal->isChecked())
	{
		gene.flags |= tf_OriginTemporal;
	}
	if(ui->data_source_temporal->isChecked())
	{
		gene.flags |= tf_SourceTemporal;
	}

	if(ui->allfiring->isChecked())
	{
		gene.flags |= tf_SourcePredictive | tf_SourceStandard;
	}
	else if(ui->predictivefiring->isChecked())
	{
		gene.flags |= tf_SourcePredictive;
	}
	else if(ui->standardfiring->isChecked())
	{
		gene.flags |= tf_SourceStandard;
	}

	gene.originLobeMaxSynapses= ui->origin_lobe_max->value();
	gene.dataSourceMaxSynapses= ui->data_source_max->value();

	gene.minAdd 		= ui->min_add->value();
	gene.maxAdd 		= ui->max_add->value();

	gene.minStr 		= ui->min_str->value();
	gene.maxStr 		= ui->max_str->value();
	gene.gain			= ui->gain   ->value();
	gene.lose			= ui->lose   ->value();

	gene.minLtw 		= ui->min_ltw->value();
	gene.maxLtw 		= ui->max_ltw->value();
	gene.threshold		= ui->threshold->value();

	gene.relaxSuscept	= ui->relax_suscept->value();
	gene.relaxState 	= ui->relax_state->value();
	gene.relaxStw		= ui->relax_stw->value();
	gene.relaxLtw		= ui->relax_ltw->value();
	gene.relaxStr      = ui->relax_str->value();
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
		ui->origin_lobe_last->setMaximum(origin_lobe->length() - 1);
	}

	if(data_source)
	{
		ui->data_source_last->setMaximum(data_source->length()-1);
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
