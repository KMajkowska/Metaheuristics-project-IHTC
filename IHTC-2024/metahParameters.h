/********************************************************************************
** Form generated from reading UI file 'metahParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/
#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QDoubleSpinBox>
#include "consts.h"
#include <qgridlayout.h>
#include "enumOperations.h"
#include <QtWidgets/QApplication>
#include "StateController.h"

class Ui_metahParameters : public QWidget
{
public: 
    Ui_metahParameters(QWidget* parent = nullptr);
    ~Ui_metahParameters() = default;
private:
    QWidget *centralwidget;
    QSlider* maxIterationSlider;
    QDoubleSpinBox* neighbourSizeDoubleSpinBox;
    QDoubleSpinBox* increaseTempItersDoubleSpinBox;
    QDoubleSpinBox* genderGroupIterDoubleSpinBox;
    QComboBox *neighbourGeneratorCombobox;
    QComboBox *initSolverCombobox;
    QSlider* startingTemperatureSlider;
    QDoubleSpinBox* simplexCoolingMulitplierDoubleSpinBox;
    QSlider *stopTemperatureSlider;
    QDoubleSpinBox* prizeSizeDoubleSpinBox;
    QLabel *maxIterationLabel;
    QLabel *neighbourSizeLabel;
    QLabel *prizeSizeLabel;
    QLabel *increaseTempIterLabel;
    QLabel *genderGroupLabel;
    QLabel *coolingMultiplier;
    QLabel *startingTemperatureLabel;
    QLabel *stopTemperatureLabel;
    QLabel *initSolverLabel;
    QLabel *neigbourGeneratorLabel;
    QPushButton* startGameButton;;
    QLabel* minValueMaxIterationSliderLabel;
    QLabel* maxValueMaxIterationSliderLabel;
    QLabel* currentValueMaxIterationSliderLabel;
    QLabel* minValueStartingTemperatureSliderLabel;
    QLabel* maxValueStartingTemperatureSliderLabel;
    QLabel* currentValueStartingTemperatureSliderLabel;
    QLabel* minValueStopTemperatureSliderLabel;
    QLabel* maxValueStopTemperatureSliderLabel;
    QLabel* currentValueStopTemperatureSliderLabel;
    QGridLayout* gridLayout;

    QFont* font;

    void setUpStartGameButton();
    QFont setUpFont(int points);
    void setUpMaxIterationSlider();
    void setUpNeighbourSizeDoubleSpinBox();
    void setUpPrizeSizeDoubleSpinBox();
    void setUpIncreaseTempItersDoubleSpinBox();
    void setUpGenderGroupIterDoubleSpinBox();
    void setUpSimplexCoolingMultiplierDoubleSpinBox();
    void setUpNeighbourGeneratorCombobox();
    void setUpStartingTemperatureSlider();
    void setUpStopTemperatureSlider();
    void setUpInitSolverCombobox();
    void setUpMaxIterationLabel();
    void setUpNeighbourSizeLabel();
    void setUpPrizeSizeLabel();
    void setUpIncreaseTempIterLabel();
    void setUpGenderGroupLabel();
    void setUpCoolingMultiplierLabel();
    void setUpStartingTemperatureLabel();
    void setUpStopTemperatureLabel();
    void setUpInitSolverLabel();
    void setUpNeighbourGeneratorLabel();

    void setupUi(QWidget* MainWindow);

    void retranslateUi(QWidget* MainWindow);

private slots:
    void updatePrizeSizeDoubleSpinBox();
    void updateMaxIterationSlider();
    void updateStopTemperatureSlider();

public slots:
    void setSlidersEnabled(const QString& value);
    void onStartGameButtonClicked();
};