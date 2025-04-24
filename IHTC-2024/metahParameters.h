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
#include <qgridlayout.h>
#include <QtWidgets/QApplication>

#include "consts.h"
#include "enumOperations.h"
#include "StateController.h"

class Ui_metahParameters : public QWidget
{

    Q_OBJECT

public: 
    Ui_metahParameters(QWidget* parent = nullptr);
    ~Ui_metahParameters();

private:
    QWidget* _centralwidget;
    QSlider* _maxIterationSlider;
    QDoubleSpinBox* _neighbourSizeDoubleSpinBox;
    QDoubleSpinBox* _increaseTempItersDoubleSpinBox;
    QDoubleSpinBox* _genderGroupIterDoubleSpinBox;
    QComboBox* _neighbourGeneratorCombobox;
    QComboBox* _initSolverCombobox;
    QSlider* _startingTemperatureSlider;
    QDoubleSpinBox* _simplexCoolingMulitplierDoubleSpinBox;
    QSlider* _stopTemperatureSlider;
    QDoubleSpinBox* _prizeSizeDoubleSpinBox;
    QLabel* _maxIterationLabel;
    QLabel* _neighbourSizeLabel;
    QLabel* _prizeSizeLabel;
    QLabel* _increaseTempIterLabel;
    QLabel* _genderGroupLabel;
    QLabel* _coolingMultiplier;
    QLabel* _startingTemperatureLabel;
    QLabel* _stopTemperatureLabel;
    QLabel* _initSolverLabel;
    QLabel* _neigbourGeneratorLabel;
    QPushButton* _startGameButton;
    QLabel* _minValueMaxIterationSliderLabel;
    QLabel* _maxValueMaxIterationSliderLabel;
    QLabel* _currentValueMaxIterationSliderLabel;
    QLabel* _minValueStartingTemperatureSliderLabel;
    QLabel* _maxValueStartingTemperatureSliderLabel;
    QLabel* _currentValueStartingTemperatureSliderLabel;
    QLabel* _minValueStopTemperatureSliderLabel;
    QLabel* _maxValueStopTemperatureSliderLabel;
    QLabel* _currentValueStopTemperatureSliderLabel;
    QGridLayout* _gridLayout;

    QFont* _font;

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