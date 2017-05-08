/********************************************************************************
** Form generated from reading UI file 'lobegene.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOBEGENE_H
#define UI_LOBEGENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "colorwidget.h"

QT_BEGIN_NAMESPACE

class Ui_LobeSettings
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QLabel *lobeName;
    QLineEdit *lineEdit;
    QPushButton *SetColor;
    ColorWidget *ColorDisplay;
    QLabel *CellsPerColumn;
    QSlider *depth;
    QLabel *depthVal;
    QGroupBox *LobeDynamics;
    QGridLayout *gridLayout_2;
    QLabel *DesiredActivity;
    QSlider *activity;
    QLabel *activityVal;
    QLabel *MaximumBoost;
    QSlider *max_boost;
    QLabel *boostVal;
    QLabel *DutyCycle;
    QSlider *duty_cycle;
    QLabel *dutyVal;
    QLabel *Period;
    QSlider *period;
    QLabel *periodVal;
    QGroupBox *NeuronDynamics;
    QGridLayout *gridLayout;
    QLabel *Threshold;
    QSlider *threshold;
    QLabel *threshVal;
    QLabel *RelaxState;
    QSlider *relax_state;
    QLabel *stateVal;
    QLabel *RelaxMemory;
    QSlider *relax_memory;
    QLabel *prevVal;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *CancelButton;
    QPushButton *CloseButton;

    void setupUi(QMainWindow *LobeSettings)
    {
        if (LobeSettings->objectName().isEmpty())
            LobeSettings->setObjectName(QStringLiteral("LobeSettings"));
        LobeSettings->resize(268, 348);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LobeSettings->sizePolicy().hasHeightForWidth());
        LobeSettings->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(LobeSettings);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        lobeName = new QLabel(centralwidget);
        lobeName->setObjectName(QStringLiteral("lobeName"));

        gridLayout_3->addWidget(lobeName, 0, 0, 1, 1);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMaxLength(16);

        gridLayout_3->addWidget(lineEdit, 0, 1, 1, 2);

        SetColor = new QPushButton(centralwidget);
        SetColor->setObjectName(QStringLiteral("SetColor"));

        gridLayout_3->addWidget(SetColor, 1, 0, 1, 1);

        ColorDisplay = new ColorWidget(centralwidget);
        ColorDisplay->setObjectName(QStringLiteral("ColorDisplay"));

        gridLayout_3->addWidget(ColorDisplay, 1, 1, 1, 2);

        CellsPerColumn = new QLabel(centralwidget);
        CellsPerColumn->setObjectName(QStringLiteral("CellsPerColumn"));

        gridLayout_3->addWidget(CellsPerColumn, 2, 0, 1, 1);

        depth = new QSlider(centralwidget);
        depth->setObjectName(QStringLiteral("depth"));
        depth->setMaximum(8);
        depth->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(depth, 2, 1, 1, 1);

        depthVal = new QLabel(centralwidget);
        depthVal->setObjectName(QStringLiteral("depthVal"));

        gridLayout_3->addWidget(depthVal, 2, 2, 1, 1);

        LobeDynamics = new QGroupBox(centralwidget);
        LobeDynamics->setObjectName(QStringLiteral("LobeDynamics"));
        gridLayout_2 = new QGridLayout(LobeDynamics);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        DesiredActivity = new QLabel(LobeDynamics);
        DesiredActivity->setObjectName(QStringLiteral("DesiredActivity"));

        gridLayout_2->addWidget(DesiredActivity, 0, 0, 1, 1);

        activity = new QSlider(LobeDynamics);
        activity->setObjectName(QStringLiteral("activity"));
        activity->setMaximum(255);
        activity->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(activity, 0, 1, 1, 1);

        activityVal = new QLabel(LobeDynamics);
        activityVal->setObjectName(QStringLiteral("activityVal"));

        gridLayout_2->addWidget(activityVal, 0, 2, 1, 1);

        MaximumBoost = new QLabel(LobeDynamics);
        MaximumBoost->setObjectName(QStringLiteral("MaximumBoost"));

        gridLayout_2->addWidget(MaximumBoost, 1, 0, 1, 1);

        max_boost = new QSlider(LobeDynamics);
        max_boost->setObjectName(QStringLiteral("max_boost"));
        max_boost->setMinimum(0);
        max_boost->setMaximum(10);
        max_boost->setValue(2);
        max_boost->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(max_boost, 1, 1, 1, 1);

        boostVal = new QLabel(LobeDynamics);
        boostVal->setObjectName(QStringLiteral("boostVal"));

        gridLayout_2->addWidget(boostVal, 1, 2, 1, 1);

        DutyCycle = new QLabel(LobeDynamics);
        DutyCycle->setObjectName(QStringLiteral("DutyCycle"));

        gridLayout_2->addWidget(DutyCycle, 2, 0, 1, 1);

        duty_cycle = new QSlider(LobeDynamics);
        duty_cycle->setObjectName(QStringLiteral("duty_cycle"));
        duty_cycle->setMaximum(255);
        duty_cycle->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(duty_cycle, 2, 1, 1, 1);

        dutyVal = new QLabel(LobeDynamics);
        dutyVal->setObjectName(QStringLiteral("dutyVal"));

        gridLayout_2->addWidget(dutyVal, 2, 2, 1, 1);

        Period = new QLabel(LobeDynamics);
        Period->setObjectName(QStringLiteral("Period"));

        gridLayout_2->addWidget(Period, 3, 0, 1, 1);

        period = new QSlider(LobeDynamics);
        period->setObjectName(QStringLiteral("period"));
        period->setMinimum(1000);
        period->setMaximum(30000);
        period->setValue(10000);
        period->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(period, 3, 1, 1, 1);

        periodVal = new QLabel(LobeDynamics);
        periodVal->setObjectName(QStringLiteral("periodVal"));

        gridLayout_2->addWidget(periodVal, 3, 2, 1, 1);


        gridLayout_3->addWidget(LobeDynamics, 3, 0, 1, 3);

        NeuronDynamics = new QGroupBox(centralwidget);
        NeuronDynamics->setObjectName(QStringLiteral("NeuronDynamics"));
        gridLayout = new QGridLayout(NeuronDynamics);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        Threshold = new QLabel(NeuronDynamics);
        Threshold->setObjectName(QStringLiteral("Threshold"));

        gridLayout->addWidget(Threshold, 0, 0, 1, 1);

        threshold = new QSlider(NeuronDynamics);
        threshold->setObjectName(QStringLiteral("threshold"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(threshold->sizePolicy().hasHeightForWidth());
        threshold->setSizePolicy(sizePolicy1);
        threshold->setMaximum(255);
        threshold->setValue(64);
        threshold->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(threshold, 0, 1, 1, 1);

        threshVal = new QLabel(NeuronDynamics);
        threshVal->setObjectName(QStringLiteral("threshVal"));

        gridLayout->addWidget(threshVal, 0, 2, 1, 1);

        RelaxState = new QLabel(NeuronDynamics);
        RelaxState->setObjectName(QStringLiteral("RelaxState"));

        gridLayout->addWidget(RelaxState, 1, 0, 1, 1);

        relax_state = new QSlider(NeuronDynamics);
        relax_state->setObjectName(QStringLiteral("relax_state"));
        relax_state->setMaximum(255);
        relax_state->setValue(64);
        relax_state->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(relax_state, 1, 1, 1, 1);

        stateVal = new QLabel(NeuronDynamics);
        stateVal->setObjectName(QStringLiteral("stateVal"));

        gridLayout->addWidget(stateVal, 1, 2, 1, 1);

        RelaxMemory = new QLabel(NeuronDynamics);
        RelaxMemory->setObjectName(QStringLiteral("RelaxMemory"));

        gridLayout->addWidget(RelaxMemory, 2, 0, 1, 1);

        relax_memory = new QSlider(NeuronDynamics);
        relax_memory->setObjectName(QStringLiteral("relax_memory"));
        relax_memory->setMaximum(255);
        relax_memory->setValue(128);
        relax_memory->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(relax_memory, 2, 1, 1, 1);

        prevVal = new QLabel(NeuronDynamics);
        prevVal->setObjectName(QStringLiteral("prevVal"));

        gridLayout->addWidget(prevVal, 2, 2, 1, 1);


        gridLayout_3->addWidget(NeuronDynamics, 4, 0, 1, 3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        CancelButton = new QPushButton(centralwidget);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));

        horizontalLayout->addWidget(CancelButton);

        CloseButton = new QPushButton(centralwidget);
        CloseButton->setObjectName(QStringLiteral("CloseButton"));

        horizontalLayout->addWidget(CloseButton);


        gridLayout_3->addLayout(horizontalLayout, 5, 0, 1, 3);

        LobeSettings->setCentralWidget(centralwidget);

        retranslateUi(LobeSettings);
        QObject::connect(CancelButton, SIGNAL(clicked()), LobeSettings, SLOT(close()));
        QObject::connect(depth, SIGNAL(valueChanged(int)), depthVal, SLOT(setNum(int)));
        QObject::connect(threshold, SIGNAL(valueChanged(int)), threshVal, SLOT(setNum(int)));
        QObject::connect(duty_cycle, SIGNAL(valueChanged(int)), dutyVal, SLOT(setNum(int)));
        QObject::connect(activity, SIGNAL(valueChanged(int)), activityVal, SLOT(setNum(int)));
        QObject::connect(max_boost, SIGNAL(valueChanged(int)), boostVal, SLOT(setNum(int)));
        QObject::connect(period, SIGNAL(valueChanged(int)), periodVal, SLOT(setNum(int)));

        QMetaObject::connectSlotsByName(LobeSettings);
    } // setupUi

    void retranslateUi(QMainWindow *LobeSettings)
    {
        LobeSettings->setWindowTitle(QApplication::translate("LobeSettings", "Edit Lobe", 0));
        lobeName->setText(QApplication::translate("LobeSettings", "Lobe Name", 0));
        SetColor->setText(QApplication::translate("LobeSettings", "Set Color", 0));
        CellsPerColumn->setText(QApplication::translate("LobeSettings", "Cells Per Column", 0));
        depthVal->setText(QApplication::translate("LobeSettings", "value", 0));
        LobeDynamics->setTitle(QApplication::translate("LobeSettings", "Lobe Dynamics", 0));
        DesiredActivity->setText(QApplication::translate("LobeSettings", "Desired Activity", 0));
        activityVal->setText(QApplication::translate("LobeSettings", "value", 0));
        MaximumBoost->setText(QApplication::translate("LobeSettings", "Maximum Boost", 0));
        boostVal->setText(QApplication::translate("LobeSettings", "value", 0));
        DutyCycle->setText(QApplication::translate("LobeSettings", "Duty Cycle", 0));
        dutyVal->setText(QApplication::translate("LobeSettings", "value", 0));
        Period->setText(QApplication::translate("LobeSettings", "Period", 0));
        periodVal->setText(QApplication::translate("LobeSettings", "value", 0));
        NeuronDynamics->setTitle(QApplication::translate("LobeSettings", "Neuron Dynamics", 0));
        Threshold->setText(QApplication::translate("LobeSettings", "Threshold", 0));
        threshVal->setText(QApplication::translate("LobeSettings", "value", 0));
        RelaxState->setText(QApplication::translate("LobeSettings", "Relax State", 0));
        stateVal->setText(QApplication::translate("LobeSettings", "value", 0));
        RelaxMemory->setText(QApplication::translate("LobeSettings", "Relax Memory", 0));
        prevVal->setText(QApplication::translate("LobeSettings", "value", 0));
        CancelButton->setText(QApplication::translate("LobeSettings", "Cancel", 0));
        CloseButton->setText(QApplication::translate("LobeSettings", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class LobeSettings: public Ui_LobeSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOBEGENE_H
