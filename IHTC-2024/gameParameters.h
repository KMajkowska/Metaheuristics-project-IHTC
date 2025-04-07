/********************************************************************************
** Form generated from reading UI file 'gameParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/
#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <qstackedwidget.h>
#include "ScreensNumber.h"
#include "GameLevel.h"
#include "GameWinningMode.h"
#include "GameTimeValues.h"
#include "consts.h"
#include "metahParameters.h"
#include <qboxlayout.h>
#include <AllGameParameters.h>

class Ui_gameParameters : public QWidget
{
public:
    Ui_gameParameters(QStackedWidget* stackedWidget, QWidget* parent = nullptr, std::shared_ptr<AllGameParameters> allGameParameters = nullptr);
    ~Ui_gameParameters() = default;

private:
    std::shared_ptr<AllGameParameters> allGameParameters;
    QWidget *centralwidget;
    QComboBox *gameTimeComboBox;
    QComboBox *gameLevelComboBox;
    QComboBox *winningModeComboBox;
    QLabel *timeLabel;
    QLabel *gameLevelLabel;
    QLabel *winningModeLabel;
    QPushButton *readyButton;
    QFont* font;
    QStackedWidget* stackedWidget;
    QVBoxLayout* mainLayout;
    QHBoxLayout* gameTimeLayout;
    QHBoxLayout* gameWinningModeLayout;
    QHBoxLayout* gameLevelLayout;
    Ui_metahParameters* metahParameters;

    void setUpTimeLabel();
    void setUpGameLevelLabel();
    void setUpWinningModeLabel();
    void setUpReadyButton();
    void setUpGameTimeCombobox();
    void setUpGameLevelCombobox();
    void setUpWinningModeCombobox();
    QFont setUpFont(int points);

    void setupUi(QWidget* MainWindow);

    void retranslateUi(QWidget* MainWindow);

private slots:
    void onReadyButtonClicked();
    void updateButtonState();
};

