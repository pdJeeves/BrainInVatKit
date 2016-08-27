/********************************************************************************
** Form generated from reading UI file 'tractgene.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACTGENE_H
#define UI_TRACTGENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TractSettings
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QFormLayout *formLayout;
    QLabel *tractName;
    QLineEdit *tract_name;
    QLabel *Mirrors;
    QComboBox *mirror;
    QTabWidget *tabs;
    QWidget *tab1;
    QGridLayout *gridLayout_2;
    QLabel *origin_lobe_conn;
    QComboBox *data_source;
    QLabel *label_6;
    QLabel *max_origin_lobe;
    QLabel *DataSource;
    QLabel *min_data_source;
    QSlider *data_source_last;
    QSlider *origin_lobe_first;
    QSlider *origin_lobe_max;
    QFrame *line;
    QLabel *label_8;
    QSlider *data_source_first;
    QLabel *label_26;
    QLabel *min_origin_lobe;
    QLabel *label_9;
    QLabel *max_data_source;
    QLabel *OriginLobe;
    QSlider *data_source_max;
    QSlider *origin_lobe_last;
    QComboBox *origin_lobe;
    QLabel *label_5;
    QLabel *label_27;
    QLabel *data_src_conn;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_5;
    QLabel *min_strVal;
    QSlider *min_str;
    QLabel *max_strVal;
    QSlider *max_ltw;
    QLabel *label_14;
    QSlider *min_ltw;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *min_ltwVal;
    QSlider *max_add;
    QLabel *label_13;
    QLabel *min_addVal;
    QLabel *max_addVal;
    QLabel *max_ltwVal;
    QSlider *min_add;
    QSlider *max_str;
    QLabel *label_16;
    QLabel *label_15;
    QLabel *label;
    QSlider *spread;
    QLabel *spread_val;
    QSpacerItem *verticalSpacer_2;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout;
    QLabel *Lose;
    QLabel *Gain;
    QSlider *lose;
    QSlider *gain;
    QLabel *label_2;
    QSlider *threshold;
    QLabel *threshVal;
    QLabel *gainVal;
    QLabel *loseVal;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QSlider *relax_stw;
    QSlider *relax_state;
    QLabel *rate_ltw;
    QLabel *rate_state;
    QLabel *label_10;
    QLabel *rate_stw;
    QLabel *label_11;
    QSlider *relax_suscept;
    QLabel *label_12;
    QLabel *rate_suscept;
    QSlider *relax_ltw;
    QLabel *label_3;
    QLabel *label_7;
    QSlider *relax_str;
    QLabel *rate_str;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton;
    QRadioButton *flat;
    QFrame *line_2;
    QRadioButton *allfiring;
    QRadioButton *standardfiring;
    QRadioButton *predictivefiring;
    QFrame *line_4;
    QRadioButton *origin_lobe_standard;
    QRadioButton *origin_lobe_temporal;
    QFrame *line_3;
    QRadioButton *data_source_standard;
    QRadioButton *data_source_temporal;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButton;
    QPushButton *closeButton;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup_3;
    QButtonGroup *buttonGroup_4;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *TractSettings)
    {
        if (TractSettings->objectName().isEmpty())
            TractSettings->setObjectName(QStringLiteral("TractSettings"));
        TractSettings->resize(379, 444);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TractSettings->sizePolicy().hasHeightForWidth());
        TractSettings->setSizePolicy(sizePolicy);
        TractSettings->setMinimumSize(QSize(379, 0));
        centralwidget = new QWidget(TractSettings);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        tractName = new QLabel(centralwidget);
        tractName->setObjectName(QStringLiteral("tractName"));

        formLayout->setWidget(0, QFormLayout::LabelRole, tractName);

        tract_name = new QLineEdit(centralwidget);
        tract_name->setObjectName(QStringLiteral("tract_name"));

        formLayout->setWidget(0, QFormLayout::FieldRole, tract_name);

        Mirrors = new QLabel(centralwidget);
        Mirrors->setObjectName(QStringLiteral("Mirrors"));

        formLayout->setWidget(1, QFormLayout::LabelRole, Mirrors);

        mirror = new QComboBox(centralwidget);
        mirror->setObjectName(QStringLiteral("mirror"));

        formLayout->setWidget(1, QFormLayout::FieldRole, mirror);


        verticalLayout_4->addLayout(formLayout);

        tabs = new QTabWidget(centralwidget);
        tabs->setObjectName(QStringLiteral("tabs"));
        tab1 = new QWidget();
        tab1->setObjectName(QStringLiteral("tab1"));
        gridLayout_2 = new QGridLayout(tab1);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        origin_lobe_conn = new QLabel(tab1);
        origin_lobe_conn->setObjectName(QStringLiteral("origin_lobe_conn"));

        gridLayout_2->addWidget(origin_lobe_conn, 3, 3, 1, 1);

        data_source = new QComboBox(tab1);
        data_source->setObjectName(QStringLiteral("data_source"));

        gridLayout_2->addWidget(data_source, 5, 1, 1, 3);

        label_6 = new QLabel(tab1);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        max_origin_lobe = new QLabel(tab1);
        max_origin_lobe->setObjectName(QStringLiteral("max_origin_lobe"));

        gridLayout_2->addWidget(max_origin_lobe, 2, 3, 1, 1);

        DataSource = new QLabel(tab1);
        DataSource->setObjectName(QStringLiteral("DataSource"));

        gridLayout_2->addWidget(DataSource, 5, 0, 1, 1);

        min_data_source = new QLabel(tab1);
        min_data_source->setObjectName(QStringLiteral("min_data_source"));

        gridLayout_2->addWidget(min_data_source, 6, 3, 1, 1);

        data_source_last = new QSlider(tab1);
        data_source_last->setObjectName(QStringLiteral("data_source_last"));
        data_source_last->setMinimum(1);
        data_source_last->setMaximum(1);
        data_source_last->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(data_source_last, 7, 2, 1, 1);

        origin_lobe_first = new QSlider(tab1);
        origin_lobe_first->setObjectName(QStringLiteral("origin_lobe_first"));
        origin_lobe_first->setMaximum(1);
        origin_lobe_first->setValue(0);
        origin_lobe_first->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(origin_lobe_first, 1, 2, 1, 1);

        origin_lobe_max = new QSlider(tab1);
        origin_lobe_max->setObjectName(QStringLiteral("origin_lobe_max"));
        origin_lobe_max->setMinimum(1);
        origin_lobe_max->setMaximum(15);
        origin_lobe_max->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(origin_lobe_max, 3, 2, 1, 1);

        line = new QFrame(tab1);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line, 4, 0, 1, 4);

        label_8 = new QLabel(tab1);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 6, 0, 1, 1);

        data_source_first = new QSlider(tab1);
        data_source_first->setObjectName(QStringLiteral("data_source_first"));
        data_source_first->setMaximum(1);
        data_source_first->setValue(0);
        data_source_first->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(data_source_first, 6, 2, 1, 1);

        label_26 = new QLabel(tab1);
        label_26->setObjectName(QStringLiteral("label_26"));

        gridLayout_2->addWidget(label_26, 3, 0, 1, 1);

        min_origin_lobe = new QLabel(tab1);
        min_origin_lobe->setObjectName(QStringLiteral("min_origin_lobe"));

        gridLayout_2->addWidget(min_origin_lobe, 1, 3, 1, 1);

        label_9 = new QLabel(tab1);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 7, 0, 1, 1);

        max_data_source = new QLabel(tab1);
        max_data_source->setObjectName(QStringLiteral("max_data_source"));

        gridLayout_2->addWidget(max_data_source, 7, 3, 1, 1);

        OriginLobe = new QLabel(tab1);
        OriginLobe->setObjectName(QStringLiteral("OriginLobe"));

        gridLayout_2->addWidget(OriginLobe, 0, 0, 1, 1);

        data_source_max = new QSlider(tab1);
        data_source_max->setObjectName(QStringLiteral("data_source_max"));
        data_source_max->setMinimum(1);
        data_source_max->setMaximum(15);
        data_source_max->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(data_source_max, 8, 2, 1, 1);

        origin_lobe_last = new QSlider(tab1);
        origin_lobe_last->setObjectName(QStringLiteral("origin_lobe_last"));
        origin_lobe_last->setMinimum(1);
        origin_lobe_last->setMaximum(1);
        origin_lobe_last->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(origin_lobe_last, 2, 2, 1, 1);

        origin_lobe = new QComboBox(tab1);
        origin_lobe->setObjectName(QStringLiteral("origin_lobe"));

        gridLayout_2->addWidget(origin_lobe, 0, 1, 1, 3);

        label_5 = new QLabel(tab1);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        label_27 = new QLabel(tab1);
        label_27->setObjectName(QStringLiteral("label_27"));

        gridLayout_2->addWidget(label_27, 8, 0, 1, 1);

        data_src_conn = new QLabel(tab1);
        data_src_conn->setObjectName(QStringLiteral("data_src_conn"));

        gridLayout_2->addWidget(data_src_conn, 8, 3, 1, 1);

        tabs->addTab(tab1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_2 = new QVBoxLayout(tab_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_4 = new QGroupBox(tab_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_5 = new QGridLayout(groupBox_4);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        min_strVal = new QLabel(groupBox_4);
        min_strVal->setObjectName(QStringLiteral("min_strVal"));

        gridLayout_5->addWidget(min_strVal, 2, 3, 1, 1);

        min_str = new QSlider(groupBox_4);
        min_str->setObjectName(QStringLiteral("min_str"));
        min_str->setMinimum(0);
        min_str->setMaximum(255);
        min_str->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(min_str, 2, 2, 1, 1);

        max_strVal = new QLabel(groupBox_4);
        max_strVal->setObjectName(QStringLiteral("max_strVal"));

        gridLayout_5->addWidget(max_strVal, 3, 3, 1, 1);

        max_ltw = new QSlider(groupBox_4);
        max_ltw->setObjectName(QStringLiteral("max_ltw"));
        max_ltw->setMinimum(0);
        max_ltw->setMaximum(128);
        max_ltw->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(max_ltw, 5, 2, 1, 1);

        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_5->addWidget(label_14, 5, 0, 1, 1);

        min_ltw = new QSlider(groupBox_4);
        min_ltw->setObjectName(QStringLiteral("min_ltw"));
        min_ltw->setMinimum(0);
        min_ltw->setMaximum(128);
        min_ltw->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(min_ltw, 4, 2, 1, 1);

        label_17 = new QLabel(groupBox_4);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_5->addWidget(label_17, 1, 0, 1, 1);

        label_18 = new QLabel(groupBox_4);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_5->addWidget(label_18, 0, 0, 1, 1);

        min_ltwVal = new QLabel(groupBox_4);
        min_ltwVal->setObjectName(QStringLiteral("min_ltwVal"));

        gridLayout_5->addWidget(min_ltwVal, 4, 3, 1, 1);

        max_add = new QSlider(groupBox_4);
        max_add->setObjectName(QStringLiteral("max_add"));
        max_add->setMinimum(2);
        max_add->setMaximum(15);
        max_add->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(max_add, 1, 2, 1, 1);

        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_5->addWidget(label_13, 4, 0, 1, 1);

        min_addVal = new QLabel(groupBox_4);
        min_addVal->setObjectName(QStringLiteral("min_addVal"));

        gridLayout_5->addWidget(min_addVal, 0, 3, 1, 1);

        max_addVal = new QLabel(groupBox_4);
        max_addVal->setObjectName(QStringLiteral("max_addVal"));

        gridLayout_5->addWidget(max_addVal, 1, 3, 1, 1);

        max_ltwVal = new QLabel(groupBox_4);
        max_ltwVal->setObjectName(QStringLiteral("max_ltwVal"));

        gridLayout_5->addWidget(max_ltwVal, 5, 3, 1, 1);

        min_add = new QSlider(groupBox_4);
        min_add->setObjectName(QStringLiteral("min_add"));
        min_add->setMinimum(1);
        min_add->setMaximum(15);
        min_add->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(min_add, 0, 2, 1, 1);

        max_str = new QSlider(groupBox_4);
        max_str->setObjectName(QStringLiteral("max_str"));
        max_str->setMaximum(255);
        max_str->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(max_str, 3, 2, 1, 1);

        label_16 = new QLabel(groupBox_4);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_5->addWidget(label_16, 3, 0, 1, 1);

        label_15 = new QLabel(groupBox_4);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_5->addWidget(label_15, 2, 0, 1, 1);

        label = new QLabel(groupBox_4);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_5->addWidget(label, 6, 0, 1, 1);

        spread = new QSlider(groupBox_4);
        spread->setObjectName(QStringLiteral("spread"));
        spread->setMinimum(1);
        spread->setMaximum(8);
        spread->setValue(6);
        spread->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(spread, 6, 2, 1, 1);

        spread_val = new QLabel(groupBox_4);
        spread_val->setObjectName(QStringLiteral("spread_val"));

        gridLayout_5->addWidget(spread_val, 6, 3, 1, 1);


        verticalLayout_2->addWidget(groupBox_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        tabs->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayout_3 = new QVBoxLayout(tab_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox_5 = new QGroupBox(tab_3);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        gridLayout = new QGridLayout(groupBox_5);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        Lose = new QLabel(groupBox_5);
        Lose->setObjectName(QStringLiteral("Lose"));

        gridLayout->addWidget(Lose, 2, 0, 1, 1);

        Gain = new QLabel(groupBox_5);
        Gain->setObjectName(QStringLiteral("Gain"));

        gridLayout->addWidget(Gain, 1, 0, 1, 1);

        lose = new QSlider(groupBox_5);
        lose->setObjectName(QStringLiteral("lose"));
        lose->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(lose, 2, 2, 1, 1);

        gain = new QSlider(groupBox_5);
        gain->setObjectName(QStringLiteral("gain"));
        gain->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(gain, 1, 2, 1, 1);

        label_2 = new QLabel(groupBox_5);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setEnabled(false);

        gridLayout->addWidget(label_2, 0, 0, 1, 2);

        threshold = new QSlider(groupBox_5);
        threshold->setObjectName(QStringLiteral("threshold"));
        threshold->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(threshold, 0, 2, 1, 1);

        threshVal = new QLabel(groupBox_5);
        threshVal->setObjectName(QStringLiteral("threshVal"));

        gridLayout->addWidget(threshVal, 0, 3, 1, 1);

        gainVal = new QLabel(groupBox_5);
        gainVal->setObjectName(QStringLiteral("gainVal"));

        gridLayout->addWidget(gainVal, 1, 3, 1, 1);

        loseVal = new QLabel(groupBox_5);
        loseVal->setObjectName(QStringLiteral("loseVal"));

        gridLayout->addWidget(loseVal, 2, 3, 1, 1);


        verticalLayout_3->addWidget(groupBox_5);

        groupBox = new QGroupBox(tab_3);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        relax_stw = new QSlider(groupBox);
        relax_stw->setObjectName(QStringLiteral("relax_stw"));
        relax_stw->setMaximum(255);
        relax_stw->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(relax_stw, 2, 2, 1, 1);

        relax_state = new QSlider(groupBox);
        relax_state->setObjectName(QStringLiteral("relax_state"));
        relax_state->setMaximum(255);
        relax_state->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(relax_state, 1, 2, 1, 1);

        rate_ltw = new QLabel(groupBox);
        rate_ltw->setObjectName(QStringLiteral("rate_ltw"));

        gridLayout_4->addWidget(rate_ltw, 3, 3, 1, 1);

        rate_state = new QLabel(groupBox);
        rate_state->setObjectName(QStringLiteral("rate_state"));

        gridLayout_4->addWidget(rate_state, 1, 3, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_4->addWidget(label_10, 1, 0, 1, 1);

        rate_stw = new QLabel(groupBox);
        rate_stw->setObjectName(QStringLiteral("rate_stw"));

        gridLayout_4->addWidget(rate_stw, 2, 3, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_4->addWidget(label_11, 2, 0, 1, 1);

        relax_suscept = new QSlider(groupBox);
        relax_suscept->setObjectName(QStringLiteral("relax_suscept"));
        relax_suscept->setMaximum(255);
        relax_suscept->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(relax_suscept, 0, 2, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_4->addWidget(label_12, 3, 0, 1, 1);

        rate_suscept = new QLabel(groupBox);
        rate_suscept->setObjectName(QStringLiteral("rate_suscept"));

        gridLayout_4->addWidget(rate_suscept, 0, 3, 1, 1);

        relax_ltw = new QSlider(groupBox);
        relax_ltw->setObjectName(QStringLiteral("relax_ltw"));
        relax_ltw->setMaximum(255);
        relax_ltw->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(relax_ltw, 3, 2, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_4->addWidget(label_3, 0, 0, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_4->addWidget(label_7, 4, 0, 1, 1);

        relax_str = new QSlider(groupBox);
        relax_str->setObjectName(QStringLiteral("relax_str"));
        relax_str->setMaximum(255);
        relax_str->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(relax_str, 4, 2, 1, 1);

        rate_str = new QLabel(groupBox);
        rate_str->setObjectName(QStringLiteral("rate_str"));

        gridLayout_4->addWidget(rate_str, 4, 3, 1, 1);


        verticalLayout_3->addWidget(groupBox);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        tabs->addTab(tab_3, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        radioButton = new QRadioButton(tab);
        buttonGroup = new QButtonGroup(TractSettings);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(radioButton);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setChecked(true);

        verticalLayout->addWidget(radioButton);

        flat = new QRadioButton(tab);
        buttonGroup->addButton(flat);
        flat->setObjectName(QStringLiteral("flat"));

        verticalLayout->addWidget(flat);

        line_2 = new QFrame(tab);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        allfiring = new QRadioButton(tab);
        buttonGroup_2 = new QButtonGroup(TractSettings);
        buttonGroup_2->setObjectName(QStringLiteral("buttonGroup_2"));
        buttonGroup_2->addButton(allfiring);
        allfiring->setObjectName(QStringLiteral("allfiring"));
        allfiring->setChecked(true);

        verticalLayout->addWidget(allfiring);

        standardfiring = new QRadioButton(tab);
        buttonGroup_2->addButton(standardfiring);
        standardfiring->setObjectName(QStringLiteral("standardfiring"));
        standardfiring->setChecked(false);

        verticalLayout->addWidget(standardfiring);

        predictivefiring = new QRadioButton(tab);
        buttonGroup_2->addButton(predictivefiring);
        predictivefiring->setObjectName(QStringLiteral("predictivefiring"));
        predictivefiring->setChecked(false);

        verticalLayout->addWidget(predictivefiring);

        line_4 = new QFrame(tab);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_4);

        origin_lobe_standard = new QRadioButton(tab);
        buttonGroup_3 = new QButtonGroup(TractSettings);
        buttonGroup_3->setObjectName(QStringLiteral("buttonGroup_3"));
        buttonGroup_3->addButton(origin_lobe_standard);
        origin_lobe_standard->setObjectName(QStringLiteral("origin_lobe_standard"));
        origin_lobe_standard->setChecked(true);

        verticalLayout->addWidget(origin_lobe_standard);

        origin_lobe_temporal = new QRadioButton(tab);
        buttonGroup_3->addButton(origin_lobe_temporal);
        origin_lobe_temporal->setObjectName(QStringLiteral("origin_lobe_temporal"));

        verticalLayout->addWidget(origin_lobe_temporal);

        line_3 = new QFrame(tab);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        data_source_standard = new QRadioButton(tab);
        buttonGroup_4 = new QButtonGroup(TractSettings);
        buttonGroup_4->setObjectName(QStringLiteral("buttonGroup_4"));
        buttonGroup_4->addButton(data_source_standard);
        data_source_standard->setObjectName(QStringLiteral("data_source_standard"));
        data_source_standard->setChecked(true);

        verticalLayout->addWidget(data_source_standard);

        data_source_temporal = new QRadioButton(tab);
        buttonGroup_4->addButton(data_source_temporal);
        data_source_temporal->setObjectName(QStringLiteral("data_source_temporal"));

        verticalLayout->addWidget(data_source_temporal);

        tabs->addTab(tab, QString());

        verticalLayout_4->addWidget(tabs);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancelButton = new QPushButton(centralwidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        closeButton = new QPushButton(centralwidget);
        closeButton->setObjectName(QStringLiteral("closeButton"));

        horizontalLayout->addWidget(closeButton);


        verticalLayout_4->addLayout(horizontalLayout);

        TractSettings->setCentralWidget(centralwidget);

        retranslateUi(TractSettings);
        QObject::connect(gain, SIGNAL(valueChanged(int)), gainVal, SLOT(setNum(int)));
        QObject::connect(threshold, SIGNAL(valueChanged(int)), threshVal, SLOT(setNum(int)));
        QObject::connect(lose, SIGNAL(valueChanged(int)), loseVal, SLOT(setNum(int)));
        QObject::connect(cancelButton, SIGNAL(clicked()), TractSettings, SLOT(close()));
        QObject::connect(max_add, SIGNAL(valueChanged(int)), max_addVal, SLOT(setNum(int)));
        QObject::connect(max_ltw, SIGNAL(valueChanged(int)), max_ltwVal, SLOT(setNum(int)));
        QObject::connect(max_str, SIGNAL(valueChanged(int)), max_strVal, SLOT(setNum(int)));
        QObject::connect(min_str, SIGNAL(valueChanged(int)), min_strVal, SLOT(setNum(int)));
        QObject::connect(min_ltw, SIGNAL(valueChanged(int)), min_ltwVal, SLOT(setNum(int)));
        QObject::connect(min_add, SIGNAL(valueChanged(int)), min_addVal, SLOT(setNum(int)));
        QObject::connect(spread, SIGNAL(valueChanged(int)), spread_val, SLOT(setNum(int)));
        QObject::connect(origin_lobe_first, SIGNAL(valueChanged(int)), min_origin_lobe, SLOT(setNum(int)));
        QObject::connect(origin_lobe_last, SIGNAL(valueChanged(int)), max_origin_lobe, SLOT(setNum(int)));
        QObject::connect(origin_lobe_max, SIGNAL(valueChanged(int)), origin_lobe_conn, SLOT(setNum(int)));
        QObject::connect(data_source_first, SIGNAL(valueChanged(int)), min_data_source, SLOT(setNum(int)));
        QObject::connect(data_source_last, SIGNAL(valueChanged(int)), max_data_source, SLOT(setNum(int)));
        QObject::connect(data_source_max, SIGNAL(valueChanged(int)), data_src_conn, SLOT(setNum(int)));

        tabs->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(TractSettings);
    } // setupUi

    void retranslateUi(QMainWindow *TractSettings)
    {
        TractSettings->setWindowTitle(QApplication::translate("TractSettings", "MainWindow", 0));
        tractName->setText(QApplication::translate("TractSettings", "Tract Name", 0));
        Mirrors->setText(QApplication::translate("TractSettings", "Mirrors", 0));
        origin_lobe_conn->setText(QApplication::translate("TractSettings", "15", 0));
        label_6->setText(QApplication::translate("TractSettings", "Last Neuron", 0));
        max_origin_lobe->setText(QApplication::translate("TractSettings", "1", 0));
        DataSource->setText(QApplication::translate("TractSettings", "Data Source", 0));
        min_data_source->setText(QApplication::translate("TractSettings", "1", 0));
        label_8->setText(QApplication::translate("TractSettings", "First Neuron", 0));
        label_26->setText(QApplication::translate("TractSettings", "Connections/Cell", 0));
        min_origin_lobe->setText(QApplication::translate("TractSettings", "1", 0));
        label_9->setText(QApplication::translate("TractSettings", "Last Neuron", 0));
        max_data_source->setText(QApplication::translate("TractSettings", "1", 0));
        OriginLobe->setText(QApplication::translate("TractSettings", "Origin Lobe", 0));
        label_5->setText(QApplication::translate("TractSettings", "First Neuron", 0));
        label_27->setText(QApplication::translate("TractSettings", "Connections/Cell", 0));
        data_src_conn->setText(QApplication::translate("TractSettings", "15", 0));
        tabs->setTabText(tabs->indexOf(tab1), QApplication::translate("TractSettings", "Connectivity", 0));
        groupBox_4->setTitle(QApplication::translate("TractSettings", "Intital Connectivity", 0));
        min_strVal->setText(QApplication::translate("TractSettings", "value", 0));
        max_strVal->setText(QApplication::translate("TractSettings", "value", 0));
        label_14->setText(QApplication::translate("TractSettings", "Max LTW", 0));
        label_17->setText(QApplication::translate("TractSettings", "Max to Add", 0));
        label_18->setText(QApplication::translate("TractSettings", "Min to Add", 0));
        min_ltwVal->setText(QApplication::translate("TractSettings", "value", 0));
        label_13->setText(QApplication::translate("TractSettings", "Min LTW", 0));
        min_addVal->setText(QApplication::translate("TractSettings", "value", 0));
        max_addVal->setText(QApplication::translate("TractSettings", "value", 0));
        max_ltwVal->setText(QApplication::translate("TractSettings", "value", 0));
#ifndef QT_NO_TOOLTIP
        label_16->setToolTip(QApplication::translate("TractSettings", "Maximum strength when new synapses are created", 0));
#endif // QT_NO_TOOLTIP
        label_16->setText(QApplication::translate("TractSettings", "Max Strength", 0));
#ifndef QT_NO_TOOLTIP
        label_15->setToolTip(QApplication::translate("TractSettings", "Minimum Strength when a new synapse is created", 0));
#endif // QT_NO_TOOLTIP
        label_15->setText(QApplication::translate("TractSettings", "Min Strength", 0));
        label->setText(QApplication::translate("TractSettings", "Spread", 0));
        spread_val->setText(QApplication::translate("TractSettings", "value", 0));
        tabs->setTabText(tabs->indexOf(tab_2), QApplication::translate("TractSettings", "Growth", 0));
        groupBox_5->setTitle(QApplication::translate("TractSettings", "Dendrite Dynamics", 0));
#ifndef QT_NO_TOOLTIP
        Lose->setToolTip(QApplication::translate("TractSettings", "When a source cell fails to fire prior to a destination cell firing any synapses connecting the two are decremented by this amount.", 0));
#endif // QT_NO_TOOLTIP
        Lose->setText(QApplication::translate("TractSettings", "Lose Strength", 0));
#ifndef QT_NO_TOOLTIP
        Gain->setToolTip(QApplication::translate("TractSettings", "When a source cell fires prior to the destination cell fires, synapses that connect them are strengthened by this amount.", 0));
#endif // QT_NO_TOOLTIP
        Gain->setText(QApplication::translate("TractSettings", "Gain Strength", 0));
        label_2->setText(QApplication::translate("TractSettings", "Threshold", 0));
        threshVal->setText(QApplication::translate("TractSettings", "value", 0));
        gainVal->setText(QApplication::translate("TractSettings", "value", 0));
        loseVal->setText(QApplication::translate("TractSettings", "value", 0));
        groupBox->setTitle(QApplication::translate("TractSettings", "Relaxation Rates", 0));
        rate_ltw->setText(QApplication::translate("TractSettings", "rate", 0));
        rate_state->setText(QApplication::translate("TractSettings", "rate", 0));
        label_10->setText(QApplication::translate("TractSettings", "Excitement", 0));
        rate_stw->setText(QApplication::translate("TractSettings", "rate", 0));
        label_11->setText(QApplication::translate("TractSettings", "STW", 0));
        label_12->setText(QApplication::translate("TractSettings", "LTW", 0));
        rate_suscept->setText(QApplication::translate("TractSettings", "rate", 0));
        label_3->setText(QApplication::translate("TractSettings", "Susceptability", 0));
        label_7->setText(QApplication::translate("TractSettings", "Strength", 0));
        rate_str->setText(QApplication::translate("TractSettings", "rate", 0));
        tabs->setTabText(tabs->indexOf(tab_3), QApplication::translate("TractSettings", "Dynamics", 0));
        radioButton->setText(QApplication::translate("TractSettings", "Dendrites migrate and are intialized randomly", 0));
        flat->setText(QApplication::translate("TractSettings", "Dendrites do not migrate and are initialized in order", 0));
        allfiring->setText(QApplication::translate("TractSettings", "Dendrites respond to all firing", 0));
        standardfiring->setText(QApplication::translate("TractSettings", "Dendrites respond only to standard firing", 0));
        predictivefiring->setText(QApplication::translate("TractSettings", "Dendrites respond only to predictive firing", 0));
        origin_lobe_standard->setText(QApplication::translate("TractSettings", "Standard Origin Lobe", 0));
        origin_lobe_temporal->setText(QApplication::translate("TractSettings", "Temporal Origin Lobe", 0));
        data_source_standard->setText(QApplication::translate("TractSettings", "Standard Data Source", 0));
        data_source_temporal->setText(QApplication::translate("TractSettings", "Temporal Data Source", 0));
        tabs->setTabText(tabs->indexOf(tab), QApplication::translate("TractSettings", "Options", 0));
        cancelButton->setText(QApplication::translate("TractSettings", "Cancel", 0));
        closeButton->setText(QApplication::translate("TractSettings", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class TractSettings: public Ui_TractSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACTGENE_H
