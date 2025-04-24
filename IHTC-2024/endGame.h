/********************************************************************************
** Form generated from reading UI file 'chooseOpponent.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/
#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <qboxlayout.h>
#include <memory>
#include <QtWidgets/QApplication>

#include "consts.h"
#include "StateController.h"
#include "ScreensNumber.h"
#include "Winner.h"

// TODO: Add 'YOU WIN/YOU LOSE'
class Ui_endGameScreen : public QWidget
{
    Q_OBJECT

public:
    Ui_endGameScreen(QWidget* parent = nullptr);
    ~Ui_endGameScreen();

private:
    QWidget* _centralWidget;
    QFont* _font;
    QPushButton* _endButton;
    QPushButton* _returnButton;
    QVBoxLayout* _mainLayout;
    QHBoxLayout* _buttonLayout;
    QLabel* _gameResultLabel;

    void setupUi(QWidget* mainWindow);
    void retranslateUi(QWidget* mainWindow);

    void setUpEndButton();
    QFont setUpFont(int points);
    void setUpReturnButton();
    void setUpGameResultLabel();

    void changeGameResultLabel(Winner winner);

private slots:
    void onReturnButtonClicked();
};

