/********************************************************************************
** Form generated from reading UI file 'chooseOpponent.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/
#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QStackedWidget>
#include "ScreensNumber.h"
#include "consts.h"
#include <qboxlayout.h>
#include "AllGameParameters.h"
#include <memory>

class Ui_chooseOpponent : public QWidget
{
    Q_OBJECT

public:
    Ui_chooseOpponent(QStackedWidget* stackedWidget, QWidget* parent = nullptr, std::shared_ptr<AllGameParameters> allGameParameters = nullptr);
    ~Ui_chooseOpponent();

private:
    std::shared_ptr<AllGameParameters> allGameParameters;
    QWidget *centralwidget;
    QLabel *chooseOpponentLabel;
    QPushButton *computerButton;
    QPushButton *playerButton;
    QFont* font;
    QStackedWidget* stackedWidget;
    QFont setUpFont(int points);
    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonLayout;

    void setUpPlayerButton();
    void setUpCompterButton();
    void setUpChooseOpponentLabel();

    void retranslateUi(QWidget* MainWindow);

    void setupUi(QWidget* MainWindow);

private slots:
    void onComputerButtonClicked();
    void onPlayerButtonClicked();
};

