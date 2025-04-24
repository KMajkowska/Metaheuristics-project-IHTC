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
#include "gameStateHandlers.h" 

class Ui_chooseOpponent : public QWidget
{
    Q_OBJECT

public:
    Ui_chooseOpponent(QWidget* parent = nullptr);
    ~Ui_chooseOpponent();


private:
    QWidget* _centralwidget;
    QLabel* _chooseOpponentLabel;
    QPushButton* _computerButton;
    QPushButton* _playerButton;
    QFont* _font;
    QFont setUpFont(int points);
    QVBoxLayout* _mainLayout;
    QHBoxLayout* _buttonLayout;

    void setUpPlayerButton();
    void setUpCompterButton();
    void setUpChooseOpponentLabel();

    void retranslateUi(QWidget* MainWindow);

    void setupUi(QWidget* MainWindow);

private slots:
    void onComputerButtonClicked();
    void onPlayerButtonClicked();
};

