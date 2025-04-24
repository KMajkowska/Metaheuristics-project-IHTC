/********************************************************************************
** Form generated from reading UI file 'gameParameters.ui'
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
#include <QtWidgets/QWidget>
#include <qboxlayout.h>
#include <qspinbox.h>
#include <QtWidgets/QApplication>

#include "consts.h"
#include "StateController.h"
#include "enumOperations.h"
#include "metahParameters.h"

class Ui_gameParameters : public QWidget
{

    Q_OBJECT

public:
    Ui_gameParameters(QWidget* parent = nullptr);
    ~Ui_gameParameters();

private:
    QWidget* _centralwidget;
    QComboBox* _gameTimeComboBox;
    QComboBox* _gameLevelComboBox;
    QComboBox* _winningModeComboBox;
    QComboBox* _inputParametersLevelComboBox;
    QDoubleSpinBox* _roundNumberDoubleSpinBox;
    QLabel* _timeLabel;
    QLabel* _gameLevelLabel;
    QLabel* _winningModeLabel;
    QLabel* _inputParametersLevelLabel;
    QLabel* _roundNumberLabel;
    QPushButton* _readyButton;
    QFont* _font;
    QVBoxLayout* _mainLayout;
    QHBoxLayout* _gameTimeLayout;
    QHBoxLayout* _gameWinningModeLayout;
    QHBoxLayout* _gameLevelLayout;
    QHBoxLayout* _inputParametersLevelLayout;
    QHBoxLayout* _roundNumberLayout;

    void setUpTimeLabel();
    void setUpInputParametersLevelLabel();
    void setUpGameLevelLabel();
    void setUpWinningModeLabel();
    void setUpRoundNumberLabel();
    void setUpReadyButton();
    void setUpGameTimeCombobox();
    void setUpInputParametersLevelCombobox();
    void setUpGameLevelCombobox();
    void setUpWinningModeCombobox();
    void setUpRoundNumberDoubleSpinBox();
    QFont setUpFont(int points);

    void setupUi(QWidget* MainWindow);

    void retranslateUi(QWidget* MainWindow);

private slots:
    void onReadyButtonClicked();
    void updateButtonState();
};

