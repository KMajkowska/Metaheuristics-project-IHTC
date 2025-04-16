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
#include "consts.h"
#include <qboxlayout.h>
#include <qspinbox.h>
#include <QtWidgets/QApplication>
#include "StateController.h"
#include <enumOperations.h>
#include <metahParameters.h>

class Ui_gameParameters : public QWidget
{
public:
    Ui_gameParameters(QWidget* parent = nullptr);
    ~Ui_gameParameters() = default;

private:
    QWidget *centralwidget;
    QComboBox *gameTimeComboBox;
    QComboBox *gameLevelComboBox;
    QComboBox *winningModeComboBox;
    QComboBox* inputParametersLevelComboBox;
    QDoubleSpinBox* roudNumberDoubleSpinBox;
    QLabel *timeLabel;
    QLabel *gameLevelLabel;
    QLabel *winningModeLabel;
    QLabel* inputParametersLevelLabel;
    QLabel *roundNumberLabel;
    QPushButton *readyButton;
    QFont* font;
    QVBoxLayout* mainLayout;
    QHBoxLayout* gameTimeLayout;
    QHBoxLayout* gameWinningModeLayout;
    QHBoxLayout* gameLevelLayout;
    QHBoxLayout* inputParametersLevelLayout;
    QHBoxLayout* roundNumberLayout;

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

